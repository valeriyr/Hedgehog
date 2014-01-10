
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/widgets/landscape_scene_states/lv_landscape_scene_states.hpp"
#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"
#include "landscape_viewer/sources/graphics_info_cache/lv_igraphics_info_cache.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

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
	,	m_objectsCollection()
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

	fillScene();

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Framework::Core::Settings::Events::SettingChanged::ms_type
							,	boost::bind( &LandscapeScene::onSettingChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_type
							,	boost::bind( &LandscapeScene::onObjectCreated, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::CreateObjectFailed::ms_type
							,	boost::bind( &LandscapeScene::onCreateObjectFailed, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_type
							,	boost::bind( &LandscapeScene::onSurfaceItemChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectsSelectionChanged::ms_type
							,	boost::bind( &LandscapeScene::onObjectsSelectionChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_type
							,	boost::bind( &LandscapeScene::onObjectMoved, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_type
							,	boost::bind( &LandscapeScene::onObjectStateChanged, this, _1 ) );

} // LandscapeScene::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeScene::landscapeWasClosed()
{
	m_subscriber.unsubscribe();

	clearScene();

	setCorrectSceneSize();

} // LandscapeScene::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onChangeSurfaceItem( const Plugins::Core::LandscapeModel::ISurfaceItem::Id& _id )
{
	m_landscapeSceneState.reset( new LandscapeSurfaceItemEditingState( m_environment, *this, _id ) );
	m_environment.playSound( Resources::Sounds::PlacementSuccess );

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
	if (	_event.getAttribute( Framework::Core::Settings::Events::SettingChanged::ms_key ).toString()
		==	Resources::Properties::TerrainMapVisibility )
	{
		const bool terrainMapVisibility = m_environment.getBool( Resources::Properties::TerrainMapVisibility );

		clearTerrainMapLayer();

		if ( terrainMapVisibility )
		{
			generateTerrainMapLayer();
		}
	}
	else if (	_event.getAttribute( Framework::Core::Settings::Events::SettingChanged::ms_key ).toString()
			==	Resources::Properties::SkinId )
	{
		clearScene();
		fillScene();
	}

} // LandscapeScene::onSettingChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectCreated( const Framework::Core::EventManager::Event& _event )
{
	const QString objectName = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_objectNameAttribute ).toString();
	const QPoint objectLocation = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_objectLocationAttribute ).toPoint();
	const Plugins::Core::LandscapeModel::Object::UniqueId id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectCreated::ms_objectUniqueIdAttribute ).toInt();

	QPointF correctedPosition(
		LandscapeScene::correctSceneObjectPosition(
				m_environment
			,	width()
			,	height()
			,	LandscapeScene::convertToScenePosition( objectLocation )
			,	objectName ) );

	ObjectGraphicsItem* newItem = new ObjectGraphicsItem( m_environment.getPixmap( objectName ) );
	addItem( newItem );

	newItem->setPos( correctedPosition );
	newItem->setZValue( LandscapeScene::ObjectZValue::Object );

	objectWasAdded( id, newItem );

	playAnimation(
			*newItem
		,	m_environment.getString( Resources::Properties::SkinId )
		,	objectName
		,	Core::LandscapeModel::ObjectState::Standing
		,	Core::LandscapeModel::Direction::Down );

	regenerateTerrainMapLayer();

	m_environment.playSound( Resources::Sounds::PlacementSuccess );

} // LandscapeScene::onObjectCreated


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onCreateObjectFailed( const Framework::Core::EventManager::Event& _event )
{
	m_environment.playSound( Resources::Sounds::PlacementError );

} // LandscapeScene::onCreateObjectFailed


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onSurfaceItemChanged( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle = m_environment.getCurrentLandscape();

	const Plugins::Core::LandscapeModel::ISurfaceItem::Id id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_surfaceItemIdAttribute ).toUInt();
	const QPoint location
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_surfaceItemLocationAttribute ).toPoint();

	if ( handle->getLandscape() )
	{
		QPointF scenePosition( LandscapeScene::convertToScenePosition( location ) );

		QList< QGraphicsItem* > itemsList = items( scenePosition, Qt::ContainsItemShape, Qt::AscendingOrder );

		if ( itemsList.isEmpty() )
			return;

		QPointF itemPos = itemsList[LandscapeScene::ObjectZValue::Surface]->scenePos();
		delete itemsList[LandscapeScene::ObjectZValue::Surface];

		boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
			surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( m_environment.getString( Resources::Properties::SkinId ), id );

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
LandscapeScene::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	markSelectedObjects();

} // LandscapeScene::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectMoved( const Framework::Core::EventManager::Event& _event )
{
	const QString name
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_objectNameAttribute ).toString();
	const Plugins::Core::LandscapeModel::Object::UniqueId id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_objectIdAttribute ).toInt();
	const QPoint movedFrom
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_movingFromAttribute ).toPoint();
	const QPoint movedTo
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_movingToAttribute ).toPoint();
	const float progress
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_movingProgressAttribute ).toFloat();

	ObjectsCollectionIterator iterator = m_objectsCollection.find( id );
	assert( iterator != m_objectsCollection.end() );

	const QPointF movedFromInScene( LandscapeScene::convertToScenePosition( movedFrom ) );
	const QPointF movedToInScene( LandscapeScene::convertToScenePosition( movedTo ) );

	QPointF correctedPosition(
		LandscapeScene::correctSceneObjectPosition(
				m_environment
			,	width()
			,	height()
			,	QPoint(
						movedFromInScene.x() + ( ( movedToInScene.x() - movedFromInScene.x() ) * progress )
					,	movedFromInScene.y() + ( ( movedToInScene.y() - movedFromInScene.y() ) * progress ) )
			,	name ) );

	iterator->second->setPos( correctedPosition );

	regenerateTerrainMapLayer();

} // LandscapeScene::onObjectMoved


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectStateChanged( const Framework::Core::EventManager::Event& _event )
{
	const QString name
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectNameAttribute ).toString();
	const Plugins::Core::LandscapeModel::Object::UniqueId id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectIdAttribute ).toInt();
	const Plugins::Core::LandscapeModel::ObjectState::Enum state
		= static_cast< Plugins::Core::LandscapeModel::ObjectState::Enum >(
			_event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectState ).toInt() );
	const Plugins::Core::LandscapeModel::Direction::Enum direction
		= static_cast< Plugins::Core::LandscapeModel::Direction::Enum >(
			_event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectDirection ).toInt() );

	ObjectsCollectionIterator iterator = m_objectsCollection.find( id );
	assert( iterator != m_objectsCollection.end() );

	playAnimation(
			*iterator->second
		,	m_environment.getString( Resources::Properties::SkinId )
		,	name
		,	state
		,	direction );

} // LandscapeScene::onObjectStateChanged


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
					surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo(
							m_environment.getString( Resources::Properties::SkinId )
						,	surfaceItem->getId() );

				QGraphicsPixmapItem* item
					= addPixmap( m_environment.getPixmap(
							surfaceItemGraphicsInfo->getAtlasName()
						,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( surfaceItemGraphicsInfo->getFrameRect() ) ) );

				item->setPos( LandscapeScene::convertToScenePosition( QPoint( i, j ) ) );
				item->setZValue( ObjectZValue::Surface );
			}
		}

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection objectsCollection;
		handle->getLandscape()->fetchObjects( objectsCollection );

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollectionIterator
				begin = objectsCollection.begin()
			,	end = objectsCollection.end();

		for ( ; begin != end; ++begin )
		{
			ObjectGraphicsItem* newItem
				= new ObjectGraphicsItem( m_environment.getPixmap( ( *begin )->getName() ) );
			addItem( newItem );

			boost::intrusive_ptr< Core::LandscapeModel::ILocateComponent > locateComponent
				= ( *begin )->getComponent< Core::LandscapeModel::ILocateComponent >( Plugins::Core::LandscapeModel::ComponentId::Locate );

			QPointF correctedPosition(
				LandscapeScene::correctSceneObjectPosition(
						m_environment
					,	width()
					,	height()
					,	LandscapeScene::convertToScenePosition( locateComponent->getLocation() )
					,	( *begin )->getName() ) );

			newItem->setPos( correctedPosition );
			newItem->setZValue( ObjectZValue::Object );

			objectWasAdded( ( *begin )->getUniqueId(), newItem );

			playAnimation(
					*newItem
				,	m_environment.getString( Resources::Properties::SkinId )
				,	( *begin )->getName()
				,	( *begin )->getState()
				,	locateComponent->getDirection() );
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

				item->setPos( LandscapeScene::convertToScenePosition( QPoint( i, j ) ) );
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
LandscapeScene::objectWasAdded( const Plugins::Core::LandscapeModel::Object::UniqueId& _id, ObjectGraphicsItem* _item )
{
	assert( m_objectsCollection.find( _id ) == m_objectsCollection.end() );
	m_objectsCollection.insert( std::make_pair( _id, _item ) );

} // LandscapeScene::objectWasAdded


/*---------------------------------------------------------------------------*/


void
LandscapeScene::markSelectedObjects()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		ObjectsCollectionIterator
				objectsBegin = m_objectsCollection.begin()
			,	objectsEnd = m_objectsCollection.end();

		for ( ; objectsBegin != objectsEnd; ++objectsBegin )
		{
			objectsBegin->second->setGraphicsEffect( NULL );
		}

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
		handle->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollectionIterator
				selectedObjectsBegin = selectedObjectsCollection.begin()
			,	selectedObjectsEnd = selectedObjectsCollection.end();

		for ( ; selectedObjectsBegin != selectedObjectsEnd; ++selectedObjectsBegin )
		{
			ObjectsCollectionIterator iterator = m_objectsCollection.find( ( *selectedObjectsBegin )->getUniqueId() );
			assert( iterator != m_objectsCollection.end() );

			iterator->second->setGraphicsEffect( new QGraphicsColorizeEffect() );
		}
	}

} // LandscapeScene::markSelectedObjects


/*---------------------------------------------------------------------------*/


QPoint
LandscapeScene::convertFromScenePosition( const QPointF& _scenePosition )
{
	return
		QPoint(
				_scenePosition.x() < 0 ? 0 : static_cast< int >( _scenePosition.x() / Resources::Landscape::CellSize )
			,	_scenePosition.y() < 0 ? 0 : static_cast< int >( _scenePosition.y() / Resources::Landscape::CellSize ) );

} // LandscapeScene::convertFromScenePosition


/*---------------------------------------------------------------------------*/


QPointF
LandscapeScene::convertToScenePosition( const QPoint& _location )
{
	return QPointF( _location.x() * Resources::Landscape::CellSize, _location.y() * Resources::Landscape::CellSize );

} // LandscapeScene::convertToScenePosition


/*---------------------------------------------------------------------------*/


QPointF
LandscapeScene::roundScenePosition( const QPointF& _scenePosition )
{
	return
		QPointF(
				_scenePosition.x() < 0 ? 0 : ( static_cast< int >( _scenePosition.x() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize )
			,	_scenePosition.y() < 0 ? 0 : ( static_cast< int >( _scenePosition.y() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize ) );

} // LandscapeScene::roundScenePosition


/*---------------------------------------------------------------------------*/


QPointF
LandscapeScene::correctSceneObjectPosition(
		const IEnvironment& _environment
	,	const int _sceneWidth
	,	const int _sceneHeight
	,	const QPointF& _roundedPosition
	,	const QString& _objectName )
{
	QPoint correctedPosition( _roundedPosition.x(), _roundedPosition.y() );

	Core::LandscapeModel::IStaticData::ObjectStaticData objectStaticData
		= _environment.getObjectStaticData( _objectName );

	const QPixmap& objectPixmap = _environment.getPixmap( _objectName );

	if ( correctedPosition.x() > _sceneWidth - ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) )
		correctedPosition.setX( _sceneWidth - ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) );

	if ( correctedPosition.y() > _sceneHeight - ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) )
		correctedPosition.setY( _sceneHeight - ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) );

	if ( objectPixmap.width() > ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) )
		correctedPosition.setX( correctedPosition.x() - ( objectPixmap.width() - ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) ) / 2 );

	if ( objectPixmap.height() > ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) )
		correctedPosition.setY( correctedPosition.y() - ( objectPixmap.height() - ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) ) / 2 );

	return correctedPosition;

} // LandscapeScene::correctSceneObjectPosition


/*---------------------------------------------------------------------------*/


void
LandscapeScene::removeAllObjects()
{
	ObjectsCollectionIterator
			begin = m_objectsCollection.begin()
		,	end = m_objectsCollection.end();

	for ( ; begin != end; ++begin )
	{
		m_environment.stopAnimation( *begin->second );
	}

	m_objectsCollection.clear();

} // LandscapeScene::removeAllObjects


/*---------------------------------------------------------------------------*/


void
LandscapeScene::clearScene()
{
	m_landscapeSceneState->removeSceneObjects();

	removeAllObjects();
	clear();

} // LandscapeScene::clearScene


/*---------------------------------------------------------------------------*/


void
LandscapeScene::fillScene()
{
	generateLandscape();

	if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
		generateTerrainMapLayer();

	m_landscapeSceneState->addSceneObjects();

} // LandscapeScene::fillScene


/*---------------------------------------------------------------------------*/


void
LandscapeScene::playAnimation(
		Framework::GUI::AnimationManager::IAnimateObject& _animateObject
	,	const QString& _skinId
	,	const QString& _typeName
	,	const Core::LandscapeModel::ObjectState::Enum _state
	,	const Core::LandscapeModel::Direction::Enum _direction )
{
	QString animationName
		= generateAnimationName( _skinId, _typeName, _state, _direction );

	if ( m_environment.hasAnimation( animationName ) )
	{
		m_environment.playAnimation( _animateObject, animationName );
	}
	else
	{
		playAnimation( _animateObject, IGraphicsInfoCache::ms_anySkinIdentifier, _typeName, _state, _direction );
	}

} // LandscapeScene::playAnimation


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
