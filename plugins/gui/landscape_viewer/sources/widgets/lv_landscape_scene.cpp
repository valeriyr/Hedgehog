
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/widgets/landscape_scene_states/lv_landscape_scene_states.hpp"
#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"
#include "landscape_viewer/sources/graphics_info/lv_igraphics_info.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"
#include "settings/h/st_events.hpp"

#include "lv_landscape_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


ObjectGraphicsItem::ObjectGraphicsItem(
		const QPixmap& _pixmap
	,	const IEnvironment& _environment
	,	const LandscapeScene& _landscapeScene
	,	const QString& _objectName
	,	const Tools::Core::Generators::IGenerator::IdType& _objectId
	,	QGraphicsItem* _parent
	)
	:	QGraphicsPixmapItem( _pixmap, _parent )
	,	m_environment( _environment )
	,	m_landscapeScene( _landscapeScene )
	,	m_objectName( _objectName )
	,	m_objectId( _objectId )
{
	setFlag( ItemSendsGeometryChanges, true );
	correctedPosition();

} // ObjectGraphicsItem::ObjectGraphicsItem


/*---------------------------------------------------------------------------*/


void
ObjectGraphicsItem::setSprite( const QPixmap& _sprite )
{
	bool needToCorrectPosition = _sprite.size() != pixmap().size();

	setPixmap( _sprite );

	if ( needToCorrectPosition )
		correctedPosition();

} // ObjectGraphicsItem::setSprite


/*---------------------------------------------------------------------------*/


QVariant
ObjectGraphicsItem::itemChange( GraphicsItemChange _change, const QVariant& value )
{
	if ( _change == ItemPositionHasChanged )
	{
		boost::shared_ptr<Core::LandscapeModel::ILocateComponent::StaticData >
			locateComponentStaticData = m_environment.getObjectStaticData( m_objectName ).m_locateData;

		QPoint position( value.toPoint() );

		int centerX = position.x() + ( boundingRect().size().width() / 2 );
		int centerY = position.y() + ( boundingRect().size().height() / 2 );

		QSize landscapeSize( m_landscapeScene.calculateLandscapeSize() );

		int z = LandscapeScene::ZValue::ObjectsBegin;
		z += ( ( centerY / Resources::Landscape::CellSize ) * landscapeSize.height() ) + ( ( centerX / Resources::Landscape::CellSize ) + 1 );

		if ( locateComponentStaticData->m_emplacement == Core::LandscapeModel::Emplacement::Air )
			z += landscapeSize.width() * landscapeSize.height();

		setZValue( z );
	}

	return QGraphicsPixmapItem::itemChange( _change, value );

} // ObjectGraphicsItem::itemChange


/*---------------------------------------------------------------------------*/


const Tools::Core::Generators::IGenerator::IdType&
ObjectGraphicsItem::getObjectId() const
{
	return m_objectId;

} // ObjectGraphicsItem::getObjectId


/*---------------------------------------------------------------------------*/


void
ObjectGraphicsItem::correctedPosition()
{
	setPos(
		LandscapeScene::correctSceneObjectPosition(
				m_environment
			,	m_landscapeScene.width()
			,	m_landscapeScene.height()
			,	LandscapeScene::convertToScenePosition(
					m_environment.lockModel()->getLandscapeModel()->getLandscape()->getObject( m_objectId )
						->getComponent< Core::LandscapeModel::ILocateComponent >( Core::LandscapeModel::ComponentId::Locate )->getLocation() )
			,	m_objectName
			,	pixmap() ) );

} // ObjectGraphicsItem::correctedPosition


/*---------------------------------------------------------------------------*/
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
							,	Plugins::Core::LandscapeModel::Events::BuilderHasStartedBuild::ms_type
							,	boost::bind( &LandscapeScene::onBuilderHasStartedBuild, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::BuilderHasFinishedBuild::ms_type
							,	boost::bind( &LandscapeScene::onBuilderHasFinishedBuild, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::HolderHasStartedCollect::ms_type
							,	boost::bind( &LandscapeScene::onHolderHasStartedCollect, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::HolderHasStopCollect::ms_type
							,	boost::bind( &LandscapeScene::onHolderHasStopCollect, this, _1 ) );

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


ObjectGraphicsItem*
LandscapeScene::getObjectGraphicsItem( const Tools::Core::Generators::IGenerator::IdType& _objectId ) const
{
	ObjectsCollectionConstIterator iterator = m_objectsCollection.find( _objectId );
	return iterator != m_objectsCollection.end() ? iterator->second : NULL;

} // LandscapeScene::getObjectGraphicsItem


/*---------------------------------------------------------------------------*/


ObjectGraphicsItem*
LandscapeScene::getObjectGraphicsItem( const QPointF& _scenePosition ) const
{
	ObjectsCollectionConstIterator
			objectsBegin = m_objectsCollection.begin()
		,	objectsEnd = m_objectsCollection.end();

	for ( ; objectsBegin != objectsEnd; ++objectsBegin )
	{
		if ( objectsBegin->second->sceneBoundingRect().contains( _scenePosition ) )
			return objectsBegin->second;
	}

	return NULL;

} // LandscapeScene::getObjectGraphicsItem


/*---------------------------------------------------------------------------*/


QSize
LandscapeScene::calculateLandscapeSize() const
{
	return QSize( width() / Resources::Landscape::CellSize, height() / Resources::Landscape::CellSize );

} // LandscapeScene::calculateLandscapeSize


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onChangeSurfaceItem( const Tools::Core::Generators::IGenerator::IdType& _id )
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
LandscapeScene::onBuildObjectButtonPressed( const Tools::Core::Generators::IGenerator::IdType _builderId, const QString& _objectName )
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
	const Tools::Core::Generators::IGenerator::IdType id
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
	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectRemoved::ms_objectUniqueIdAttribute ).toInt();

	removeObject( id );

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
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle = m_environment.lockModel();

	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_surfaceItemIdAttribute ).toUInt();
	const QPoint location
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::SurfaceItemChanged::ms_surfaceItemLocationAttribute ).toPoint();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		QPointF scenePosition( LandscapeScene::convertToScenePosition( location ) );

		QList< QGraphicsItem* > itemsList = items( scenePosition, Qt::ContainsItemShape, Qt::AscendingOrder );

		if ( itemsList.isEmpty() )
			return;

		QPointF itemPos = itemsList[LandscapeScene::ZValue::Surface]->scenePos();
		delete itemsList[LandscapeScene::ZValue::Surface];

		boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
			surfaceItemGraphicsInfo = m_environment.getGraphicsInfo()
				->getSurfaceItemGraphicsInfo( m_environment.getString( Resources::Properties::SkinId ), id );

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
	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_objectIdAttribute ).toInt();
	const QPoint movedFrom
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_movingFromAttribute ).toPoint();
	const QPoint movedTo
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_movingToAttribute ).toPoint();
	const Core::LandscapeModel::TickType progress
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_movingProgressAttribute ).toLongLong();
	const Core::LandscapeModel::TickType movingSpeed
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_movingSpeedAttribute ).toLongLong();

	ObjectGraphicsItem* graphicsItem = getObjectGraphicsItem( id );
	assert( graphicsItem );

	const QPointF movedFromInScene( LandscapeScene::convertToScenePosition( movedFrom ) );
	const QPointF movedToInScene( LandscapeScene::convertToScenePosition( movedTo ) );

	QPointF correctedPosition(
		LandscapeScene::correctSceneObjectPosition(
				m_environment
			,	width()
			,	height()
			,	QPoint(
						movedFromInScene.x() + ( ( movedToInScene.x() - movedFromInScene.x() ) * ( static_cast< float >( progress ) / movingSpeed ) )
					,	movedFromInScene.y() + ( ( movedToInScene.y() - movedFromInScene.y() ) * ( static_cast< float >( progress ) / movingSpeed ) ) )
			,	name ) );

	graphicsItem->setPos( correctedPosition );

	regenerateTerrainMapLayer();

} // LandscapeScene::onObjectMoved


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onObjectStateChanged( const Framework::Core::EventManager::Event& _event )
{
	const QString name
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectNameAttribute ).toString();
	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectIdAttribute ).toInt();
	const Plugins::Core::LandscapeModel::ObjectState::Enum state
		= static_cast< Plugins::Core::LandscapeModel::ObjectState::Enum >(
			_event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectState ).toInt() );
	const Plugins::Core::LandscapeModel::Direction::Enum direction
		= static_cast< Plugins::Core::LandscapeModel::Direction::Enum >(
			_event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectDirection ).toInt() );

	ObjectGraphicsItem* graphicsItem = getObjectGraphicsItem( id );

	if ( !graphicsItem )
		return;

	if (	state == Plugins::Core::LandscapeModel::ObjectState::Dying
		||	state == Plugins::Core::LandscapeModel::ObjectState::Standing )
	{
		playAnimationOnce(
				*graphicsItem
			,	m_environment.getString( Resources::Properties::SkinId )
			,	name
			,	state
			,	direction );
	}
	else if ( state != Plugins::Core::LandscapeModel::ObjectState::Attacking )
	{
		playAnimation(
				*graphicsItem
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
	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectIdAttribute ).toInt();
	const Plugins::Core::LandscapeModel::Direction::Enum direction
		= static_cast< Plugins::Core::LandscapeModel::Direction::Enum >(
			_event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectStateChanged::ms_objectDirection ).toInt() );

	ObjectGraphicsItem* graphicsItem = getObjectGraphicsItem( id );
	assert( graphicsItem );

	playAnimationOnce(
			*graphicsItem
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
	const Tools::Core::Generators::IGenerator::IdType id
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
LandscapeScene::onBuilderHasStartedBuild( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::BuilderHasStartedBuild::ms_objectUniqueIdAttribute ).toInt();

	removeObject( id );

} // LandscapeScene::onBuilderHasStartedBuild


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onBuilderHasFinishedBuild( const Framework::Core::EventManager::Event& _event )
{
	const QString objectName = _event.getAttribute( Plugins::Core::LandscapeModel::Events::BuilderHasFinishedBuild::ms_objectNameAttribute ).toString();
	const QPoint objectLocation = _event.getAttribute( Plugins::Core::LandscapeModel::Events::BuilderHasFinishedBuild::ms_objectLocationAttribute ).toPoint();
	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::BuilderHasFinishedBuild::ms_objectUniqueIdAttribute ).toInt();
	const Core::LandscapeModel::Emplacement::Enum emplacement
		= static_cast< Core::LandscapeModel::Emplacement::Enum >( _event.getAttribute( Plugins::Core::LandscapeModel::Events::BuilderHasFinishedBuild::ms_objectEmplacementAttribute ).toInt() );

	playAnimationOnce(
			*addObject( objectName, objectLocation, id, emplacement )
		,	m_environment.getString( Resources::Properties::SkinId )
		,	objectName
		,	Core::LandscapeModel::ObjectState::Standing
		,	Core::LandscapeModel::Direction::South );

} // LandscapeScene::onBuilderHasFinishedBuild


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onHolderHasStartedCollect( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::HolderHasStartedCollect::ms_objectUniqueIdAttribute ).toInt();

	removeObject( id );

} // LandscapeScene::onHolderHasStartedCollect


/*---------------------------------------------------------------------------*/


void
LandscapeScene::onHolderHasStopCollect( const Framework::Core::EventManager::Event& _event )
{
	const QString objectName = _event.getAttribute( Plugins::Core::LandscapeModel::Events::HolderHasStopCollect::ms_objectNameAttribute ).toString();
	const QPoint objectLocation = _event.getAttribute( Plugins::Core::LandscapeModel::Events::HolderHasStopCollect::ms_objectLocationAttribute ).toPoint();
	const Tools::Core::Generators::IGenerator::IdType id
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::HolderHasStopCollect::ms_objectUniqueIdAttribute ).toInt();
	const Core::LandscapeModel::Emplacement::Enum emplacement
		= static_cast< Core::LandscapeModel::Emplacement::Enum >( _event.getAttribute( Plugins::Core::LandscapeModel::Events::HolderHasStopCollect::ms_objectEmplacementAttribute ).toInt() );

	playAnimationOnce(
			*addObject( objectName, objectLocation, id, emplacement )
		,	m_environment.getString( Resources::Properties::SkinId )
		,	objectName
		,	Core::LandscapeModel::ObjectState::Standing
		,	Core::LandscapeModel::Direction::South );

} // LandscapeScene::onHolderHasStopCollect


/*---------------------------------------------------------------------------*/


void
LandscapeScene::generateLandscape()
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		for ( int i = 0; i < handle->getLandscapeModel()->getLandscape()->getWidth(); ++i )
		{
			for ( int j = 0; j < handle->getLandscapeModel()->getLandscape()->getHeight(); ++j )
			{
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
					surfaceItem = handle->getLandscapeModel()->getLandscape()->getSurfaceItem( QPoint( i, j ) );

				boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
					surfaceItemGraphicsInfo = m_environment.getGraphicsInfo()->getSurfaceItemGraphicsInfo(
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
		handle->getLandscapeModel()->getLandscape()->fetchObjects( objectsCollection );

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollectionIterator
				begin = objectsCollection.begin()
			,	end = objectsCollection.end();

		for ( ; begin != end; ++begin )
		{
			boost::intrusive_ptr<Core::LandscapeModel::ILocateComponent >
				locateComponent = ( *begin )->getComponent< Core::LandscapeModel::ILocateComponent >( Core::LandscapeModel::ComponentId::Locate );

			ObjectGraphicsItem* newItem
				= new ObjectGraphicsItem(
						m_environment.getPixmap( ( *begin )->getName() )
					,	m_environment
					,	*this
					,	( *begin )->getName()
					,	( *begin )->getUniqueId() );
			addItem( newItem );

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
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		for ( int i = 0; i < handle->getLandscapeModel()->getLandscape()->getWidth(); ++i )
		{
			for ( int j = 0; j < handle->getLandscapeModel()->getLandscape()->getHeight(); ++j )
			{
				Plugins::Core::LandscapeModel::TerrainMapData
					terrainMapData = handle->getLandscapeModel()->getLandscape()->getTerrainMapData( QPoint( i, j ) );

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
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		setSceneRect(
				0
			,	0
			,	handle->getLandscapeModel()->getLandscape()->getWidth() * Resources::Landscape::CellSize
			,	handle->getLandscapeModel()->getLandscape()->getHeight() * Resources::Landscape::CellSize );
	}
	else
	{
		setSceneRect( 0, 0, 0, 0 );
	}

} // LandscapeScene::setCorrectSceneSize


/*---------------------------------------------------------------------------*/


void
LandscapeScene::objectWasAdded( const Tools::Core::Generators::IGenerator::IdType& _id, ObjectGraphicsItem* _item )
{
	assert( !getObjectGraphicsItem( _id ) );
	m_objectsCollection.insert( std::make_pair( _id, _item ) );

} // LandscapeScene::objectWasAdded


/*---------------------------------------------------------------------------*/


ObjectGraphicsItem*
LandscapeScene::addObject(
		const QString& _objectName
	,	const QPoint& _objectLocation
	,	const Tools::Core::Generators::IGenerator::IdType _id
	,	const Core::LandscapeModel::Emplacement::Enum _emplacement )
{
	ObjectGraphicsItem* newItem
		= new ObjectGraphicsItem(
				m_environment.getPixmap( _objectName )
			,	m_environment
			,	*this
			,	_objectName
			,	_id );
	addItem( newItem );

	objectWasAdded( _id, newItem );

	regenerateTerrainMapLayer();

	return newItem;

} // LandscapeScene::addObject


/*---------------------------------------------------------------------------*/


void
LandscapeScene::markSelectedObjects()
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		ObjectsCollectionIterator
				objectsBegin = m_objectsCollection.begin()
			,	objectsEnd = m_objectsCollection.end();

		for ( ; objectsBegin != objectsEnd; ++objectsBegin )
		{
			objectsBegin->second->setGraphicsEffect( NULL );
		}

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
		handle->getLandscapeModel()->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollectionIterator
				selectedObjectsBegin = selectedObjectsCollection.begin()
			,	selectedObjectsEnd = selectedObjectsCollection.end();

		for ( ; selectedObjectsBegin != selectedObjectsEnd; ++selectedObjectsBegin )
		{
			ObjectGraphicsItem* graphicsItem = getObjectGraphicsItem( ( *selectedObjectsBegin )->getUniqueId() );
			assert( graphicsItem );

			graphicsItem->setGraphicsEffect( new QGraphicsColorizeEffect() );
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
	return correctSceneObjectPosition( _environment, _sceneWidth, _sceneHeight, _roundedPosition, _objectName, _environment.getPixmap( _objectName ) );

} // LandscapeScene::correctSceneObjectPosition


/*---------------------------------------------------------------------------*/


QPointF
LandscapeScene::correctSceneObjectPosition(
		const IEnvironment& _environment
	,	const int _sceneWidth
	,	const int _sceneHeight
	,	const QPointF& _roundedPosition
	,	const QString& _objectName
	,	const QPixmap& _objectPixmap )
{
	QPoint correctedPosition( _roundedPosition.x(), _roundedPosition.y() );

	Core::LandscapeModel::IStaticData::ObjectStaticData objectStaticData
		= _environment.getObjectStaticData( _objectName );

	if ( correctedPosition.x() > _sceneWidth - ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) )
		correctedPosition.setX( _sceneWidth - ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) );

	if ( correctedPosition.y() > _sceneHeight - ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) )
		correctedPosition.setY( _sceneHeight - ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) );

	correctedPosition.setX( correctedPosition.x() - ( _objectPixmap.width() - ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) ) / 2 );
	correctedPosition.setY( correctedPosition.y() - ( _objectPixmap.height() - ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) ) / 2 );

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
		playAnimation( _animateObject, IGraphicsInfo::ms_anySkinIdentifier, _typeName, _state, _direction );
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
		playAnimationOnce( _animateObject, IGraphicsInfo::ms_anySkinIdentifier, _typeName, _state, _direction );
	}

} // LandscapeScene::playAnimationOnce


/*---------------------------------------------------------------------------*/


void
LandscapeScene::removeObject( const Tools::Core::Generators::IGenerator::IdType _id )
{
	ObjectsCollectionIterator iterator = m_objectsCollection.find( _id );

	if ( iterator != m_objectsCollection.end() )
	{
		m_environment.stopAnimation( *iterator->second );

		delete iterator->second;

		m_objectsCollection.erase( _id );

		regenerateTerrainMapLayer();
	}

} // LandscapeScene::removeObject


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
