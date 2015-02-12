
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/player/lm_player.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"
#include "landscape_model/sources/replay_serializer/lm_ireplay_serializer.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/sources/actions/lm_generate_resources_action.hpp"
#include "landscape_model/sources/actions/lm_move_action.hpp"
#include "landscape_model/sources/actions/lm_attack_action.hpp"
#include "landscape_model/sources/actions/lm_train_action.hpp"
#include "landscape_model/sources/actions/lm_build_action.hpp"
#include "landscape_model/sources/actions/lm_repair_action.hpp"
#include "landscape_model/sources/actions/lm_collect_resource_action.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/sources/notification_center/lm_inotification_center.hpp"

#include "landscape_model/sources/ai/ai_manager/lm_iai_manager.hpp"

#include "landscape_model/sources/components/lm_train_component.hpp"
#include "landscape_model/sources/components/lm_actions_component.hpp"
#include "landscape_model/sources/components/lm_resource_source_component.hpp"
#include "landscape_model/sources/components/lm_resource_storage_component.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_multi_player_mode.hpp"
#include "landscape_model/sources/landscape_model/game_modes/lm_single_player_mode.hpp"
#include "landscape_model/sources/landscape_model/game_modes/lm_replay_mode.hpp"

#include "landscape_model/sources/landscape_model/victory_checker/lm_stay_alone_checker.hpp"
#include "landscape_model/sources/landscape_model/victory_checker/lm_endless_checker.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"
#include "landscape_model/ih/lm_imodel_information.hpp"

#include "landscape_model/h/lm_resources.hpp"
#include "landscape_model/h/lm_events.hpp"
#include "landscape_model/h/lm_victory_condition.hpp"

#include "event_manager/h/em_external_resources.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

static const TickType gs_aiThinkCallPeriod = 300;

/*---------------------------------------------------------------------------*/

COMMAND_MAP_BEGIN( LandscapeModel )
	PROCESSOR( ChangeVictoryCondition )
	PROCESSOR( StartSimulation )
	PROCESSOR( StopSimulation )
	PROCESSOR( SetSurfaceItem )
	PROCESSOR( SelectById )
	PROCESSOR( SelectByRect )
	PROCESSOR( SendToPoint )
	PROCESSOR( SendToObject )
	PROCESSOR( CreateObject )
	PROCESSOR( TrainObject )
	PROCESSOR( BuildObject )
	PROCESSOR( ChangePlayerRace )
	PROCESSOR( ChangePlayerType )
	PROCESSOR( ChangePlayerName )
	PROCESSOR( ChangeMyPlayer )
COMMAND_MAP_END()

/*---------------------------------------------------------------------------*/

struct ObjectsByRectFilter
	:	public ILandscape::IObjectsFilter
{
	ObjectsByRectFilter( const QRect& _rect )
		:	m_rect( _rect )
	{}

	/*virtual*/ bool check( const GameObject& _object ) const
	{
		Tools::Core::Object::Ptr locationComponent = _object.getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

		return	locationComponent
			&&	LocateComponent::getRect( *locationComponent ).intersects( m_rect );
	}

	const QRect m_rect;
};

/*---------------------------------------------------------------------------*/

struct ObjectsByIdFilter
	:	public ILandscape::IObjectsFilter
{
	ObjectsByIdFilter( const Tools::Core::Generators::IGenerator::IdType& _id )
		:	m_id( _id )
	{}

	/*virtual*/ bool check( const GameObject& _object ) const
	{
		return _object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) == m_id;
	}

	const Tools::Core::Generators::IGenerator::IdType m_id;
};

/*---------------------------------------------------------------------------*/


LandscapeModel::LandscapeModel( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_playersIdsGenerator()
	,	m_objectsIdsGenerator()
	,	m_subscriber( _environment.createSubscriber() )
	,	m_actionsProcessingTaskHandle()
	,	m_simulationStartTimeStamp( 0 )
	,	m_landscape()
	,	m_landscapeFilePath()
	,	m_players()
	,	m_myPlayerId( Tools::Core::Generators::IGenerator::ms_wrongId )
	,	m_mutex( QMutex::Recursive )
	,	m_ticksCounter( 0 )
	,	m_workers()
	,	m_gameMode()
	,	m_victoryChecker()
	,	m_simulationBlocked( false )
{
	initVictoryChecker( VictoryCondition::Begin );

	m_environment.startThread( Resources::ModelThreadName );

} // LandscapeModel::LandscapeModel


/*---------------------------------------------------------------------------*/


LandscapeModel::~LandscapeModel()
{
	resetModel();

	m_environment.stopThread( Resources::ModelThreadName );

} // LandscapeModel::~LandscapeModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initLandscape( const QString& _filePath )
{
	if ( isSimulationRunning() )
		return;

	boost::intrusive_ptr< ILandscape >
		landscape( new Landscape( m_environment, *this ) );

	try
	{
		m_environment.getLandscapeSerializer()->load( *landscape, _filePath );
	}
	catch( ... )
	{
	}

	m_landscape = landscape;
	m_landscapeFilePath = _filePath;

	initPlayers();

} // LandscapeModel::initLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeModel::setupMultiPlayerGame()
{
	if ( isSimulationRunning() )
		return;

	Framework::Core::NetworkManager::ConnectionInfo myConnectionInfo(
			m_environment.getString( Resources::Properties::Ip )
		,	m_environment.getUInt( Resources::Properties::Port ) );

	m_gameMode.reset(
		new MultiPlayerMode(
				m_environment
			,	myConnectionInfo
			,	Framework::Core::NetworkManager::ConnectionInfo() ) );

	setupMyPlayer();

} // LandscapeModel::setupMultiPlayerGame


/*---------------------------------------------------------------------------*/


void
LandscapeModel::connectToMultiPlayerGame( const Framework::Core::NetworkManager::ConnectionInfo& _connectTo )
{
	if ( isSimulationRunning() )
		return;

	Framework::Core::NetworkManager::ConnectionInfo myConnectionInfo(
			m_environment.getString( Resources::Properties::Ip )
		,	m_environment.getUInt( Resources::Properties::Port ) );

	m_gameMode.reset(
		new MultiPlayerMode(
				m_environment
			,	myConnectionInfo
			,	_connectTo ) );

} // LandscapeModel::connectToMultiPlayerGame


/*---------------------------------------------------------------------------*/


void
LandscapeModel::setupSinglePlayerGame()
{
	if ( isSimulationRunning() )
		return;

	m_gameMode.reset( new SinglePlayerMode( m_environment ) );

	setupMyPlayer();

} // LandscapeModel::setupSinglePlayerGame


/*---------------------------------------------------------------------------*/


void
LandscapeModel::resetModel()
{
	bool needToPrintMessage = isSimulationRunning();

	m_subscriber.unsubscribe();

	m_environment.removeTask( m_actionsProcessingTaskHandle );
	m_actionsProcessingTaskHandle.reset();

	m_gameMode.reset();

	m_simulationBlocked = false;

	m_simulationStartTimeStamp = 0;
	m_ticksCounter = 0;

	m_landscape.reset();
	m_landscapeFilePath.clear();

	m_players.clear();
	m_workers.clear();

	m_myPlayerId = Tools::Core::Generators::IGenerator::ms_wrongId;

	m_playersIdsGenerator.reset();
	m_objectsIdsGenerator.reset();

	processCommand( Command( CommandId::ChangeVictoryCondition ).pushArgument( VictoryCondition::Begin ) );

	if ( needToPrintMessage )
	{
		m_environment.printMessage(
				Tools::Core::IMessenger::MessegeLevel::Info
			,	QString( Resources::SimulationHasBeenStoppedMessage ).arg( Tools::Core::Time::currentTime() ) );
	}

} // LandscapeModel::resetModel


/*---------------------------------------------------------------------------*/


void
LandscapeModel::saveModel( const QString& _filePath )
{
	if ( m_landscape )
	{
		QString filePath( _filePath );

		if ( filePath.isEmpty() )
			filePath = m_landscapeFilePath;

		if ( filePath.isEmpty() )
			return;

		m_environment.getLandscapeSerializer()->save( *this, *m_landscape, _filePath );
	}

} // LandscapeModel::saveModel


/*---------------------------------------------------------------------------*/


bool
LandscapeModel::isSimulationRunning() const
{
	return m_actionsProcessingTaskHandle.isValid();

} // LandscapeModel::isSimulationRunning


/*---------------------------------------------------------------------------*/


bool
LandscapeModel::isConfigurated() const
{
	return m_gameMode;

} // LandscapeModel::isConfigurated


/*---------------------------------------------------------------------------*/


void
LandscapeModel::setupReplay( const QString& _filePath )
{
	resetModel();

	QString landscapeName;
	VictoryCondition::Enum victoryCondition( VictoryCondition::Begin );
	ILandscapeModel::PlayersCollection players;
	CommandsQueue commandsQueue;

	m_environment.getReplaySerializer()->load( _filePath, landscapeName, victoryCondition, players, commandsQueue );

	initVictoryChecker( victoryCondition );
	initLandscape( m_environment.getModelInformation()->generateLandscapePath( landscapeName ) );

	m_gameMode.reset( new ReplayMode( m_environment ) );

	// Setup players

	m_players.clear();

	ILandscapeModel::PlayersCollectionIterator
			begin = players.begin()
		,	end = players.end();

	// TODO: should be corrected
	for( ; begin != end; ++begin )
		m_players.insert( std::make_pair( ( *begin )->getUniqueId(), boost::intrusive_ptr< Player >( dynamic_cast< Player* >( ( *begin ).get() ) ) ) );

	// Setup commands

	CommandsQueue::CommandsByTickCollection commands;
	commandsQueue.fetchCommands( commands );

	CommandsQueue::CommandsByTickCollectionIterator
			beginTicks = commands.begin()
		,	endTicks = commands.end();

	for ( ; beginTicks != endTicks; ++beginTicks )
	{
		CommandsQueue::CommandsByPlayerCollectionIterator
				beginCommandsByPlayer = beginTicks->second.begin()
			,	endCommandsByPlayer = beginTicks->second.end();

		for ( ; beginCommandsByPlayer != endCommandsByPlayer; ++beginCommandsByPlayer )
		{
			CommandsQueue::CommandsCollectionIterator
					beginCommands = beginCommandsByPlayer->second.begin()
				,	endCommands = beginCommandsByPlayer->second.end();

			for ( ; beginCommands != endCommands; ++beginCommands )
			{
				m_gameMode->processCommand( *beginCommands );
			}
		}
	}

} // LandscapeModel::setupReplay


/*---------------------------------------------------------------------------*/


void
LandscapeModel::saveReplay( const QString& _filePath )
{
	if ( !m_gameMode )
		return;

	ILandscapeModel::PlayersCollection players;
	fetchPlayers( players );

	m_environment.getReplaySerializer()->save(
			_filePath
		,	getLandscapeName()
		,	getVictoryConditionType()
		,	players
		,	m_gameMode->getCommands() );

} // LandscapeModel::saveReplay


/*---------------------------------------------------------------------------*/


const VictoryCondition::Enum
LandscapeModel::getVictoryConditionType() const
{
	return m_victoryChecker->getType();

} // LandscapeModel::getVictoryConditionType


/*---------------------------------------------------------------------------*/


const IGameMode::Type::Enum
LandscapeModel::getGameModeType() const
{
	return m_gameMode ? m_gameMode->getType() : IGameMode::Type::Undefined;

} // LandscapeModel::getGameModeType


/*---------------------------------------------------------------------------*/


void
LandscapeModel::pushCommand( const Command& _command )
{
	if ( !m_gameMode || ( m_simulationBlocked && CommandId::simulationTimeCommand( _command.m_id ) ) )
	{
		m_environment.printMessage(
				Tools::Core::IMessenger::MessegeLevel::Warning
			,	QString( Resources::CommandWilNotBeProcessedMessage ).arg( CommandId::toString( _command.m_id ) ) );

		return;
	}

	if ( m_gameMode->getType() == IGameMode::Type::Replay && CommandId::simulationTimeCommand( _command.m_id ) )
	{
		m_environment.printMessage(
				Tools::Core::IMessenger::MessegeLevel::Warning
			,	QString( Resources::CommandCannotBeProcessedInReplayModeMessage ).arg( CommandId::toString( _command.m_id ) ) );

		return;
	}

	Command command( _command );

	command.m_timeStamp = Tools::Core::Time::currentTime() - m_simulationStartTimeStamp;
	command.m_targetTick = m_ticksCounter;
	command.m_playerId = m_myPlayerId;

	m_gameMode->processCommand( command );

} // LandscapeModel::pushCommand


/*---------------------------------------------------------------------------*/


bool
LandscapeModel::hasMoreCommands() const
{
	assert( isSimulationRunning() );
	return m_gameMode && m_gameMode->getCommands().hasCommandsFrom( m_ticksCounter + 1 );

} // LandscapeModel::hasMoreCommands


/*---------------------------------------------------------------------------*/


void
LandscapeModel::getTrainObjectsList(
		boost::shared_ptr< GameObject > _forObject
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


const QString&
LandscapeModel::getLandscapeFilePath() const
{
	return m_landscapeFilePath;

} // LandscapeModel::getLandscapeFilePath


/*---------------------------------------------------------------------------*/


QString
LandscapeModel::getLandscapeName() const
{
	if ( m_landscapeFilePath.isEmpty() )
		return QString();

	return QFileInfo( m_landscapeFilePath ).baseName();

} // LandscapeModel::getLandscapeName


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeModel::getPlayer( const Tools::Core::Generators::IGenerator::IdType& _id ) const
{
	PlayersMapIterator iterator = m_players.find( _id );
	return iterator != m_players.end() ? iterator->second : boost::intrusive_ptr< IPlayer >();

} // LandscapeModel::getPlayer


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeModel::getPlayer( const GameObject& _object ) const
{
	Tools::Core::Object::Ptr playerComponent
		= _object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

	if ( !playerComponent )
		return boost::intrusive_ptr< IPlayer >();

	return getPlayer( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );

} // LandscapeModel::getPlayer


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeModel::getPlayer( const QString& _name ) const
{
	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for ( ; begin != end; ++begin )
	{
		if ( begin->second->getName() == _name )
			return begin->second;
	}

	return boost::intrusive_ptr< IPlayer >();

} // LandscapeModel::getPlayer


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeModel::getPlayerByStartPoint( const Tools::Core::Generators::IGenerator::IdType& _id ) const
{
	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for ( ; begin != end; ++begin )
	{
		if ( begin->second->getStartPointId() == _id )
			return begin->second;
	}

	return boost::intrusive_ptr< IPlayer >();

} // LandscapeModel::getPlayerByStartPoint


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeModel::getMyPlayer() const
{
	return getPlayer( m_myPlayerId );

} // LandscapeModel::getMyPlayer


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeModel::getFirstFreePlayer() const
{
	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for ( ; begin != end; ++begin )
	{
		if ( PlayerType::isFree( begin->second->getType() ) )
			return begin->second;
	}

	return boost::intrusive_ptr< IPlayer >();

} // LandscapeModel::getFirstFreePlayer


/*---------------------------------------------------------------------------*/


void
LandscapeModel::fetchPlayers( ILandscapeModel::PlayersCollection& _collection ) const
{
	_collection.clear();

	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for ( ; begin != end; ++begin )
		_collection.push_back( begin->second );

} // LandscapeModel::fetchPlayers


/*---------------------------------------------------------------------------*/


bool
LandscapeModel::twoOrMoreActivatedPlayers() const
{
	int count = 0;

	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for ( ; begin != end; ++begin )
	{
		if ( PlayerType::isActivated( begin->second->getType() ) )
			++count;

		if ( count == 2 )
			return true;
	}

	return false;

} // LandscapeModel::twoOrMoreActivatedPlayers


/*---------------------------------------------------------------------------*/


bool
LandscapeModel::isMyObject( const Tools::Core::Generators::IGenerator::IdType& _objectId ) const
{
	return m_landscape && isMyObject( m_landscape->getObject( _objectId ) );

} // LandscapeModel::isMyObject


/*---------------------------------------------------------------------------*/


bool
LandscapeModel::isMyObject( boost::shared_ptr< GameObject > _object ) const
{
	if ( !_object )
		return false;

	boost::intrusive_ptr< IPlayer > myPlayer = getMyPlayer();

	if ( !myPlayer )
		return false;

	Tools::Core::Object::Ptr playerComponent
		= _object->getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

	return playerComponent && playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) == myPlayer->getUniqueId();

} // LandscapeModel::isMyObject


/*---------------------------------------------------------------------------*/


void
LandscapeModel::fetchWorkers( ILandscape::ObjectsCollection& _collection ) const
{
	_collection.clear();

	WorkersCollectionIterator
			begin = m_workers.begin()
		,	end = m_workers.end();

	for ( ; begin != end; ++begin )
		_collection.push_back( begin->second );

} // LandscapeModel::fetchWorkers


/*---------------------------------------------------------------------------*/


QMutex&
LandscapeModel::getMutex()
{
	return m_mutex;

} // LandscapeModel::getMutex


/*---------------------------------------------------------------------------*/


boost::shared_ptr< GameObject >
LandscapeModel::create( const QString& _objectName, const QPoint& _location, const Tools::Core::Generators::IGenerator::IdType& _playerId )
{
	IStaticData::ObjectStaticData staticData = m_environment.getStaticData()->getObjectStaticData( _objectName );

	boost::shared_ptr< GameObject > object( new GameObject( _objectName, m_objectsIdsGenerator.generate() ) );

	object->addComponent(
			ComponentId::Actions
		,	boost::intrusive_ptr< IComponent >( new ActionsComponent( *object ) ) );

	if ( staticData.m_healthData )
		object->pushMember( GameObject::generateName( HealthComponent::Name, StaticDataTools::Name ), staticData.m_healthData );

	if ( staticData.m_locateData )
	{
		object->pushMember( GameObject::generateName( LocateComponent::Name, StaticDataTools::Name ), staticData.m_locateData );
		object->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name )->pushMember( LocateComponent::Location, _location );
	}

	if ( staticData.m_selectionData )
		object->pushMember( GameObject::generateName( SelectionComponent::Name, StaticDataTools::Name ), staticData.m_selectionData );

	if ( staticData.m_trainData )
		object->addComponent(
				ComponentId::Train
			,	boost::intrusive_ptr< IComponent >( new TrainComponent( *object, *staticData.m_trainData ) ) );

	if ( staticData.m_moveData )
		object->pushMember( GameObject::generateName( MoveComponent::Name, StaticDataTools::Name ), staticData.m_moveData );

	if ( staticData.m_attackData )
		object->pushMember( GameObject::generateName( AttackComponent::Name, StaticDataTools::Name ), staticData.m_attackData );

	if ( staticData.m_buildData )
		object->pushMember( GameObject::generateName( BuildComponent::Name, StaticDataTools::Name ), staticData.m_buildData );

	if ( staticData.m_repairData )
		object->pushMember( GameObject::generateName( RepairComponent::Name, StaticDataTools::Name ), staticData.m_repairData );

	if ( staticData.m_resourceHolderData )
		object->pushMember( GameObject::generateName( ResourceHolderComponent::Name, StaticDataTools::Name ), staticData.m_resourceHolderData );

	if ( staticData.m_resourceSourceData )
		object->addComponent(
				ComponentId::ResourceSource
			,	boost::intrusive_ptr< IComponent >( new ResourceSourceComponent( *object, *staticData.m_resourceSourceData ) ) );

	if ( staticData.m_resourceStorageData )
		object->addComponent(
				ComponentId::ResourceStorage
			,	boost::intrusive_ptr< IComponent >( new ResourceStorageComponent( *object, *staticData.m_resourceStorageData ) ) );

	if ( staticData.m_playerData )
	{
		object->pushMember( GameObject::generateName( PlayerComponent::Name, StaticDataTools::Name ), staticData.m_playerData );
		object->getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name )->pushMember( PlayerComponent::PlayerId, _playerId );
	}

	if ( staticData.m_generateResourcesData )
	{
		object->pushMember( GameObject::generateName( GenerateResourcesComponent::Name, StaticDataTools::Name ), staticData.m_generateResourcesData );

		boost::intrusive_ptr< IActionsComponent > actionsComponent
			= object->getComponent< IActionsComponent >( ComponentId::Actions );
		actionsComponent->pushPeriodicalAction( boost::intrusive_ptr< IAction >( new GenerateResourcesAction( m_environment, *this, *object ) ) );
	}

	m_environment.getFunctionCaller().callFunction( m_environment.getStaticData()->getObjectCreator( _objectName ), boost::shared_static_cast< Tools::Core::Object >( object ) );

	return object;

} // LandscapeModel::create


/*---------------------------------------------------------------------------*/


boost::shared_ptr< GameObject >
LandscapeModel::getWorker( const Tools::Core::Generators::IGenerator::IdType& _id ) const
{
	WorkersCollectionIterator iterator = m_workers.find( _id );

	return		iterator != m_workers.end()
			?	iterator->second
			:	boost::shared_ptr< GameObject >();

} // LandscapeModel::getWorker


/*---------------------------------------------------------------------------*/


void
LandscapeModel::removeWorker( const Tools::Core::Generators::IGenerator::IdType& _id )
{
	m_workers.erase( _id );

} // LandscapeModel::removeWorker


/*---------------------------------------------------------------------------*/


void
LandscapeModel::addWorker( boost::shared_ptr< GameObject > _worker )
{
	assert( m_workers.find( _worker->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) == m_workers.end() );
	m_workers.insert( std::make_pair( _worker->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ), _worker ) );

} // LandscapeModel::addWorker


/*---------------------------------------------------------------------------*/


void
LandscapeModel::gameMainLoop()
{
	const Tools::Core::Time::Milliseconds startTime = Tools::Core::Time::currentTime();

	{
		QMutexLocker locker( &m_mutex );

		if ( !m_gameMode->prepareToTick( m_ticksCounter + 1 ) )
		{
			m_simulationBlocked = true;
			return;
		}

		m_simulationBlocked = false;

		// Oops, simulation has been finished!
		if ( !isSimulationRunning() )
			return;

		++m_ticksCounter;

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::CurrentTickNumberChanged::Type )
				.pushMember( Events::CurrentTickNumberChanged::TickNumberAttribute, m_ticksCounter ) );

		if ( m_ticksCounter == 1 || ( m_ticksCounter % gs_aiThinkCallPeriod == 0 ) )
			processAIThinkCall();

		processAIPlayersGoals();

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

		// Process workers

		// TODO: workers can be removed during processing
		WorkersCollection workers = m_workers;

		WorkersCollectionIterator
				begin = workers.begin()
			,	end = workers.end();

		for ( ; begin != end; ++begin )
			begin->second->getComponent< IActionsComponent >( ComponentId::Actions )->processAction();

		// Fetch dying objects

		// Process notifications

		m_environment.getNotificationCenter()->processNotifiers();
	}

	if ( m_victoryChecker->check() )
	{
		pushCommand( Command( CommandId::StopSimulation ) );
		return;
	}

	const Tools::Core::Time::Milliseconds time = Tools::Core::Time::currentTime() - startTime;

	if ( time > Resources::TimeLimit )
	{
		/*m_environment.printMessage(
				Tools::Core::IMessenger::MessegeLevel::Warning
			,	QString( Resources::TimeLimitWarning ).arg( time ).arg( Resources::TimeLimit )  );*/
	}

} // LandscapeModel::gameMainLoop


/*---------------------------------------------------------------------------*/


void
LandscapeModel::locateStartPointObjects()
{
	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for( ; begin != end; ++begin )
	{
		if ( !PlayerType::isActivated( begin->second->getType() ) )
			continue;

		m_landscape->createObject(
				m_environment.getStaticData()->getStartPointObjectName( begin->second->getRace() )
			,	m_landscape->getStartPoint( begin->second->getStartPointId() ).getMember< QPoint >( StartPoint::Point )
			,	begin->second->getUniqueId() );
	}

} // LandscapeModel::locateStartPointObjects


/*---------------------------------------------------------------------------*/


bool
LandscapeModel::shouldStoreResources( const GameObject& _holder, boost::shared_ptr< GameObject > _storage )
{
	Tools::Core::Object::Ptr resourceHolderComponent
		= _holder.getMember< Tools::Core::Object::Ptr >( ResourceHolderComponent::Name );
	boost::intrusive_ptr< IResourceStorageComponent > resourceStorageComponent
		= _storage->getComponent< IResourceStorageComponent >( ComponentId::ResourceStorage );

	if ( !resourceHolderComponent || !resourceStorageComponent )
		return false;

	Tools::Core::Object::Ptr storagePlayerComponent
		= _storage->getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );
	Tools::Core::Object::Ptr holderPlayerComponent
		= _holder.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

	assert( storagePlayerComponent );
	assert( holderPlayerComponent );

	if ( storagePlayerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId )
			!= holderPlayerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) )
		return false;

	IResourceStorageComponent::StaticData::StoredResourcesCollectionIterator
			begin = resourceStorageComponent->getStaticData().m_storedResources.begin()
		,	end = resourceStorageComponent->getStaticData().m_storedResources.end();

	for ( ; begin != end; ++begin )
	{
		if ( resourceHolderComponent->getMember< ResourcesData >( ResourceHolderComponent::HeldResources ).getResourceValue( *begin ) > 0 )
			return true;
	}

	return false;

} // LandscapeModel::shouldStoreResources


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initPlayers()
{
	m_playersIdsGenerator.reset();
	m_players.clear();

	IStaticData::RacesCollection races;
	m_environment.getStaticData()->fetchRaces( races );

	ILandscape::StartPointsIterator iterator = m_landscape->getStartPointsIterator();

	while( iterator->isValid() )
	{
		boost::intrusive_ptr< Player > player(
			new Player(	m_environment
					,	m_playersIdsGenerator.generate(), races.begin()->first
					,	iterator->current().getMember< Tools::Core::Generators::IGenerator::IdType >( StartPoint::Id ) ) );
		m_players.insert( std::make_pair( player->getUniqueId(), player ) );

		iterator->next();
	}

} // LandscapeModel::initPlayers


/*---------------------------------------------------------------------------*/


void
LandscapeModel::setupMyPlayer()
{
	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for ( ; begin != end; ++begin )
	{
		if ( PlayerType::isFree( begin->second->getType() ) )
		{
			pushCommand( Command( CommandId::ChangePlayerType ).pushArgument( begin->first ).pushArgument( PlayerType::Player ) );
			pushCommand( Command( CommandId::ChangePlayerName ).pushArgument( begin->first ).pushArgument( m_environment.getString( Resources::Properties::PlayerName ) ) );
			m_myPlayerId = begin->first;
			break;
		}
	}

	assert( m_myPlayerId != Tools::Core::Generators::IGenerator::ms_wrongId );

} // LandscapeModel::setupMyPlayer


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initVictoryChecker( const VictoryCondition::Enum _condition )
{
	switch( _condition )
	{
	case VictoryCondition::StayAlone:
		m_victoryChecker.reset( new StayAloneChecker( *this ) );
		break;
	default:
		m_victoryChecker.reset( new EndlessChecker( *this ) );
		break;
	}

} // LandscapeModel::initVictoryChecker


/*---------------------------------------------------------------------------*/


void
LandscapeModel::processAIThinkCall()
{
	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for ( ; begin != end; ++begin )
	{
		if ( begin->second->getType() == PlayerType::AI )
		{
			const IAIManager::AIData& aiData = m_environment.getAIManager()->getAIData( begin->second->getAIName() );
			m_environment.getFunctionCaller().callFunction( aiData.m_thinkFunction, begin->second->getUniqueId() );
		}
	}

} // LandscapeModel::processAIThinkCall


/*---------------------------------------------------------------------------*/


void
LandscapeModel::processAIPlayersGoals()
{
	PlayersMapIterator
			begin = m_players.begin()
		,	end = m_players.end();

	for ( ; begin != end; ++begin )
	{
		if ( begin->second->getType() == PlayerType::AI )
			begin->second->processGoals();
	}

} // LandscapeModel::processAIPlayersGoals


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onStartSimulationProcessor( const Command& _command )
{
	if ( isSimulationRunning() || !m_gameMode )
		return;

	locateStartPointObjects();

	try
	{
		m_environment.getLandscapeSerializer()->loadObjects( *this, *m_landscape, m_landscapeFilePath );
	}
	catch( ... )
	{
	}

	m_ticksCounter = 0;

	m_simulationStartTimeStamp = Tools::Core::Time::currentTime();

	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Info
		,	QString( Resources::SimulationHasBeenStartedMessage ).arg( m_simulationStartTimeStamp ) );

	m_actionsProcessingTaskHandle = m_environment.pushPeriodicalTask(
			Resources::ModelThreadName
		,	boost::bind( &LandscapeModel::gameMainLoop, this )
		,	Resources::TimeLimit );

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::SimulationStarted::Type ) );

	m_subscriber.subscribe(		Resources::ModelThreadName
							,	Framework::Core::EventManager::Resources::AnyEventName
							,	boost::bind( &LandscapeModel::onEvent, this, _1 ) );

} // LandscapeModel::onStartSimulationProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onStopSimulationProcessor( const Command& _command )
{
	if ( !isSimulationRunning() )
		return;

	m_subscriber.unsubscribe();

	m_environment.removeTask( m_actionsProcessingTaskHandle );
	m_actionsProcessingTaskHandle.reset();

	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Success
			,	QString( Resources::SimulationStoppedMessage ).arg( Tools::Core::Time::currentTime() ).arg( m_ticksCounter ) );

} // LandscapeModel::onStopSimulationProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangeVictoryConditionProcessor( const Command& _command )
{
	const VictoryCondition::Enum condition = static_cast< VictoryCondition::Enum >( _command.m_arguments[ 0 ].toInt() );

	initVictoryChecker( condition );

	Framework::Core::EventManager::Event conditionChanged( Events::VictoryConditionChanged::Type );
	conditionChanged.pushMember( Events::VictoryConditionChanged::ConditionAttribute, condition );

	m_environment.riseEvent( conditionChanged );

} // LandscapeModel::onChangeVictoryConditionProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangePlayerRaceProcessor( const Command& _command )
{
	const Tools::Core::Generators::IGenerator::IdType id = _command.m_arguments[ 0 ].toInt();
	const QString race = _command.m_arguments[ 1 ].toString();

	PlayersMapIterator iterator = m_players.find( id );
	
	if ( iterator != m_players.end() )
	{
		iterator->second->setRace( race );

		Framework::Core::EventManager::Event playerRaceChangedEvent( Events::PlayerRaceChanged::Type );
		playerRaceChangedEvent.pushMember( Events::PlayerRaceChanged::PlayerIdAttribute, id );
		playerRaceChangedEvent.pushMember( Events::PlayerRaceChanged::PlayerRaceAttribute, race );

		m_environment.riseEvent( playerRaceChangedEvent );
	}

} // LandscapeModel::onChangePlayerRaceProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangePlayerTypeProcessor( const Command& _command )
{
	const Tools::Core::Generators::IGenerator::IdType id = _command.m_arguments[ 0 ].toInt();
	const PlayerType::Enum type = static_cast< PlayerType::Enum >( _command.m_arguments[ 1 ].toInt() );

	PlayersMapIterator iterator = m_players.find( id );
	
	if ( iterator != m_players.end() )
	{
		iterator->second->setType( type );

		Framework::Core::EventManager::Event playerTypeChangedEvent( Events::PlayerTypeChanged::Type );
		playerTypeChangedEvent.pushMember( Events::PlayerTypeChanged::PlayerIdAttribute, id );
		playerTypeChangedEvent.pushMember( Events::PlayerTypeChanged::PlayerTypeAttribute, type );

		m_environment.riseEvent( playerTypeChangedEvent );
	}

} // LandscapeModel::onChangePlayerTypeProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangePlayerNameProcessor( const Command& _command )
{
	const Tools::Core::Generators::IGenerator::IdType id = _command.m_arguments[ 0 ].toInt();
	const QString name = _command.m_arguments[ 1 ].toString();

	PlayersMapIterator iterator = m_players.find( id );
	
	if ( iterator != m_players.end() )
	{
		iterator->second->setName( name );

		Framework::Core::EventManager::Event playerNameChangedEvent( Events::PlayerNameChanged::Type );
		playerNameChangedEvent.pushMember( Events::PlayerNameChanged::PlayerIdAttribute, id );
		playerNameChangedEvent.pushMember( Events::PlayerNameChanged::PlayerNameAttribute, name );
		playerNameChangedEvent.pushMember( Events::PlayerNameChanged::StartPointIdAttribute, iterator->second->getStartPointId() );

		m_environment.riseEvent( playerNameChangedEvent );
	}

} // LandscapeModel::onChangePlayerNameProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangeMyPlayerProcessor( const Command& _command )
{
	const Tools::Core::Generators::IGenerator::IdType id = _command.m_arguments[ 0 ].toInt();
	const QString name = _command.m_arguments[ 1 ].toString();
	const QString race = _command.m_arguments[ 2 ].toString();
	const PlayerType::Enum type = static_cast< PlayerType::Enum >( _command.m_arguments[ 3 ].toInt() );

	PlayersMapIterator iterator = m_players.find( id );
	
	if ( iterator != m_players.end() )
	{
		m_myPlayerId = id;
		processCommand( Command( CommandId::ChangePlayerName ).pushArgument( id ).pushArgument( name ) );
		processCommand( Command( CommandId::ChangePlayerRace ).pushArgument( id ).pushArgument( race ) );
		processCommand( Command( CommandId::ChangePlayerType ).pushArgument( id ).pushArgument( type ) );
	}

} // LandscapeModel::onChangeMyPlayerProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onSelectByRectProcessor( const Command& _command )
{
	if ( m_landscape )
	{
		m_landscape->selectObjects( ObjectsByRectFilter( _command.m_arguments[ 0 ].toRect() ) );
		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::Type ) );
	}

} // LandscapeModel::onSelectByRectProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onSelectByIdProcessor( const Command& _command )
{
	if ( m_landscape )
	{
		m_landscape->selectObjects( ObjectsByIdFilter( _command.m_arguments[ 0 ].toInt() ) );
		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::Type ) );
	}

} // LandscapeModel::onSelectByIdProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onSendToPointProcessor( const Command& _command )
{
	if ( m_landscape )
	{
		const QList< QVariant > objects = _command.m_arguments[ 0 ].toList();
		const QPoint location = _command.m_arguments[ 1 ].toPoint();
		const bool flush = _command.m_arguments[ 2 ].toBool();

		QList< QVariant >::ConstIterator
				begin = objects.begin()
			,	end = objects.end();

		for ( ; begin != end; ++begin )
		{
			boost::shared_ptr< GameObject > object = m_landscape->getObject( begin->toInt() );

			if ( object )
			{
				boost::intrusive_ptr< IActionsComponent > actionsComponent
					= object->getComponent< IActionsComponent >( ComponentId::Actions );

				if ( object->getMember< Tools::Core::Object::Ptr >( MoveComponent::Name ) )
				{
					actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >( new MoveAction( m_environment, *this, *object, location ) )
						,	flush );
				}
			}
		}
	}

} // LandscapeModel::onSendToPointProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onSendToObjectProcessor( const Command& _command )
{
	if ( m_landscape )
	{
		const QList< QVariant > objects = _command.m_arguments[ 0 ].toList();
		const Tools::Core::Generators::IGenerator::IdType id = _command.m_arguments[ 1 ].toInt();
		const bool flush = _command.m_arguments[ 2 ].toBool();

		boost::shared_ptr< GameObject > targetObject = m_landscape->getObject( id );

		if ( !targetObject )
			return;

		QList< QVariant >::ConstIterator
				begin = objects.begin()
			,	end = objects.end();

		for ( ; begin != end; ++begin )
		{
			boost::shared_ptr< GameObject > object = m_landscape->getObject( begin->toInt() );

			if ( object )
			{
				boost::intrusive_ptr< IActionsComponent > actionsComponent
					= object->getComponent< IActionsComponent >( ComponentId::Actions );
				Tools::Core::Object::Ptr moveComponent
					= object->getMember< Tools::Core::Object::Ptr >( MoveComponent::Name );
				Tools::Core::Object::Ptr attackComponent
					= object->getMember< Tools::Core::Object::Ptr >( AttackComponent::Name );
				Tools::Core::Object::Ptr resourceHolderComponent
					= object->getMember< Tools::Core::Object::Ptr >( ResourceHolderComponent::Name );
				Tools::Core::Object::Ptr repairComponent
					= object->getMember< Tools::Core::Object::Ptr >( RepairComponent::Name );

				Tools::Core::Object::Ptr playerComponent
					= object->getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );
				assert( playerComponent );

				if ( targetObject != object )
				{
					Tools::Core::Object::Ptr targetHealthComponent
						= targetObject->getMember< Tools::Core::Object::Ptr >( HealthComponent::Name );
					Tools::Core::Object::Ptr targetPlayerComponent
						= targetObject->getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

					if (	resourceHolderComponent
						&&	targetObject->getComponent< IResourceSourceComponent >( ComponentId::ResourceSource ) )
					{
						actionsComponent->pushAction(
								boost::intrusive_ptr< IAction >( new CollectResourceAction( m_environment, *this, *this, *object, targetObject ) )
							,	flush );
					}
					else if ( shouldStoreResources( *object, targetObject ) )
					{
						actionsComponent->pushAction(
								boost::intrusive_ptr< IAction >( new CollectResourceAction( m_environment, *this, *this, targetObject, *object ) )
							,	flush );
					}
					else if (	repairComponent
							&&	targetHealthComponent
							&&	!HealthComponent::isHealthy( *targetHealthComponent ) //!targetHealthComponent->callMethod< bool >( HealthComponent::IsHealthy )
							&&	playerComponent
							&&	targetPlayerComponent
							&&	playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId )
									== targetPlayerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) )
					{
						actionsComponent->pushAction(
								boost::intrusive_ptr< IAction >( new RepairAction( m_environment, *this, *object, targetObject ) )
							,	flush );
					}
					else if (	attackComponent
							&&	targetHealthComponent
							&&	playerComponent
							&&	targetPlayerComponent
							&&	playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId )
									!= targetPlayerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) )
					{
						actionsComponent->pushAction(
								boost::intrusive_ptr< IAction >( new AttackAction( m_environment, *this, *object, targetObject ) )
							,	flush );
					}
					else if ( moveComponent )
					{
						actionsComponent->pushAction(
								boost::intrusive_ptr< IAction >( new MoveAction( m_environment, *this, *object, targetObject, Geometry::DiagonalDistance ) )
							,	flush );
					}
				}
			}
		}
	}

} // LandscapeModel::onSendToObjectProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onCreateObjectProcessor( const Command& _command )
{
	Tools::Core::Generators::IGenerator::IdType objectId = Tools::Core::Generators::IGenerator::ms_wrongId;

	const Tools::Core::Generators::IGenerator::IdType id = _command.m_arguments[ 0 ].toInt();
	const QString name = _command.m_arguments[ 1 ].toString();
	const QPoint location = _command.m_arguments[ 2 ].toPoint();

	if ( m_landscape )
	{
		objectId = m_landscape->createObject( name, location, id );
	}

	if ( objectId != Tools::Core::Generators::IGenerator::ms_wrongId )
	{
		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::ObjectAdded::Type )
				.pushMember( Events::ObjectAdded::ObjectNameAttribute, name )
				.pushMember( Events::ObjectAdded::ObjectLocationAttribute, location )
				.pushMember( Events::ObjectAdded::ObjectUniqueIdAttribute, objectId )
				.pushMember(
						Events::ObjectAdded::ObjectEmplacementAttribute
					,	m_environment.getStaticData()->getObjectStaticData( name ).m_locateData->getMember< Emplacement::Enum >( LocateComponent::StaticData::Emplacement ) ) );
	}
	else
	{
		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::CreateObjectFailed::Type )
				.pushMember( Events::CreateObjectFailed::ObjectNameAttribute, name )
				.pushMember( Events::CreateObjectFailed::ObjectLocationAttribute, location ) );
	}

} // LandscapeModel::onCreateObjectProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onSetSurfaceItemProcessor( const Command& _command )
{
	if ( m_landscape )
	{
		const QPoint location = _command.m_arguments[ 0 ].toPoint();
		const Tools::Core::Generators::IGenerator::IdType id = _command.m_arguments[ 1 ].toInt();

		m_landscape->setSurfaceItem( location, id );

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::SurfaceItemChanged::Type )
				.pushMember( Events::SurfaceItemChanged::SurfaceItemIdAttribute, id )
				.pushMember( Events::SurfaceItemChanged::SurfaceItemLocationAttribute, location ) );
	}

} // LandscapeModel::onSetSurfaceItemProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onTrainObjectProcessor( const Command& _command )
{
	if ( !m_landscape )
		return;

	const Tools::Core::Generators::IGenerator::IdType parentId = _command.m_arguments[ 0 ].toInt();
	const QString name = _command.m_arguments[ 1 ].toString();

	boost::shared_ptr< GameObject > object = m_landscape->getObject( parentId );

	if ( object )
	{
		boost::intrusive_ptr< IPlayer > player = getPlayer( *object );

		if ( player )
		{
			boost::intrusive_ptr< IActionsComponent > actionsComponent
				= object->getComponent< IActionsComponent >( ComponentId::Actions );
			boost::intrusive_ptr< ITrainComponent > trainComponent
				= object->getComponent< ITrainComponent >( ComponentId::Train );

			if ( trainComponent )
			{
				ITrainComponent::StaticData::TrainDataCollectionIterator
					iterator = trainComponent->getStaticData().m_trainObjects.find( name );

				if (	iterator != trainComponent->getStaticData().m_trainObjects.end()
					&&	player->getResourcesData().isEnaught( iterator->second->m_resourcesData ) )
				{
					player->substructResources( iterator->second->m_resourcesData );

					actionsComponent->pushAction(
						boost::intrusive_ptr< IAction >( new TrainAction( m_environment, *this, *object, name ) ), false );

					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::TrainQueueChanged::Type )
							.pushMember( Events::TrainQueueChanged::TrainerIdAttribute, object->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );
				}
			}
		}
	}

} // LandscapeModel::onTrainObjectProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onBuildObjectProcessor( const Command& _command )
{
	if ( m_landscape )
	{
		const Tools::Core::Generators::IGenerator::IdType builderId = _command.m_arguments[ 0 ].toInt();
		const QString name = _command.m_arguments[ 1 ].toString();
		const QPoint location = _command.m_arguments[ 2 ].toPoint();
		const bool flush = _command.m_arguments[ 3 ].toBool();

		boost::shared_ptr< GameObject > object = m_landscape->getObject( builderId );

		if ( object )
		{
			boost::intrusive_ptr< IActionsComponent > actionsComponent
				= object->getComponent< IActionsComponent >( ComponentId::Actions );

			actionsComponent->pushAction(
				boost::intrusive_ptr< IAction >( new BuildAction( m_environment, *this, *this, *object, name, location ) ), flush );
		}
	}

} // LandscapeModel::onBuildObjectProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onEvent( const Framework::Core::EventManager::Event& _event )
{
} // LandscapeModel::onEvent


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
