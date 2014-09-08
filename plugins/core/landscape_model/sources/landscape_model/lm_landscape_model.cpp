
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/player/lm_player.hpp"

#include "landscape_model/sources/landscape_serializer/lm_ilandscape_serializer.hpp"
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

#include "landscape_model/sources/landscape_model/game_modes/lm_multi_player_mode.hpp"
#include "landscape_model/sources/landscape_model/game_modes/lm_single_player_mode.hpp"

#include "landscape_model/sources/landscape_model/victory_checker/lm_stay_alone_checker.hpp"
#include "landscape_model/sources/landscape_model/victory_checker/lm_endless_checker.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/h/lm_resources.hpp"
#include "landscape_model/h/lm_events.hpp"
#include "landscape_model/h/lm_victory_condition.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

COMMAND_MAP_BEGIN( LandscapeModel )
	PROCESSOR( ChangeVictoryCondition )
	PROCESSOR( StartSimulation )
	PROCESSOR( StopSimulation )
	PROCESSOR( SetSurfaceItem )
	PROCESSOR( SelectById )
	PROCESSOR( SelectByRect )
	PROCESSOR( Send )
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

	/*virtual*/ bool check( const Object& _object ) const
	{
		boost::intrusive_ptr< ILocateComponent > locationComponent
			= _object.getComponent< ILocateComponent >( ComponentId::Locate );

		return	locationComponent
			&&	locationComponent->getRect().intersects( m_rect );
	}

	const QRect m_rect;
};

/*---------------------------------------------------------------------------*/

struct ObjectsByIdFilter
	:	public ILandscape::IObjectsFilter
{
	ObjectsByIdFilter( const Object::Id& _id )
		:	m_id( _id )
	{}

	/*virtual*/ bool check( const Object& _object ) const
	{
		return _object.getUniqueId() == m_id;
	}

	const Object::Id m_id;
};

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
	,	m_actionsProcessingTaskHandle()
	,	m_simulationStartTimeStamp( 0 )
	,	m_landscape()
	,	m_filePath()
	,	m_players()
	,	m_myPlayerId( IPlayer::ms_wrondId )
	,	m_mutex( QMutex::Recursive )
	,	m_ticksCounter( 0 )
	,	m_workers()
	,	m_gameMode()
	,	m_victoryChecker( new StayAloneChecker( m_environment ) ) // TODO: should be set not in the constructor
	,	m_simulationBlocked( false )
{
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
		landscape( new Landscape( m_surfaceItemsCache, m_staticData, *this ) );

	try
	{
		m_landscapeSerializer.load( *landscape, _filePath );
	}
	catch( ... )
	{
	}

	m_landscape = landscape;
	m_filePath = _filePath;

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

	m_victoryChecker.reset( new EndlessChecker() );
	m_gameMode.reset();

	m_environment.removeTask( m_actionsProcessingTaskHandle );
	m_actionsProcessingTaskHandle.reset();

	m_simulationBlocked = false;

	m_simulationStartTimeStamp = 0;

	m_ticksCounter = 0;

	m_landscape.reset();
	m_filePath.clear();

	m_players.clear();
	m_workers.clear();

	m_myPlayerId = IPlayer::ms_wrondId;

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
			filePath = m_filePath;

		if ( filePath.isEmpty() )
			return;

		m_landscapeSerializer.save( *this, *m_landscape, _filePath );
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


const QString&
LandscapeModel::getFilePath() const
{
	return m_filePath;

} // LandscapeModel::getFilePath


/*---------------------------------------------------------------------------*/


const VictoryCondition::Enum
LandscapeModel::getVictoryConditionType() const
{
	return m_victoryChecker->getType();

} // LandscapeModel::getVictoryConditionType


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

	// TODO: const_cast
	const_cast< Command& >( _command ).m_timeStamp = Tools::Core::Time::currentTime() - m_simulationStartTimeStamp;
	const_cast< Command& >( _command ).m_pushToProcessingTick = m_ticksCounter;
	const_cast< Command& >( _command ).m_playerId = m_myPlayerId;

	m_gameMode->processCommand( _command );

} // LandscapeModel::pushCommand


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
	PlayersMapIterator iterator = m_players.find( _id );
	return iterator != m_players.end() ? iterator->second : boost::intrusive_ptr< IPlayer >();

} // LandscapeModel::getPlayer


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IPlayer >
LandscapeModel::getPlayer( const Object& _object ) const
{
	boost::intrusive_ptr< IPlayerComponent > playerComponent
		= _object.getComponent< IPlayerComponent >( ComponentId::Player );

	if ( !playerComponent )
		return boost::intrusive_ptr< IPlayer >();

	return getPlayer( playerComponent->getPlayerId() );

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
LandscapeModel::getPlayerByStartPoint( const StartPoint::Id& _id ) const
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


QMutex&
LandscapeModel::getMutex()
{
	return m_mutex;

} // LandscapeModel::getMutex


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
LandscapeModel::create( const QString& _objectName, const QPoint& _location, const IPlayer::Id& _playerId )
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
			,	boost::intrusive_ptr< IComponent >( new PlayerComponent( *object, *staticData.m_playerData, _playerId ) ) );

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
LandscapeModel::getWorker( const Object::Id& _id ) const
{
	WorkersCollectionIterator iterator = m_workers.find( _id );

	return		iterator != m_workers.end()
			?	iterator->second
			:	boost::shared_ptr< Object >();

} // LandscapeModel::getWorker


/*---------------------------------------------------------------------------*/


void
LandscapeModel::removeWorker( const Object::Id& _id )
{
	m_workers.erase( _id );

} // LandscapeModel::removeWorker


/*---------------------------------------------------------------------------*/


void
LandscapeModel::addWorker( boost::shared_ptr< Object > _worker )
{
	assert( m_workers.find( _worker->getUniqueId() ) == m_workers.end() );
	m_workers.insert( std::make_pair( _worker->getUniqueId(), _worker ) );

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
			Framework::Core::EventManager::Event( Events::CurrentTickNumberChanged::ms_type )
				.pushAttribute( Events::CurrentTickNumberChanged::ms_tickNumberAttribute, m_ticksCounter ) );

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
		m_environment.printMessage(
				Tools::Core::IMessenger::MessegeLevel::Warning
			,	QString( Resources::TimeLimitWarning ).arg( time ).arg( Resources::TimeLimit )  );
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
				m_staticData.getStartPointObjectName( begin->second->getRace() )
			,	m_landscape->getStartPoint( begin->second->getStartPointId() ).m_point
			,	begin->second->getUniqueId() );
	}

} // LandscapeModel::locateStartPointObjects


/*---------------------------------------------------------------------------*/


bool
LandscapeModel::shouldStoreResources( const Object& _holder, boost::shared_ptr< Object > _storage )
{
	boost::intrusive_ptr< IResourceHolderComponent > resourceHolderComponent
		= _holder.getComponent< IResourceHolderComponent >( ComponentId::ResourceHolder );
	boost::intrusive_ptr< IResourceStorageComponent > resourceStorageComponent
		= _storage->getComponent< IResourceStorageComponent >( ComponentId::ResourceStorage );

	if ( !resourceHolderComponent || !resourceStorageComponent )
		return false;

	boost::intrusive_ptr< IPlayerComponent > storagePlayerComponent
		= _storage->getComponent< IPlayerComponent >( ComponentId::Player );
	boost::intrusive_ptr< IPlayerComponent > holderPlayerComponent
		= _holder.getComponent< IPlayerComponent >( ComponentId::Player );

	assert( storagePlayerComponent );
	assert( holderPlayerComponent );

	if ( storagePlayerComponent->getPlayerId() != holderPlayerComponent->getPlayerId() )
		return false;

	IResourceStorageComponent::StaticData::StoredResourcesCollectionIterator
			begin = resourceStorageComponent->getStaticData().m_storedResources.begin()
		,	end = resourceStorageComponent->getStaticData().m_storedResources.end();

	for ( ; begin != end; ++begin )
	{
		if ( resourceHolderComponent->holdResources().getResourceValue( *begin ) > 0 )
			return true;
	}

	return false;

} // LandscapeModel::shouldStoreResources


/*---------------------------------------------------------------------------*/


void
LandscapeModel::initPlayers()
{
	m_players.clear();

	IStaticData::RacesCollection races;
	m_staticData.fetchRaces( races );

	ILandscape::StartPointsIterator iterator = m_landscape->getStartPointsIterator();

	while( iterator->isValid() )
	{
		boost::intrusive_ptr< Player > player(
			new Player( m_environment, m_staticData, races.begin()->first, iterator->current().m_id ) );
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

	assert( m_myPlayerId != IPlayer::ms_wrondId );

} // LandscapeModel::setupMyPlayer


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onStartSimulationProcessor( const Command& _command )
{
	if ( isSimulationRunning() || !m_gameMode )
		return;

	locateStartPointObjects();

	try
	{
		m_landscapeSerializer.loadObjects( *this, *m_landscape, m_filePath );
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

	m_environment.riseEvent( Framework::Core::EventManager::Event( Events::SimulationStarted::ms_type ) );

} // LandscapeModel::onStartSimulationProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onStopSimulationProcessor( const Command& _command )
{
	if ( !isSimulationRunning() )
		return;

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

	switch( condition )
	{
	case VictoryCondition::StayAlone:
		m_victoryChecker.reset( new StayAloneChecker( m_environment ) );
		break;
	default:
		m_victoryChecker.reset( new EndlessChecker() );
		break;
	}

	Framework::Core::EventManager::Event conditionChanged( Events::VictoryConditionChanged::ms_type );
	conditionChanged.pushAttribute( Events::VictoryConditionChanged::ms_conditionAttribute, condition );

	m_environment.riseEvent( conditionChanged );

} // LandscapeModel::onChangeVictoryConditionProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangePlayerRaceProcessor( const Command& _command )
{
	const IPlayer::Id id = _command.m_arguments[ 0 ].toInt();
	const QString race = _command.m_arguments[ 1 ].toString();

	PlayersMapIterator iterator = m_players.find( id );
	
	if ( iterator != m_players.end() )
	{
		iterator->second->setRace( race );

		Framework::Core::EventManager::Event playerRaceChangedEvent( Events::PlayerRaceChanged::ms_type );
		playerRaceChangedEvent.pushAttribute( Events::PlayerRaceChanged::ms_playerIdAttribute, id );
		playerRaceChangedEvent.pushAttribute( Events::PlayerRaceChanged::ms_playerRaceAttribute, race );

		m_environment.riseEvent( playerRaceChangedEvent );
	}

} // LandscapeModel::onChangePlayerRaceProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangePlayerTypeProcessor( const Command& _command )
{
	const IPlayer::Id id = _command.m_arguments[ 0 ].toInt();
	const PlayerType::Enum type = static_cast< PlayerType::Enum >( _command.m_arguments[ 1 ].toInt() );

	PlayersMapIterator iterator = m_players.find( id );
	
	if ( iterator != m_players.end() )
	{
		iterator->second->setType( type );

		Framework::Core::EventManager::Event playerTypeChangedEvent( Events::PlayerTypeChanged::ms_type );
		playerTypeChangedEvent.pushAttribute( Events::PlayerTypeChanged::ms_playerIdAttribute, id );
		playerTypeChangedEvent.pushAttribute( Events::PlayerTypeChanged::ms_playerTypeAttribute, type );

		m_environment.riseEvent( playerTypeChangedEvent );
	}

} // LandscapeModel::onChangePlayerTypeProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangePlayerNameProcessor( const Command& _command )
{
	const IPlayer::Id id = _command.m_arguments[ 0 ].toInt();
	const QString name = _command.m_arguments[ 1 ].toString();

	PlayersMapIterator iterator = m_players.find( id );
	
	if ( iterator != m_players.end() )
	{
		iterator->second->setName( name );

		Framework::Core::EventManager::Event playerNameChangedEvent( Events::PlayerNameChanged::ms_type );
		playerNameChangedEvent.pushAttribute( Events::PlayerNameChanged::ms_playerIdAttribute, id );
		playerNameChangedEvent.pushAttribute( Events::PlayerNameChanged::ms_playerNameAttribute, name );
		playerNameChangedEvent.pushAttribute( Events::PlayerNameChanged::ms_startPointIdAttribute, iterator->second->getStartPointId() );

		m_environment.riseEvent( playerNameChangedEvent );
	}

} // LandscapeModel::onChangePlayerNameProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onChangeMyPlayerProcessor( const Command& _command )
{
	const IPlayer::Id id = _command.m_arguments[ 0 ].toInt();
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
		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );
	}

} // LandscapeModel::onSelectByRectProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onSelectByIdProcessor( const Command& _command )
{
	if ( m_landscape )
	{
		m_landscape->selectObjects( ObjectsByIdFilter( _command.m_arguments[ 0 ].toInt() ) );
		m_environment.riseEvent( Framework::Core::EventManager::Event( Events::ObjectsSelectionChanged::ms_type ) );
	}

} // LandscapeModel::onSelectByIdProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onSendProcessor( const Command& _command )
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
			boost::shared_ptr< Object > object = m_landscape->getObject( begin->toInt() );
			boost::shared_ptr< Object > targetObject = m_landscape->getObject( location );

			if ( object )
			{
				boost::intrusive_ptr< IActionsComponent > actionsComponent
					= object->getComponent< IActionsComponent >( ComponentId::Actions );
				boost::intrusive_ptr< IMoveComponent > moveComponent
					= object->getComponent< IMoveComponent >( ComponentId::Move );
				boost::intrusive_ptr< IAttackComponent > attackComponent
					= object->getComponent< IAttackComponent >( ComponentId::Attack );
				boost::intrusive_ptr< IResourceHolderComponent > resourceHolderComponent
					= object->getComponent< IResourceHolderComponent >( ComponentId::ResourceHolder );
				boost::intrusive_ptr< IRepairComponent > repairComponent
					= object->getComponent< IRepairComponent >( ComponentId::Repair );

				boost::intrusive_ptr< IPlayerComponent > playerComponent
					= object->getComponent< IPlayerComponent >( ComponentId::Player);
				assert( playerComponent );

				if ( targetObject && targetObject != object )
				{
					boost::intrusive_ptr< IHealthComponent > targetHealthComponent
						= targetObject->getComponent< IHealthComponent >( ComponentId::Health );
					boost::intrusive_ptr< IPlayerComponent > targetPlayerComponent
						= targetObject->getComponent< IPlayerComponent >( ComponentId::Player );

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
							&&	!targetHealthComponent->isHealthy()
							&&	playerComponent
							&&	targetPlayerComponent
							&&	playerComponent->getPlayerId() == targetPlayerComponent->getPlayerId() )
					{
						actionsComponent->pushAction(
								boost::intrusive_ptr< IAction >( new RepairAction( m_environment, *this, *object, targetObject ) )
							,	flush );
					}
					else if (	attackComponent
							&&	targetHealthComponent
							&&	playerComponent
							&&	targetPlayerComponent
							&&	playerComponent->getPlayerId() != targetPlayerComponent->getPlayerId() )
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
				else if ( moveComponent )
				{
					actionsComponent->pushAction(
							boost::intrusive_ptr< IAction >( new MoveAction( m_environment, *this, *object, location ) )
						,	flush );
				}
			}
		}
	}

} // LandscapeModel::onSendProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onCreateObjectProcessor( const Command& _command )
{
	Object::Id objectId = Object::ms_wrongId;

	const IPlayer::Id id = _command.m_arguments[ 0 ].toInt();
	const QString name = _command.m_arguments[ 1 ].toString();
	const QPoint location = _command.m_arguments[ 2 ].toPoint();

	if ( m_landscape )
	{
		objectId = m_landscape->createObject( name, location, id );
	}

	if ( objectId != Object::ms_wrongId )
	{
		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::ObjectAdded::ms_type )
				.pushAttribute( Events::ObjectAdded::ms_objectNameAttribute, name )
				.pushAttribute( Events::ObjectAdded::ms_objectLocationAttribute, location )
				.pushAttribute( Events::ObjectAdded::ms_objectUniqueIdAttribute, objectId )
				.pushAttribute( Events::ObjectAdded::ms_objectEmplacementAttribute, m_staticData.getObjectStaticData( name ).m_locateData->m_emplacement ) );
	}
	else
	{
		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::CreateObjectFailed::ms_type )
				.pushAttribute( Events::CreateObjectFailed::ms_objectNameAttribute, name )
				.pushAttribute( Events::CreateObjectFailed::ms_objectLocationAttribute, location ) );
	}

} // LandscapeModel::onCreateObjectProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onSetSurfaceItemProcessor( const Command& _command )
{
	if ( m_landscape )
	{
		const QPoint location = _command.m_arguments[ 0 ].toPoint();
		const ISurfaceItem::Id id = _command.m_arguments[ 1 ].toInt();

		m_landscape->setSurfaceItem( location, id );

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::SurfaceItemChanged::ms_type )
				.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemIdAttribute, id )
				.pushAttribute( Events::SurfaceItemChanged::ms_surfaceItemLocationAttribute, location ) );
	}

} // LandscapeModel::onSetSurfaceItemProcessor


/*---------------------------------------------------------------------------*/


void
LandscapeModel::onTrainObjectProcessor( const Command& _command )
{
	if ( !m_landscape )
		return;

	const Object::Id parentId = _command.m_arguments[ 0 ].toInt();
	const QString name = _command.m_arguments[ 1 ].toString();

	boost::shared_ptr< Object > object = m_landscape->getObject( parentId );

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
						Framework::Core::EventManager::Event( Events::TrainQueueChanged::ms_type )
							.pushAttribute( Events::TrainQueueChanged::ms_trainerIdAttribute, object->getUniqueId() ) );
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
		const Object::Id builderId = _command.m_arguments[ 0 ].toInt();
		const QString name = _command.m_arguments[ 1 ].toString();
		const QPoint location = _command.m_arguments[ 2 ].toPoint();
		const bool flush = _command.m_arguments[ 3 ].toBool();

		boost::shared_ptr< Object > object = m_landscape->getObject( builderId );

		if ( object )
		{
			boost::intrusive_ptr< IActionsComponent > actionsComponent
				= object->getComponent< IActionsComponent >( ComponentId::Actions );

			actionsComponent->pushAction(
				boost::intrusive_ptr< IAction >( new BuildAction( m_environment, *this, *this, m_staticData, *object, name, location ) ), flush );
		}
	}

} // LandscapeModel::onBuildObjectProcessor


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
