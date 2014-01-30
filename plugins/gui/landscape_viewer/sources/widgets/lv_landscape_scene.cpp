
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

#include "landscape_model/ih/components/lm_ilocate_component.hpp"

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

	ObjectGraphicsItem(
			const QPixmap& _pixmap
		,	const Core::LandscapeModel::Emplacement::Enum _emplacement
		,	const QSize& _landscapeSize
		,	QGraphicsItem* _parent = NULL
		)
		:	QGraphicsPixmapItem( _pixmap, _parent )
		,	m_emplacement( _emplacement )
		,	m_landscapeSize( _landscapeSize )
	{
		setFlag( ItemSendsGeometryChanges, true );
	}

	/*virtual*/ void setSprite( const QPixmap& _sprite )
	{
		setPixmap( _sprite );
	}

	/*virtual*/ QVariant itemChange( GraphicsItemChange _change, const QVariant& value )
	{
		if ( _change == ItemPositionHasChanged )
		{
			QPoint position( value.toPoint() );

			int centerX = position.x() + ( boundingRect().size().width() / 2 );
			int centerY = position.y() + ( boundingRect().size().height() / 2 );

			int z = LandscapeScene::ZValue::ObjectsBegin;
			z += ( ( centerY / Resources::Landscape::CellSize ) * m_landscapeSize.height() ) + ( ( centerX / Resources::Landscape::CellSize ) + 1 );

			if ( m_emplacement == Core::LandscapeModel::Emplacement::Air )
				z += m_landscapeSize.width() * m_landscapeSize.height();

			setZValue( z );
		}

		return QGraphicsPixmapItem::itemChange( _change, value );
	}

private:

	const Core::LandscapeModel::Emplacement::Enum m_emplacement;

	const QSize m_landscapeSize;

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
							,	Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_type
							,	boost::bind( &LandscapeScene::onObjectAdded, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectRemoved::ms_type
							,	boost::bind( &LandscapeScene::onObjectRemoved, this, _1 ) );

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

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectWasHit::ms_type
							,	boost::bind( &LandscapeScene::onObjectWasHit, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectReadyToAttack::ms_type
							,	boost::bind( &LandscapeScene::onObjectReadyToAttack, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectStartBuilding::ms_type
							,	boost::bind( &LandscapeScene::onObjectStartBuilding, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::BuilderHasFinishedBuild::ms_type
							,	boost::bind( &LandscapeScene::onBuilderHasFinishedBuild, this, _1 ) );

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


void
LandscapeScene::onBuildObjectButtonPressed( const Plugins::Core::LandscapeModel::Object::UniqueId _builderId, const QString& _objectName )
{
	m_landscapeSceneState.reset( new LandscapeObjectBuildState( m_environment, *this, _builderId, _objectName ) );

} // LandscapeScene::onBuildObjectButtonPressed


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
LandscapeScene::onObjectAdded( const Framework::Core::EventManager::Event& _event )
{
	const QString objectName = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectNameAttribute ).toString();
	const QPoint objectLocation = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectLocationAttribute ).toPoint();
	const Plugins::Core::LandscapeModel::Object::UniqueId id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectUniqueIdAttribute ).toInt();
	const Core::LandscapeModel::Emplacement::Enum emplacement
		= static_cast< Core::LandscapeModel::Emplacement::Enum >( _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectEmplacementAttribute ).toInt() );

	playAnimationOnce(
			*addObject( objectName, objectLocation, id, emplacement )
		,	m_environment.getString( Resources::Properties::SkinId )
		,	objectName
		,	Core::LandscapeModel::ObjectState::Standing
		,	Core::LandscapeModel::Direction::South );

	m_environment.playSound( Resources::Sounds::PlacementSuccess );

} // LandscapeScene::onObjectAdded


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectRemoved( const Framework::Core::EventManager::Event& _event )
{
	const Plugins::Core::LandscapeModel::Object::UniqueId id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectRemoved::ms_objectUniqueIdAttribute ).toInt();

	ObjectsCollectionIterator iterator = m_objectsCollection.find( id );

	if ( iterator != m_objectsCollection.end() )
	{
		m_environment.stopAnimation( *iterator->second );

		delete iterator->second;

		m_objectsCollection.erase( id );
	}

} // LandscapeScene::onObjectRemoved


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

		QPointF itemPos = itemsList[LandscapeScene::ZValue::Surface]->scenePos();
		delete itemsList[LandscapeScene::ZValue::Surface];

		boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
			surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( m_environment.getString( Resources::Properties::SkinId ), id );

		QGraphicsPixmapItem* newItem
			= addPixmap( m_environment.getPixmap(
					surfaceItemGraphicsInfo->getAtlasName()
				,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( surfaceItemGraphicsInfo->getFrameRect() ) ) );

		newItem->setPos( itemPos );
		newItem->setZValue( LandscapeScene::ZValue::Surface );
	}

	regenerateTerrainMapLayer();

	m_environment.playSound( Resources::Sounds::PlacementSuccess );

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

	if (	state == Plugins::Core::LandscapeModel::ObjectState::Dying
		||	state == Plugins::Core::LandscapeModel::ObjectState::Standing )
	{
		playAnimationOnce(
				*iterator->second
			,	m_environment.getString( Resources::Properties::SkinId )
			,	name
			,	state
			,	direction );
	}
	else if ( state != Plugins::Core::LandscapeModel::ObjectState::Attacking )
	{
		playAnimation(
				*iterator->second
			,	m_environment.getString( Resources::Properties::SkinId )
			,	name
			,	state
			,	direction );
	}

} // LandscapeScene::onObjectStateChanged


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectWasHit( const Framework::Core::EventManager::Event& _event )
{
	m_environment.playSound( "missiles/fist" );

} // LandscapeScene::onObjectWasHit


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectReadyToAttack( const Framework::Core::EventManager::Event& _event )
{
	const QString name
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectNameAttribute ).toString();
	const Plugins::Core::LandscapeModel::Object::UniqueId id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectIdAttribute ).toInt();
	const Plugins::Core::LandscapeModel::Direction::Enum direction
		= static_cast< Plugins::Core::LandscapeModel::Direction::Enum >(
			_event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectDirection ).toInt() );

	ObjectsCollectionIterator iterator = m_objectsCollection.find( id );
	assert( iterator != m_objectsCollection.end() );

	playAnimationOnce(
			*iterator->second
		,	m_environment.getString( Resources::Properties::SkinId )
		,	name
		,	Core::LandscapeModel::ObjectState::Attacking
		,	direction );

} // LandscapeScene::onObjectReadyToAttack


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectStartBuilding( const Framework::Core::EventManager::Event& _event )
{
	const QString objectName = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectNameAttribute ).toString();
	const QPoint objectLocation = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectLocationAttribute ).toPoint();
	const Plugins::Core::LandscapeModel::Object::UniqueId id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectUniqueIdAttribute ).toInt();
	const Core::LandscapeModel::Emplacement::Enum emplacement
		= static_cast< Core::LandscapeModel::Emplacement::Enum >( _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectEmplacementAttribute ).toInt() );

	playAnimationOnce(
			*addObject( objectName, objectLocation, id, emplacement )
		,	m_environment.getString( Resources::Properties::SkinId )
		,	objectName
		,	Core::LandscapeModel::ObjectState::UnderConstruction
		,	Core::LandscapeModel::Direction::South );

} // LandscapeScene::onObjectStartBuilding


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onBuilderHasFinishedBuild( const Framework::Core::EventManager::Event& _event )
{
	const QString objectName = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectNameAttribute ).toString();
	const QPoint objectLocation = _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectLocationAttribute ).toPoint();
	const Plugins::Core::LandscapeModel::Object::UniqueId id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectUniqueIdAttribute ).toInt();
	const Core::LandscapeModel::Emplacement::Enum emplacement
		= static_cast< Core::LandscapeModel::Emplacement::Enum >( _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectAdded::ms_objectEmplacementAttribute ).toInt() );

	playAnimationOnce(
			*addObject( objectName, objectLocation, id, emplacement )
		,	m_environment.getString( Resources::Properties::SkinId )
		,	objectName
		,	Core::LandscapeModel::ObjectState::Standing
		,	Core::LandscapeModel::Direction::South );

} // LandscapeScene::onBuilderHasFinishedBuild


/*---------------------------------------------------------------------------*/


void
LandscapeScene::generateLandscape()
{
	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		for ( int i = 0; i < handle->getLandscape()->getWidth(); ++i )
		{
			for ( int j = 0; j < handle->getLandscape()->getHeight(); ++j )
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
				item->setZValue( ZValue::Surface );
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
				= new ObjectGraphicsItem(
						m_environment.getPixmap( ( *begin )->getName() )
					,	( *begin )->getComponent< Core::LandscapeModel::ILocateComponent >( Core::LandscapeModel::ComponentId::Locate )->getStaticData().m_emplacement
					,	QSize( handle->getLandscape()->getWidth(), handle->getLandscape()->getHeight() ) );
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

			objectWasAdded( ( *begin )->getUniqueId(), newItem );

			playAnimationOnce(
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
		for ( int i = 0; i < handle->getLandscape()->getWidth(); ++i )
		{
			for ( int j = 0; j < handle->getLandscape()->getHeight(); ++j )
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
				item->setZValue( ZValue::Terrain );

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
		if ( items[ i ]->zValue() == ZValue::Terrain )
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


ObjectGraphicsItem*
LandscapeScene::addObject(
		const QString& _objectName
	,	const QPoint& _objectLocation
	,	const Plugins::Core::LandscapeModel::Object::UniqueId _id
	,	const Core::LandscapeModel::Emplacement::Enum _emplacement )
{
	QPointF correctedPosition(
		LandscapeScene::correctSceneObjectPosition(
				m_environment
			,	width()
			,	height()
			,	LandscapeScene::convertToScenePosition( _objectLocation )
			,	_objectName ) );

	ObjectGraphicsItem* newItem = new ObjectGraphicsItem( m_environment.getPixmap( _objectName ), _emplacement, calculateLandscapeSize() );
	addItem( newItem );

	newItem->setPos( correctedPosition );

	objectWasAdded( _id, newItem );

	regenerateTerrainMapLayer();

	return newItem;

} // LandscapeScene::addObject


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

	correctedPosition.setX( correctedPosition.x() - ( objectPixmap.width() - ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) ) / 2 );
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


void
LandscapeScene::playAnimationOnce(
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
		m_environment.playAnimationOnce( _animateObject, animationName );
	}
	else
	{
		playAnimationOnce( _animateObject, IGraphicsInfoCache::ms_anySkinIdentifier, _typeName, _state, _direction );
	}

} // LandscapeScene::playAnimationOnce


/*---------------------------------------------------------------------------*/


QSize
LandscapeScene::calculateLandscapeSize() const
{
	return QSize( width() / Resources::Landscape::CellSize, height() / Resources::Landscape::CellSize );

} // LandscapeScene::calculateLandscapeSize


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
