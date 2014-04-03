
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
#include "landscape_model/sources/actions/lm_repair_action.hpp"

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
#include "landscape_model/sources/components/lm_repair_component.hpp"
#include "landscape_model/sources/components/lm_resource_holder_component.hpp"
#include "landscape_model/sources/components/lm_resource_source_component.hpp"
#include "landscape_model/sources/components/lm_resource_storage_component.hpp"
#include "landscape_model/sources/components/lm_player_component.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

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
	,	ILandscapeSerializer& _landscapeSerializer
	,	const ISurfaceItemsCache& _surfaceItemsCache
	,	const IStaticData& _staticData
	)
	:	m_environment( _environment )
	,	m_landscapeSerializer( _landscapeSerializer )
	,	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_staticData( _staticData )
	,	m_landscape()
	,	m_player()
	,	m_mutex( QMutex::Recursive )
	,	m_ticksCounter( 0 )
	,	m_builders()
{
	m_environment.startThread( Resources::ModelThreadName );

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


void
LandscapeModel::selectObjects( const QRect& _rect )
{
	if ( m_landscape )
	{
		m_landscape->selectObjects( _rect );
		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );
	}

} // LandscapeModel::selectObjects


/*---------------------------------------------------------------------------*/


void
LandscapeModel::selectObject( const Object::Id& _id )
{
	if ( m_landscape )
	{
		m_landscape->selectObject( _id );
		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );
	}

} // LandscapeModel::selectObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::sendSelectedObjects( const QPoint& _to, const bool _flush )
{
	if ( m_landscape )
	{
		ILandscape::ObjectsCollection selectedObjects;
		m_landscape->fetchSelectedObjects( selectedObjects );

		ILandscape::ObjectsCollectionIterator
				begin = selectedObjects.begin()
			,	end = selectedObjects.end();

		for ( ; begin != end; ++begin )
		{
			boost::shared_ptr< Object > targetObject = m_landscape->getObject( _to );

			boost::intrusive_ptr< IActionsComponent > actionsComponent
				= ( *begin )->getComponent< IActionsComponent >( ComponentId::Actions );
			boost::intrusive_ptr< IMoveComponent > moveComponent
				= ( *begin )->getComponent< IMoveComponent >( ComponentId::Move );
			boost::intrusive_ptr< IAttackComponent > attackComponent
				= ( *begin )->getComponent< IAttackComponent >( ComponentId::Attack );
			boost::intrusive_ptr< IResourceHolderComponent > resourceHolderComponent
				= ( *begin )->getComponent< IResourceHolderComponent >( ComponentId::ResourceHolder );
			boost::intrusive_ptr< IRepairComponent > repairComponent
				= ( *begin )->getComponent< IRepairComponent >( ComponentId::Repair );

			if ( targetObject && targetObject != *begin )
			{
				boost::intrusive_ptr< IHealthComponent > targetHealthComponent
					= targetObject->getComponent< IHealthComponent >( ComponentId::Health );

				/*if ( resourceHolderComponent && targetObject->getComponent< IResourceSourceComponent >( ComponentId::ResourceSource ) )
				{
					actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >( new CollectResourceAction( m_environment, *this, **begin, targetObject ) )
						,	_flush );
				}
				else*/
				if ( repairComponent && targetHealthComponent && targetHealthComponent->getHealth() != targetHealthComponent->getStaticData().m_maximumHealth )
				{
					actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >( new RepairAction( m_environment, *this, **begin, targetObject ) )
						,	_flush );
				}
				else if ( attackComponent && targetObject->getComponent< IHealthComponent >( ComponentId::Health ) )
				{
					actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >( new AttackAction( m_environment, *this, **begin, targetObject ) )
						,	_flush );
				}
				else if ( moveComponent )
				{
					actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >( new MoveAction( m_environment, *this, **begin, targetObject, Geometry::DiagonalDistance ) )
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

	if ( m_landscape )
	{
		objectId = m_landscape->createObject( _location, _objectName );
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
	if ( m_landscape )
	{
		m_landscape->setSurfaceItem( _location, _id );

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
	if ( !m_landscape )
		return;

	boost::shared_ptr< Object > object = m_landscape->getObject( _parentObject );

	if ( object )
	{
		boost::intrusive_ptr< IPlayer > player = getPlayer( object->getComponent< IPlayerComponent >( ComponentId::Player )->getPlayerId() );

		if ( player )
		{
			boost::intrusive_ptr< IActionsComponent > actionsComponent
				= object->getComponent< IActionsComponent >( ComponentId::Actions );
			boost::intrusive_ptr< ITrainComponent > trainComponent
				= object->getComponent< ITrainComponent >( ComponentId::Train );

			if ( trainComponent )
			{
				ITrainComponent::StaticData::TrainDataCollectionIterator
					iterator = trainComponent->getStaticData().m_trainObjects.find( _objectName );

				if (	iterator != trainComponent->getStaticData().m_trainObjects.end()
					&&	player->getResourcesData().isEnaught( iterator->second->m_resourcesData ) )
				{
					player->substructResources( iterator->second->m_resourcesData );

					actionsComponent->pushAction(
						boost::intrusive_ptr< IAction >( new TrainAction( m_environment, *this, *object, _objectName ) ), false );

					Framework::Core::EventManager::Event trainQueueChangedEvent( Events::TrainQueueChanged::ms_type );
					trainQueueChangedEvent.pushAttribute( Events::TrainQueueChanged::ms_trainerIdAttribute, object->getUniqueId() );
	
					m_environment.riseEvent( trainQueueChangedEvent );
				}
			}
		}
	}

} // LandscapeModel::trainObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::buildObject(
		const Object::Id& _builder
	,	const QString& _objectName
	,	const QPoint& _atLocation
	,	const bool _flush )
{
	boost::shared_ptr< Object > object = m_landscape->getObject( _builder );

	if ( object )
	{
		boost::intrusive_ptr< IActionsComponent > actionsComponent
			= object->getComponent< IActionsComponent >( ComponentId::Actions );

		actionsComponent->pushAction(
			boost::intrusive_ptr< IAction >( new BuildAction( m_environment, *this, *this, m_staticData, *object, _objectName, _atLocation ) ), _flush );
	}

} // LandscapeModel::buildObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::getTrainObjectsList(
		boost::shared_ptr< Object > _forObject
	,	ILandscapeModel::TrainObjectsList& _list ) const
{
	_list.clear();

	if ( _forObject )
	{
		boost::intrusive_ptr< IActionsComponent > actionsComponent
			= _forObject->getComponent< IActionsComponent >( ComponentId::Actions );

		IActionsComponent::ActionsIterator actionsIterator = actionsComponent->getActionsIterator( Actions::Train );

		while( actionsIterator->isValid() )
		{
			// TODO: костыль
			_list.push_back( dynamic_cast< TrainAction* >( actionsIterator->current().get() )->getTrainObjectName() );
			actionsIterator->next();
		}
	}

} // LandscapeModel::getTrainObjectsList


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscape >
LandscapeModel::getLandscape() const
{
	return m_landscape;

} // LandscapeModel::getLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeModel::getPlayer( const IPlayer::Id& _id ) const
{
	return m_player;

} // LandscapeModel::getPlayer


/*---------------------------------------------------------------------------*/


QMutex&
LandscapeModel::getMutex()
{
	return m_mutex;

} // LandscapeModel::getMutex


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
LandscapeModel::create( const QPoint& _location, const QString& _objectName )
{
	IStaticData::ObjectStaticData staticData = m_staticData.getObjectStaticData( _objectName );

	boost::shared_ptr< Object > object( new Object( _objectName ) );

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

	if ( staticData.m_repairData )
		object->addComponent(
				ComponentId::Repair
			,	boost::intrusive_ptr< IComponent >( new RepairComponent( *object, *staticData.m_repairData ) ) );

	if ( staticData.m_resourceHolderData )
		object->addComponent(
				ComponentId::ResourceHolder
			,	boost::intrusive_ptr< IComponent >( new ResourceHolderComponent( *object, *staticData.m_resourceHolderData ) ) );

	if ( staticData.m_resourceSourceData )
		object->addComponent(
				ComponentId::ResourceSource
			,	boost::intrusive_ptr< IComponent >( new ResourceSourceComponent( *object, *staticData.m_resourceSourceData ) ) );

	if ( staticData.m_resourceStorageData )
		object->addComponent(
				ComponentId::ResourceStorage
			,	boost::intrusive_ptr< IComponent >( new ResourceStorageComponent( *object, *staticData.m_resourceStorageData ) ) );

	if ( staticData.m_playerData )
		object->addComponent(
				ComponentId::Player
			,	boost::intrusive_ptr< IComponent >( new PlayerComponent( *object, *staticData.m_playerData, m_player->getUniqueId() ) ) );

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


boost::shared_ptr< Object >
LandscapeModel::getBuilder( const Object::Id& _id ) const
{
	BuildersCollectionIterator iterator = m_builders.find( _id );

	return		iterator != m_builders.end()
			?	iterator->second
			:	boost::shared_ptr< Object >();

} // LandscapeModel::getBuilder


/*---------------------------------------------------------------------------*/


void
LandscapeModel::removeBuilder( const Object::Id& _id )
{
	m_builders.erase( _id );

} // LandscapeModel::removeBuilder


/*---------------------------------------------------------------------------*/


void
LandscapeModel::addBuilder( boost::shared_ptr< Object > _builder )
{
	assert( m_builders.find( _builder->getUniqueId() ) == m_builders.end() );
	m_builders.insert( std::make_pair( _builder->getUniqueId(), _builder ) );

} // LandscapeModel::addBuilder


/*---------------------------------------------------------------------------*/


void
LandscapeModel::gameMainLoop()
{
	qint64 startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

	{
		QMutexLocker locker( &m_mutex );

		++m_ticksCounter;

		if ( m_landscape )
		{
			ILandscape::ObjectsCollection objects;
			m_landscape->fetchObjects( objects );

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
					periodocalActions->current()->processAction();
					periodocalActions->next();
				}

				// Actions loop

				actionsComponent->processAction();
			}
		}

		// Process builders

		BuildersCollectionIterator
				begin = m_builders.begin()
			,	end = m_builders.end();

		for ( ; begin != end; ++begin )
			begin->second->getComponent< IActionsComponent >( ComponentId::Actions )->processAction();

		// Fetch dying objects

		// Process notifications

		m_environment.getNotificationCenter()->processNotifiers();
	}

	qint64 time = QDateTime::currentDateTime().toMSecsSinceEpoch() - startTime;

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
	QMutexLocker locker( &m_mutex );

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
		landscape->setSize( 200, 200 );
	}

	m_landscape = landscape;

	Framework::Core::EventManager::Event modelInitEvent( Events::LandscapeWasInitialized::ms_type );
	modelInitEvent.pushAttribute( Events::LandscapeWasInitialized::ms_filePathAttribute, _filePath );
	modelInitEvent.pushAttribute( Events::LandscapeWasInitialized::ms_landscapeWidthAttribute, landscape->getWidth() );
	modelInitEvent.pushAttribute( Events::LandscapeWasInitialized::ms_landscapeHeightAttribute, landscape->getHeight() );

	m_environment.riseEvent( modelInitEvent );

	m_ticksCounter = 0;

	m_actionsProcessingTaskHandle = m_environment.pushPeriodicalTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::gameMainLoop, this )
		,	Resources::TimeLimit );

} // LandscapeModel::initTask


/*---------------------------------------------------------------------------*/


void
LandscapeModel::resetTask()
{
	QMutexLocker locker( &m_mutex );

	m_environment.removeTask( m_actionsProcessingTaskHandle );
	m_ticksCounter = 0;

	m_landscape.reset();
	m_player.reset();

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::LandscapeWasReset::ms_type ) );

} // LandscapeModel::resetTask


/*---------------------------------------------------------------------------*/


void
LandscapeModel::saveTask( const QString& _filePath )
{
	QMutexLocker locker( &m_mutex );

	if ( m_landscape )
	{
		m_landscapeSerializer.save( *m_landscape, _filePath );

		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::LandscapeWasSaved::ms_type ) );
	}

} // LandscapeModel::saveTask


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
