
#ifndef __LM_LANDSCAPE_MODEL_HPP__
#define __LM_LANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/landscape/lm_iobjects_creator.hpp"
#include "landscape_model/sources/actions/lm_iworkers_holder.hpp"

#include "landscape_model/h/lm_constants.hpp"

#include "landscape_model/sources/unique_id_generator/lm_unique_id_generator.hpp"

#include "multithreading_manager/h/mm_task_handle.hpp"
#include "event_manager/h/em_subscriber.hpp"

#include "time/t_time.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ILandscape;
struct IModelLocker;
struct IPathFinder;
struct IGameMode;
struct IVictoryChecker;

class Player;

/*---------------------------------------------------------------------------*/

class LandscapeModel
	:	public Tools::Core::BaseWrapper< ILandscapeModel >
	,	private IObjectCreator
	,	private IWorkersHolder
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeModel( const IEnvironment& _environment );

	virtual ~LandscapeModel();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initLandscape( const QString& _filePath );

	/*virtual*/ void setupMultiPlayerGame();

	/*virtual*/ void connectToMultiPlayerGame( const Framework::Core::NetworkManager::ConnectionInfo& _connectTo );

	/*virtual*/ void setupSinglePlayerGame();

	/*virtual*/ void resetModel();

	/*virtual*/ void saveModel( const QString& _filePath );

	/*virtual*/ bool isSimulationRunning() const;

	/*virtual*/ bool isConfigurated() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setupReplay( const QString& _filePath );

	/*virtual*/ void saveReplay( const QString& _filePath );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const VictoryCondition::Enum getVictoryConditionType() const;

	/*virtual*/ const IGameMode::Type::Enum getGameModeType() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushCommand( const Command& _command );

	/*virtual*/ bool hasMoreCommands() const;

	COMMAND_MAP_DECLARE()

/*---------------------------------------------------------------------------*/

	/*virtual*/ void getTrainObjectsList(
			boost::shared_ptr< GameObject > _forObject
		,	ILandscapeModel::TrainObjectsList& _list ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getLandscape() const;

	/*virtual*/ const QString& getLandscapeFilePath() const;

	/*virtual*/ QString getLandscapeName() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const Tools::Core::Generators::IGenerator::IdType& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const GameObject& _object ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const QString& _name ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayerByStartPoint( const Tools::Core::Generators::IGenerator::IdType& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getMyPlayer() const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getFirstFreePlayer() const;

	/*virtual*/ void fetchPlayers( ILandscapeModel::PlayersCollection& _collection ) const;

	/*virtual*/ bool twoOrMoreActivatedPlayers() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isMyObject( const Tools::Core::Generators::IGenerator::IdType& _objectId ) const;

	/*virtual*/ bool isMyObject( boost::shared_ptr< GameObject > _object ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void fetchWorkers( ILandscape::ObjectsCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	QMutex& getMutex();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< GameObject > create(
			const QString& _objectName
		,	const QPoint& _location
		,	const Tools::Core::Generators::IGenerator::IdType& _playerId );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< GameObject > getWorker( const Tools::Core::Generators::IGenerator::IdType& _id ) const;

	/*virtual*/ void removeWorker( const Tools::Core::Generators::IGenerator::IdType& _id );

	/*virtual*/ void addWorker( boost::shared_ptr< GameObject > _worker );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void gameMainLoop();

/*---------------------------------------------------------------------------*/

	void locateStartPointObjects();

	bool shouldStoreResources( const GameObject& _holder, boost::shared_ptr< GameObject > _storage );

	void initPlayers();

	void setupMyPlayer();

	void initVictoryChecker( const VictoryCondition::Enum _condition );

	void processAIThinkCall();

	void processAIPlayersGoals();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	DECLARE_PROCESSOR( ChangeVictoryCondition )
	DECLARE_PROCESSOR( StartSimulation )
	DECLARE_PROCESSOR( StopSimulation )
	DECLARE_PROCESSOR( SetSurfaceItem )
	DECLARE_PROCESSOR( SelectById )
	DECLARE_PROCESSOR( SelectByRect )
	DECLARE_PROCESSOR( SendToPoint )
	DECLARE_PROCESSOR( SendToObject )
	DECLARE_PROCESSOR( CreateObject )
	DECLARE_PROCESSOR( TrainObject )
	DECLARE_PROCESSOR( BuildObject )
	DECLARE_PROCESSOR( ChangePlayerRace )
	DECLARE_PROCESSOR( ChangePlayerType )
	DECLARE_PROCESSOR( ChangePlayerName )
	DECLARE_PROCESSOR( ChangeMyPlayer )

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onEvent( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< Tools::Core::Generators::IGenerator::IdType, boost::shared_ptr< GameObject > >
		WorkersCollection;
	typedef
		WorkersCollection::const_iterator
		WorkersCollectionIterator;

	typedef
		std::map< Tools::Core::Generators::IGenerator::IdType, boost::intrusive_ptr< Player > >
		PlayersMap;
	typedef
		PlayersMap::const_iterator
		PlayersMapIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	UniqueIdGenerator m_playersIdsGenerator;

	UniqueIdGenerator m_objectsIdsGenerator;

/*---------------------------------------------------------------------------*/

	Framework::Core::EventManager::Subscriber m_subscriber;

	Framework::Core::MultithreadingManager::TaskHandle m_actionsProcessingTaskHandle;

	Tools::Core::Time::Milliseconds m_simulationStartTimeStamp;

	boost::intrusive_ptr< ILandscape > m_landscape;

	QString m_landscapeFilePath;

	PlayersMap m_players;

	Tools::Core::Generators::IGenerator::IdType m_myPlayerId;

	QMutex m_mutex;

	TickType m_ticksCounter;

	WorkersCollection m_workers;

	boost::intrusive_ptr< IGameMode > m_gameMode;

	boost::intrusive_ptr< IVictoryChecker > m_victoryChecker;

	bool m_simulationBlocked;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_MODEL_HPP__
