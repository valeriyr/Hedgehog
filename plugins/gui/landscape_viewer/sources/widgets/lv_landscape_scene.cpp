
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/widgets/landscape_scene_states/lv_landscape_scene_states.hpp"
#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"
#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_iunit.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"
#include "settings/h/st_events.hpp"

#include "animation_manager/ih/am_ianimate_object.hpp"

#include "lv_landscape_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class ObjectGraphicsItem
	:	public QGraphicsPixmapItem
	,	public Framework::GUI::AnimationManager::IAnimateObject
{

public:

	ObjectGraphicsItem( const QPixmap& _pixmap, QGraphicsItem* _parent = NULL )
		:	QGraphicsPixmapItem( _pixmap, _parent )
	{}

	virtual void setSprite( const QPixmap& _sprite )
	{
		setPixmap( _sprite );
	}
};

/*---------------------------------------------------------------------------*/


LandscapeScene::LandscapeScene( const IEnvironment& _environment, QObject* _parent )
	:	QGraphicsScene( _parent )
	,	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_landscapeSceneState( new LandscapeSceneGameState( _environment, *this ) )
	,	m_unitsCollection()
{
} // LandscapeScene::LandscapeScene


/*---------------------------------------------------------------------------*/


LandscapeScene::~LandscapeScene()
{
} // LandscapeScene::~LandscapeScene


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	m_landscapeSceneState->mousePressEvent( _mouseEvent );

	QGraphicsScene::mousePressEvent( _mouseEvent );

} // LandscapeScene::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	m_landscapeSceneState->mouseMoveEvent( _mouseEvent );

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeScene::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	m_landscapeSceneState->mouseReleaseEvent( _mouseEvent );

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeScene::mouseReleaseEvent


/*---------------------------------------------------------------------------*/


void
LandscapeScene::landscapeWasOpened()
{
	setCorrectSceneSize();

	generateLandscape();

	if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
		generateTerrainMapLayer();

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Framework::Core::Settings::Events::SettingChanged::ms_type
							,	boost::bind( &LandscapeScene::onSettingChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_type
							,	boost::bind( &LandscapeScene::onObjectCreated, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_type
							,	boost::bind( &LandscapeScene::onSurfaceItemChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::UnitsSelectionChanged::ms_type
							,	boost::bind( &LandscapeScene::onUnitsSelectionChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::UnitMoved::ms_type
							,	boost::bind( &LandscapeScene::onUnitMoved, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::UnitStateChanged::ms_type
							,	boost::bind( &LandscapeScene::onUnitStateChanged, this, _1 ) );

} // LandscapeScene::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeScene::landscapeWasClosed()
{
	m_subscriber.unsubscribe();

	removeAllObjects();
	clear();

	setCorrectSceneSize();

} // LandscapeScene::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onChangeSurfaceItem( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& _id )
{
	m_landscapeSceneState.reset( new LandscapeSurfaceItemEditingState( m_environment, *this, _id ) );

} // LandscapeScene::onChangeSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onChangeObject( const QString& _name )
{
	m_landscapeSceneState.reset( new LandscapeObjectEditingState( m_environment, *this, _name ) );

} // LandscapeScene::onChangeObject


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onControlItemSelected()
{
	m_landscapeSceneState.reset( new LandscapeSceneGameState( m_environment, *this ) );

} // LandscapeScene::onControlItemSelected


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onMousePossitionWasChanged( const QPointF& _point )
{
	m_landscapeSceneState->onMousePossitionWasChanged( _point );

} // LandscapeScene::onMousePossitionWasChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onSettingChanged( const Framework::Core::EventManager::Event& _event )
{
	const bool terrainMapVisibility = m_environment.getBool( Resources::Properties::TerrainMapVisibility );

	clearTerrainMapLayer();

	if ( terrainMapVisibility )
	{
		generateTerrainMapLayer();
	}

} // LandscapeScene::onSettingChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectCreated( const Framework::Core::EventManager::Event& _event )
{
	const QString objectName = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_objectNameAttribute ).toString();
	const QPoint objectPosition = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_objectPositionAttribute ).toPoint();
	const Plugins::Core::LandscapeModel::IUnit::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_objectUniqueIdAttribute ).toInt();

	const QPixmap& objectPixmap = m_environment.getPixmap( objectName, GraphicsInfoCache::ms_anySkinIdentifier );

	qreal xpos = objectPosition.x() * Resources::Landscape::CellSize;
	qreal ypos = objectPosition.y() * Resources::Landscape::CellSize;

	if ( static_cast< unsigned int >( objectPixmap.width() ) > Resources::Landscape::CellSize )
	{
		xpos -= ( objectPixmap.width() - Resources::Landscape::CellSize ) / 2;
	}

	if ( static_cast< unsigned int >( objectPixmap.height() ) > Resources::Landscape::CellSize )
	{
		ypos -= ( objectPixmap.height() - Resources::Landscape::CellSize ) / 2;
	}

	if ( xpos > width() - objectPixmap.width() )
		xpos = width() - Resources::Landscape::CellSize - ( objectPixmap.width() - Resources::Landscape::CellSize ) / 2;

	if ( ypos > height() - objectPixmap.height() )
		ypos = height() - Resources::Landscape::CellSize - ( objectPixmap.height() - Resources::Landscape::CellSize ) / 2;

	ObjectGraphicsItem* newItem = new ObjectGraphicsItem( objectPixmap );
	addItem( newItem );

	newItem->setPos( QPoint( xpos, ypos ) );
	newItem->setZValue( LandscapeScene::ObjectZValue::Object );

	unitWasAdded( id, newItem );

	m_environment.playAnimation(
			*newItem
		,	generateAnimationName(
					GraphicsInfoCache::ms_anySkinIdentifier
				,	objectName
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Down ) );

	regenerateTerrainMapLayer();

} // LandscapeScene::onObjectCreated


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onSurfaceItemChanged( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle = m_environment.getCurrentLandscape();

	const Plugins::Core::LandscapeModel::ISurfaceItem::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_surfaceItemIdAttribute ).toUInt();
	const QPoint position
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_surfaceItemPositionAttribute ).toPoint();

	if ( handle->getLandscape() )
	{
		QPoint scenePosition( position.x() * Resources::Landscape::CellSize, position.y() * Resources::Landscape::CellSize );

		QList< QGraphicsItem* > itemsList = items( scenePosition, Qt::ContainsItemShape, Qt::AscendingOrder );

		if ( itemsList.isEmpty() )
			return;

		QPointF itemPos = itemsList[LandscapeScene::ObjectZValue::Surface]->scenePos();
		delete itemsList[LandscapeScene::ObjectZValue::Surface];

		boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
			surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, id );

		QGraphicsPixmapItem* newItem
			= addPixmap( m_environment.getPixmap(
					surfaceItemGraphicsInfo->getAtlasName()
				,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( surfaceItemGraphicsInfo->getFrameRect() ) ) );

		newItem->setPos( itemPos );
		newItem->setZValue( LandscapeScene::ObjectZValue::Surface );
	}

	regenerateTerrainMapLayer();

} // LandscapeScene::onSurfaceItemChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onUnitsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	markSelectedUnits();

} // LandscapeScene::onUnitsSelectionChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onUnitMoved( const Framework::Core::EventManager::Event& _event )
{
	const QString unitName
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitMoved::ms_unitNameAttribute ).toString();
	const Plugins::Core::LandscapeModel::IUnit::IdType unitId
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitMoved::ms_unitIdAttribute ).toInt();
	const QPoint movedFrom
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitMoved::ms_movingFromAttribute ).toPoint();
	const QPoint movedTo
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitMoved::ms_movingToAttribute ).toPoint();
	const float progress
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitMoved::ms_movingProgressAttribute ).toFloat();

	UnitsCollectionIterator iterator = m_unitsCollection.find( unitId );
	assert( iterator != m_unitsCollection.end() );

	const QPoint movedFromInScene( movedFrom.x() * Resources::Landscape::CellSize, movedFrom.y() * Resources::Landscape::CellSize );
	const QPoint movedToInScene( movedTo.x() * Resources::Landscape::CellSize, movedTo.y() * Resources::Landscape::CellSize );

	int xpos = movedFromInScene.x() + ( ( movedToInScene.x() - movedFromInScene.x() ) * progress );
	int ypos = movedFromInScene.y() + ( ( movedToInScene.y() - movedFromInScene.y() ) * progress );

	const QPixmap& objectPixmap = m_environment.getPixmap( unitName, GraphicsInfoCache::ms_anySkinIdentifier );

	if ( static_cast< unsigned int >( objectPixmap.width() ) > Resources::Landscape::CellSize )
	{
		xpos -= ( objectPixmap.width() - Resources::Landscape::CellSize ) / 2;
	}

	if ( static_cast< unsigned int >( objectPixmap.height() ) > Resources::Landscape::CellSize )
	{
		ypos -= ( objectPixmap.height() - Resources::Landscape::CellSize ) / 2;
	}

	/*QTimeLine *timer = new QTimeLine(5000);
    timer->setFrameRange(0, 100);

	QGraphicsItemAnimation *animation = new QGraphicsItemAnimation();

	animation->setItem( iterator->second );
    animation->setTimeLine( timer );

	for (int x = movedFromInScene.x(); x < movedToInScene.x(); ++x)
        animation->setPosAt(movedFromInScene.x() / movedToInScene.x(), QPointF(x, movedFromInScene.y()));

	timer->start();*/

	iterator->second->setPos( QPoint( xpos, ypos ) );

	regenerateTerrainMapLayer();

} // LandscapeScene::onUnitMoved


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onUnitStateChanged( const Framework::Core::EventManager::Event& _event )
{
	const QString unitName
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitStateChanged::ms_unitNameAttribute ).toString();
	const Plugins::Core::LandscapeModel::IUnit::IdType unitId
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitStateChanged::ms_unitIdAttribute ).toInt();
	const Plugins::Core::LandscapeModel::ObjectState::Enum unitState
		= static_cast< Plugins::Core::LandscapeModel::ObjectState::Enum >(
			_event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitStateChanged::ms_unitState ).toInt() );
	const Plugins::Core::LandscapeModel::Direction::Enum unitDirection
		= static_cast< Plugins::Core::LandscapeModel::Direction::Enum >(
			_event.getAttribute( Plugins::Core::LandscapeModel::Events::UnitStateChanged::ms_unitDirection ).toInt() );

	UnitsCollectionIterator iterator = m_unitsCollection.find( unitId );
	assert( iterator != m_unitsCollection.end() );

	m_environment.playAnimation(
			*iterator->second
		,	generateAnimationName(
					GraphicsInfoCache::ms_anySkinIdentifier
				,	unitName
				,	unitState
				,	unitDirection ) );

} // LandscapeScene::onUnitStateChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::generateLandscape()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		for ( unsigned int i = 0; i < handle->getLandscape()->getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < handle->getLandscape()->getHeight(); ++j )
			{
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
					surfaceItem = handle->getLandscape()->getSurfaceItem( QPoint( i, j ) );

				boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
					surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, surfaceItem->getId() );

				QGraphicsPixmapItem* item
					= addPixmap( m_environment.getPixmap(
							surfaceItemGraphicsInfo->getAtlasName()
						,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( surfaceItemGraphicsInfo->getFrameRect() ) ) );

				item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
				item->setZValue( ObjectZValue::Surface );
			}
		}

		Plugins::Core::LandscapeModel::ILandscape::UnitsCollection unitsCollection;
		handle->getLandscape()->fetchUnits( unitsCollection );

		Plugins::Core::LandscapeModel::ILandscape::UnitsCollectionIterator
				begin = unitsCollection.begin()
			,	end = unitsCollection.end();

		for ( ; begin != end; ++begin )
		{
			const QPixmap& objectPixmap = m_environment.getPixmap( ( *begin )->getType()->getName(), GraphicsInfoCache::ms_anySkinIdentifier );

			ObjectGraphicsItem* newItem = new ObjectGraphicsItem( objectPixmap );
			addItem( newItem );

			QRect position = ( *begin )->getPosition();

			qreal posByX = position.x() * Resources::Landscape::CellSize;
			qreal posByY = position.y() * Resources::Landscape::CellSize;

			if ( static_cast< unsigned int >( objectPixmap.width() ) > Resources::Landscape::CellSize )
			{
				posByX -= ( objectPixmap.width() - Resources::Landscape::CellSize ) / 2;
			}

			if ( static_cast< unsigned int >( objectPixmap.height() ) > Resources::Landscape::CellSize )
			{
				posByY -= ( objectPixmap.height() - Resources::Landscape::CellSize ) / 2;
			}

			newItem->setPos( posByX, posByY );
			newItem->setZValue( ObjectZValue::Object );

			unitWasAdded( ( *begin )->getUniqueId(), newItem );

			m_environment.playAnimation(
					*newItem
				,	generateAnimationName(
							GraphicsInfoCache::ms_anySkinIdentifier
						,	( *begin )->getType()->getName()
						,	( *begin )->getState()
						,	( *begin )->getDirection() ) );
		}
	}

} // LandscapeScene::generateLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeScene::generateTerrainMapLayer()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		for ( unsigned int i = 0; i < handle->getLandscape()->getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < handle->getLandscape()->getHeight(); ++j )
			{
				Plugins::Core::LandscapeModel::TerrainMapData
					terrainMapData = handle->getLandscape()->getTerrainMapData( QPoint( i, j ) );

				QColor color;

				if ( terrainMapData.m_engagedWithGround )
				{
					color = QColor( 255, 0, 255 );
				}
				else if ( terrainMapData.m_engagedWithAir )
				{
					color = QColor( 0, 255, 255 );
				}
				else if ( terrainMapData.m_terrainMapItem == Plugins::Core::LandscapeModel::TerrainMapItem::Ground )
				{
					color = QColor( 0, 255, 0 );
				}
				else if ( terrainMapData.m_terrainMapItem == Plugins::Core::LandscapeModel::TerrainMapItem::NotAvailable )
				{
					color = QColor( 255, 0, 0 );
				}
				else if ( terrainMapData.m_terrainMapItem == Plugins::Core::LandscapeModel::TerrainMapItem::Water )
				{
					color = QColor( 0, 0, 255 );
				}
				else
				{
					assert( !"Unknown terrain map item!" );
				}

				QPixmap pixmap( QSize( Resources::Landscape::CellSize, Resources::Landscape::CellSize ) );
				pixmap.fill( color );

				QGraphicsPixmapItem* item = new QGraphicsPixmapItem( pixmap );

				item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
				item->setZValue( ObjectZValue::Terrain );

				QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
				opacityEffect->setOpacity( 0.4 );

				item->setGraphicsEffect( opacityEffect );

				addItem( item );
			}
		}
	}

} // LandscapeScene::generateTerrainMapLayer


/*---------------------------------------------------------------------------*/


void
LandscapeScene::clearTerrainMapLayer()
{
	QList< QGraphicsItem* > items( items() );

	for ( int i = 0; i < items.size(); ++i )
	{
		if ( items[ i ]->zValue() == ObjectZValue::Terrain )
			delete items[ i ];
	}

} // LandscapeScene::clearTerrainMapLayer


/*---------------------------------------------------------------------------*/


void
LandscapeScene::regenerateTerrainMapLayer()
{
	if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
	{
		clearTerrainMapLayer();
		generateTerrainMapLayer();
	}

} // LandscapeScene::regenerateTerrainMapLayer


/*---------------------------------------------------------------------------*/


void
LandscapeScene::setCorrectSceneSize()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		setSceneRect( 0, 0, handle->getLandscape()->getWidth() * Resources::Landscape::CellSize, handle->getLandscape()->getHeight() * Resources::Landscape::CellSize );
	}
	else
	{
		setSceneRect( 0, 0, 0, 0 );
	}

} // LandscapeScene::setCorrectSceneSize


/*---------------------------------------------------------------------------*/


void
LandscapeScene::unitWasAdded( const Plugins::Core::LandscapeModel::IUnit::IdType& _id, ObjectGraphicsItem* _item )
{
	assert( m_unitsCollection.find( _id ) == m_unitsCollection.end() );
	m_unitsCollection.insert( std::make_pair( _id, _item ) );

} // LandscapeScene::unitWasAdded


/*---------------------------------------------------------------------------*/


void
LandscapeScene::markSelectedUnits()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		UnitsCollectionIterator
				unitsBegin = m_unitsCollection.begin()
			,	unitsEnd = m_unitsCollection.end();

		for ( ; unitsBegin != unitsEnd; ++unitsBegin )
		{
			unitsBegin->second->setGraphicsEffect( NULL );
		}

		Plugins::Core::LandscapeModel::ILandscape::UnitsCollection selectedUnitsCollection;
		handle->getLandscape()->fetchSelectedUnits( selectedUnitsCollection );

		Plugins::Core::LandscapeModel::ILandscape::UnitsCollectionIterator
				selectedUnitsBegin = selectedUnitsCollection.begin()
			,	selectedUnitsEnd = selectedUnitsCollection.end();

		for ( ; selectedUnitsBegin != selectedUnitsEnd; ++selectedUnitsBegin )
		{
			UnitsCollectionIterator iterator = m_unitsCollection.find( ( *selectedUnitsBegin )->getUniqueId() );
			assert( iterator != m_unitsCollection.end() );

			iterator->second->setGraphicsEffect( new QGraphicsColorizeEffect() );
		}
	}

} // LandscapeScene::markSelectedUnits


/*---------------------------------------------------------------------------*/


QPoint
LandscapeScene::convertFromScenePosition( const QPointF& _scenePosition )
{
	return
		QPoint(
				_scenePosition.x() / Resources::Landscape::CellSize
			,	_scenePosition.y() / Resources::Landscape::CellSize );

} // LandscapeScene::convertFromScenePosition


/*---------------------------------------------------------------------------*/


void
LandscapeScene::removeAllObjects()
{
	UnitsCollectionIterator
			unitsBegin = m_unitsCollection.begin()
		,	unitsEnd = m_unitsCollection.end();

	for ( ; unitsBegin != unitsEnd; ++unitsBegin )
	{
		m_environment.stopAnimation( *unitsBegin->second );
	}

	m_unitsCollection.clear();

} // LandscapeScene::removeAllObjects


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
