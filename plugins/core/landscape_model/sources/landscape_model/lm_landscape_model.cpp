
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/player/lm_player.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"
#include "landscape_model/sources/model_locker/lm_model_locker.hpp"
#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/sources/actions/lm_generate_resources_action.hpp"
#include "landscape_model/sources/actions/lm_move_action.hpp"
#include "landscape_model/sources/actions/lm_attack_action.hpp"
#include "landscape_model/sources/actions/lm_train_action.hpp"
#include "landscape_model/sources/actions/lm_build_action.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/sources/notification_center/lm_inotification_center.hpp"

#include "landscape_model/sources/components/lm_train_component.hpp"
#include "landscape_model/sources/components/lm_health_component.hpp"
#include "landscape_model/sources/components/lm_locate_component.hpp"
#include "landscape_model/sources/components/lm_selection_component.hpp"
#include "landscape_model/sources/components/lm_actions_component.hpp"
#include "landscape_model/sources/components/lm_move_component.hpp"
#include "landscape_model/sources/components/lm_generate_resources_component.hpp"
#include "landscape_model/sources/components/lm_attack_component.hpp"
#include "landscape_model/sources/components/lm_build_component.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/h/lm_resources.hpp"
#include "landscape_model/h/lm_events.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


LandscapeModel::LandscapeModel(
		const IEnvironment& _environment
	,	const ILandscapeSerializer& _landscapeSerializer
	,	const ISurfaceItemsCache& _surfaceItemsCache
	,	const IStaticData& _staticData
	)
	:	m_environment( _environment )
	,	m_landscapeSerializer( _landscapeSerializer )
	,	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_staticData( _staticData )
	,	m_currentLandscape()
	,	m_player()
	,	m_mutex( QMutex::Recursive )
	,	m_builders()
{
	m_environment.startThread( Resources::ModelThreadName );
	m_actionsProcessingTaskHandle = m_environment.pushPeriodicalTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::gameMainLoop, this )
		,	Resources::TimeLimit );

} // LandscapeModel::LandscapeModel


/*---------------------------------------------------------------------------*/


LandscapeModel::~LandscapeModel()
{
	m_environment.removeTask( m_actionsProcessingTaskHandle );
	m_environment.stopThread( Resources::ModelThreadName );

} // LandscapeModel::~LandscapeModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initModel( const QString& _filePath )
{
	m_environment.pushTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::initTask, this, _filePath ) );

} // LandscapeModel::initModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::resetModel()
{
	m_environment.pushTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::resetTask, this ) );

} // LandscapeModel::resetModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::saveModel( const QString& _filePath )
{
	m_environment.pushTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::saveTask, this, _filePath ) );

} // LandscapeModel::saveModel


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IModelLocker >
LandscapeModel::lockModel()
{
	return boost::intrusive_ptr< IModelLocker >( new ModelLocker( m_currentLandscape, m_player, m_mutex ) );

} // LandscapeModel::lockModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectObjects( const QRect& _rect )
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	if ( handle->getLandscape() )
	{
		handle->getLandscape()->selectObjects( _rect );

		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );
	}

} // LandscapeModel::selectObjects


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectObject( const Object::Id& _id )
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	if ( handle->getLandscape() )
	{
		handle->getLandscape()->selectObject( _id );

		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );
	}

} // LandscapeModel::selectObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::sendSelectedObjects( const QPoint& _to, const bool _flush )
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	if ( handle->getLandscape() )
	{
		ILandscape::ObjectsCollection selectedObjects;
		handle->getLandscape()->fetchSelectedObjects( selectedObjects );

		ILandscape::ObjectsCollectionIterator
				begin = selectedObjects.begin()
			,	end = selectedObjects.end();

		for ( ; begin != end; ++begin )
		{
			boost::shared_ptr< Object > targetObject = handle->getLandscape()->getObject( _to );

			boost::intrusive_ptr< IActionsComponent > actionsComponent
				= ( *begin )->getComponent< IActionsComponent >( ComponentId::Actions );
			boost::intrusive_ptr< IMoveComponent > moveComponent
				= ( *begin )->getComponent< IMoveComponent >( ComponentId::Move );
			boost::intrusive_ptr< IAttackComponent > attackComponent
				= ( *begin )->getComponent< IAttackComponent >( ComponentId::Attack );

			if ( targetObject )
			{
				if ( targetObject != *begin && attackComponent )
				{
					actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >( new AttackAction( m_environment, *this, **begin, targetObject ) )
						,	_flush );
				}
			}
			else if ( moveComponent )
			{
				actionsComponent->pushAction(
						boost::intrusive_ptr< IAction >( new MoveAction( m_environment, *this, **begin, _to ) )
					,	_flush );
			}
		}
	}

} // LandscapeModel::sendSelectedObjects


/*---------------------------------------------------------------------------*/


void
LandscapeModel::createObject( const QPoint& _location, const QString& _objectName )
{
	Object::Id objectId = Object::ms_wrongId;

	{
		boost::intrusive_ptr< IModelLocker > handle( lockModel() );

		if ( handle->getLandscape() )
		{
			objectId = handle->getLandscape()->createObject( _location, _objectName );
		}
	}

	if ( objectId != Object::ms_wrongId )
	{
		Framework::Core::EventManager::Event objectAddedEvent( Events::ObjectAdded::ms_type );
		objectAddedEvent.pushAttribute( Events::ObjectAdded::ms_objectNameAttribute, _objectName );
		objectAddedEvent.pushAttribute( Events::ObjectAdded::ms_objectLocationAttribute, _location );
		objectAddedEvent.pushAttribute( Events::ObjectAdded::ms_objectUniqueIdAttribute, objectId );
		objectAddedEvent.pushAttribute( Events::ObjectAdded::ms_objectEmplacementAttribute, m_staticData.getObjectStaticData( _objectName ).m_locateData->m_emplacement );

		m_environment.riseEvent( objectAddedEvent );
	}
	else
	{
		Framework::Core::EventManager::Event createObjectFailedEvent( Events::CreateObjectFailed::ms_type );
		createObjectFailedEvent.pushAttribute( Events::CreateObjectFailed::ms_objectNameAttribute, _objectName );
		createObjectFailedEvent.pushAttribute( Events::CreateObjectFailed::ms_objectLocationAttribute, _location );

		m_environment.riseEvent( createObjectFailedEvent );
	}

} // LandscapeModel::createObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::setSurfaceItem(
		const QPoint& _location
	,	const Core::LandscapeModel::ISurfaceItem::Id& _id )
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	if ( handle->getLandscape() )
	{
		handle->getLandscape()->setSurfaceItem( _location, _id );

		Framework::Core::EventManager::Event surfaceItemChangedEvent( Events::SurfaceItemChanged::ms_type );
		surfaceItemChangedEvent.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemIdAttribute, _id );
		surfaceItemChangedEvent.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemLocationAttribute, _location );

		m_environment.riseEvent( surfaceItemChangedEvent );
	}

} // LandscapeModel::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeModel::trainObject( const Object::Id& _parentObject, const QString& _objectName )
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	boost::shared_ptr< Object > object = handle->getLandscape()->getObject( _parentObject );

	if ( object )
	{
		boost::intrusive_ptr< IActionsComponent > actionsComponent
			= object->getComponent< IActionsComponent >( ComponentId::Actions );

		actionsComponent->pushAction(
			boost::intrusive_ptr< IAction >( new TrainAction( m_environment, *this, *object, _objectName ) ), false );
	}

} // LandscapeModel::trainObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::buildObject( const Object::Id& _builder, const QString& _objectName, const QPoint& _atLocation )
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	boost::shared_ptr< Object > object = handle->getLandscape()->getObject( _builder );

	if ( object )
	{
		boost::intrusive_ptr< IActionsComponent > actionsComponent
			= object->getComponent< IActionsComponent >( ComponentId::Actions );

		actionsComponent->pushAction(
			boost::intrusive_ptr< IAction >( new BuildAction( m_environment, *this, *object, _objectName, _atLocation ) ), true );
	}

} // LandscapeModel::buildObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::startBuild(
		const Object::Id& _id
	,	const QString& _objectName
	,	const QPoint& _location )
{
	{
		boost::intrusive_ptr< IModelLocker > handle( lockModel() );

		if ( handle->getLandscape() )
		{
			boost::shared_ptr< Object > object = handle->getLandscape()->removeObject( _id );

			if ( object )
			{
				object->setState( ObjectState::Building );

				assert( m_builders.find( _id ) == m_builders.end() );
				m_builders.insert( std::make_pair( _id, object ) );

				const Object::Id objectId
					= handle->getLandscape()->createObjectForBuilding( _location, _objectName );
				assert( objectId != Object::ms_wrongId );

				boost::intrusive_ptr< IBuildComponent > buildComponent
					= object->getComponent< IBuildComponent >( ComponentId::Build );
				buildComponent->getBuildData().m_objectId = objectId;

				Framework::Core::EventManager::Event objectRemovedEvent( Events::ObjectRemoved::ms_type );
				objectRemovedEvent.pushAttribute( Events::ObjectRemoved::ms_objectUniqueIdAttribute, _id );

				m_environment.riseEvent( objectRemovedEvent );

				Framework::Core::EventManager::Event objectStartBuildingEvent( Events::ObjectStartBuilding::ms_type );
				objectStartBuildingEvent.pushAttribute( Events::ObjectAdded::ms_objectNameAttribute, _objectName );
				objectStartBuildingEvent.pushAttribute( Events::ObjectAdded::ms_objectLocationAttribute, _location );
				objectStartBuildingEvent.pushAttribute( Events::ObjectAdded::ms_objectUniqueIdAttribute, objectId );
				objectStartBuildingEvent.pushAttribute( Events::ObjectAdded::ms_objectEmplacementAttribute, m_staticData.getObjectStaticData( _objectName ).m_locateData->m_emplacement );

				m_environment.riseEvent( objectStartBuildingEvent );
			}
		}
	}

} // LandscapeModel::startBuild


/*---------------------------------------------------------------------------*/


void
LandscapeModel::stopBuild( const Object::Id& _id )
{
	{
		boost::intrusive_ptr< IModelLocker > handle( lockModel() );

		if ( handle->getLandscape() )
		{
			BuildersCollectionIterator iterator = m_builders.find( _id );

			assert( iterator != m_builders.end() );

			boost::intrusive_ptr< ILocateComponent >
				locateComponent = iterator->second->getComponent< ILocateComponent >( ComponentId::Locate );
			boost::intrusive_ptr< IBuildComponent >
				buildComponent = iterator->second->getComponent< IBuildComponent >( ComponentId::Build );

			boost::shared_ptr< Object > targetObject
				= handle->getLandscape()->getObject( buildComponent->getBuildData().m_objectId );
			targetObject->setState( ObjectState::Standing );

			Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, targetObject->getName() );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, targetObject->getUniqueId() );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, targetObject->getState() );
			objectStateChangedEvent.pushAttribute(
					Events::ObjectStateChanged::ms_objectDirection
				,	targetObject->getComponent< ILocateComponent >( ComponentId::Locate )->getDirection() );

			m_environment.riseEvent( objectStateChangedEvent );

			locateComponent->setLocation(
				handle->getLandscape()->getNearestLocation(
						*targetObject
					,	iterator->second->getName() ) );
			iterator->second->setState( ObjectState::Standing );

			handle->getLandscape()->addObject( iterator->second );

			Framework::Core::EventManager::Event builderHasFinishedBuildEvent( Events::BuilderHasFinishedBuild::ms_type );
			builderHasFinishedBuildEvent.pushAttribute( Events::BuilderHasFinishedBuild::ms_objectNameAttribute, iterator->second->getName() );
			builderHasFinishedBuildEvent.pushAttribute( Events::BuilderHasFinishedBuild::ms_objectLocationAttribute, locateComponent->getLocation() );
			builderHasFinishedBuildEvent.pushAttribute( Events::BuilderHasFinishedBuild::ms_objectUniqueIdAttribute, _id );
			builderHasFinishedBuildEvent.pushAttribute( Events::BuilderHasFinishedBuild::ms_objectEmplacementAttribute, locateComponent->getStaticData().m_emplacement );

			m_environment.riseEvent( builderHasFinishedBuildEvent );

			m_builders.erase( _id );
		}
	}

} // LandscapeModel::stopBuild


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
LandscapeModel::create( const QPoint& _location, const QString& _objectName )
{
	IStaticData::ObjectStaticData staticData = m_staticData.getObjectStaticData( _objectName );

	boost::shared_ptr< Object > object( new Object( _objectName, m_player->getUniqueId() ) );

	object->addComponent(
			ComponentId::Actions
		,	boost::intrusive_ptr< IComponent >( new ActionsComponent( *object ) ) );

	if ( staticData.m_healthData )
		object->addComponent(
				ComponentId::Health
			,	boost::intrusive_ptr< IComponent >( new HealthComponent( *object, *staticData.m_healthData ) ) );

	if ( staticData.m_locateData )
		object->addComponent(
				ComponentId::Locate
			,	boost::intrusive_ptr< IComponent >( new LocateComponent( *object, *staticData.m_locateData, _location ) ) );

	if ( staticData.m_selectionData )
		object->addComponent(
				ComponentId::Selection
			,	boost::intrusive_ptr< IComponent >( new SelectionComponent( *object, *staticData.m_selectionData ) ) );

	if ( staticData.m_trainData )
		object->addComponent(
				ComponentId::Train
			,	boost::intrusive_ptr< IComponent >( new TrainComponent( *object, *staticData.m_trainData ) ) );

	if ( staticData.m_moveData )
		object->addComponent(
				ComponentId::Move
			,	boost::intrusive_ptr< IComponent >( new MoveComponent( *object, *staticData.m_moveData ) ) );

	if ( staticData.m_attackData )
		object->addComponent(
				ComponentId::Attack
			,	boost::intrusive_ptr< IComponent >( new AttackComponent( *object, *staticData.m_attackData ) ) );

	if ( staticData.m_buildData )
		object->addComponent(
				ComponentId::Build
			,	boost::intrusive_ptr< IComponent >( new BuildComponent( *object, *staticData.m_buildData ) ) );

	if ( staticData.m_generateResourcesData )
	{
		object->addComponent(
				ComponentId::ResourcesGenerating
			,	boost::intrusive_ptr< IComponent >( new GenerateResourcesComponent( *object, *staticData.m_generateResourcesData ) ) );

		boost::intrusive_ptr< IActionsComponent > actionsComponent
			= object->getComponent< IActionsComponent >( ComponentId::Actions );
		actionsComponent->pushPeriodicalAction( boost::intrusive_ptr< IAction >( new GenerateResourcesAction( m_environment, *this, *object ) ) );
	}

	return object;

} // LandscapeModel::create


/*---------------------------------------------------------------------------*/


void
LandscapeModel::gameMainLoop()
{
	static qint64 lastStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - 100;

	qint64 tickTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - lastStartTime;

	lastStartTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

	{
		boost::intrusive_ptr< IModelLocker > handle( lockModel() );

		if ( handle->getLandscape() )
		{
			ILandscape::ObjectsCollection objects;
			handle->getLandscape()->fetchObjects( objects );

			ILandscape::ObjectsCollectionIterator
					begin = objects.begin()
				,	end = objects.end();

			for ( ; begin != end; ++begin )
			{
				boost::intrusive_ptr< IActionsComponent > actionsComponent
					= ( *begin )->getComponent< IActionsComponent >( ComponentId::Actions );

				// Periodical Actions loop

				IActionsComponent::ActionsIterator periodocalActions
					= actionsComponent->getPeriodicalActionsIterator();

				while( periodocalActions->isValid() )
				{
					periodocalActions->current()->processAction( tickTime );
					periodocalActions->next();
				}

				// Actions loop

				actionsComponent->processAction( tickTime );
			}
		}
	}

	// Process builders

	BuildersCollectionIterator
			begin = m_builders.begin()
		,	end = m_builders.end();

	for ( ; begin != end; ++begin )
		begin->second->getComponent< IActionsComponent >( ComponentId::Actions )->processAction( tickTime );

	// Fetch dying objects

	// Process notifications

	m_environment.getNotificationCenter()->processNotifiers();

	qint64 time = QDateTime::currentDateTime().toMSecsSinceEpoch() - lastStartTime;

	if ( time > Resources::TimeLimit )
	{
		m_environment.printMessage(
				Tools::Core::IMessenger::MessegeLevel::Warning
			,	QString( Resources::TimeLimitWarning ).arg( time ).arg( Resources::TimeLimit )  );
	}

} // LandscapeModel::gameMainLoop


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initTask( const QString& _filePath )
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	m_player.reset( new Player( m_environment, m_staticData ) );

	boost::intrusive_ptr< ILandscape >
		landscape( new Landscape( m_surfaceItemsCache, m_staticData, *this ) );

	try
	{
		m_landscapeSerializer.load( *landscape, _filePath );
	}
	catch( ... )
	{
		landscape.reset( new Landscape( m_surfaceItemsCache, m_staticData, *this ) );
		landscape->setSize( 20, 20 );
	}

	m_currentLandscape = landscape;

	Framework::Core::EventManager::Event modelInitEvent( Events::LandscapeWasInitialized::ms_type );
	modelInitEvent.pushAttribute( Events::LandscapeWasInitialized::ms_filePathAttribute, _filePath );
	modelInitEvent.pushAttribute( Events::LandscapeWasInitialized::ms_landscapeWidthAttribute, landscape->getWidth() );
	modelInitEvent.pushAttribute( Events::LandscapeWasInitialized::ms_landscapeHeightAttribute, landscape->getHeight() );

	m_environment.riseEvent( modelInitEvent );

} // LandscapeModel::initTask


/*---------------------------------------------------------------------------*/


void
LandscapeModel::resetTask()
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	m_currentLandscape.reset();
	m_player.reset();

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::LandscapeWasReset::ms_type ) );

} // LandscapeModel::resetTask


/*---------------------------------------------------------------------------*/


void
LandscapeModel::saveTask( const QString& _filePath )
{
	boost::intrusive_ptr< IModelLocker > handle( lockModel() );

	if ( m_currentLandscape )
	{
		m_landscapeSerializer.save( *m_currentLandscape, _filePath );

		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::LandscapeWasSaved::ms_type ) );
	}

} // LandscapeModel::saveTask


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
