
#ifndef __LM_LANDSCAPE_MODEL_HPP__
#define __LM_LANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/landscape/lm_iobjects_creator.hpp"
#include "landscape_model/sources/actions/lm_iworkers_holder.hpp"

#include "landscape_model/h/lm_constants.hpp"

#include "multithreading_manager/h/mm_task_handle.hpp"

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

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushCommand( const Command& _command );

	COMMAND_MAP_DECLARE()

/*---------------------------------------------------------------------------*/

	/*virtual*/ void getTrainObjectsList(
			boost::shared_ptr< Object > _forObject
		,	ILandscapeModel::TrainObjectsList& _list ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getLandscape() const;

	/*virtual*/ const QString& getLandscapeFilePath() const;

	/*virtual*/ QString getLandscapeName() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const IPlayer::Id& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const Object& _object ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const QString& _name ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayerByStartPoint( const StartPoint::Id& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getMyPlayer() const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getFirstFreePlayer() const;

	/*virtual*/ void fetchPlayers( ILandscapeModel::PlayersCollection& _collection ) const;

	/*virtual*/ bool twoOrMoreActivatedPlayers() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool isMyObject( const Object::Id& _objectId ) const;

	/*virtual*/ bool isMyObject( boost::shared_ptr< Object > _object ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void fetchWorkers( ILandscape::ObjectsCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	QMutex& getMutex();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< Object > create(
			const QString& _objectName
		,	const QPoint& _location
		,	const IPlayer::Id& _playerId );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< Object > getWorker( const Object::Id& _id ) const;

	/*virtual*/ void removeWorker( const Object::Id& _id );

	/*virtual*/ void addWorker( boost::shared_ptr< Object > _worker );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void gameMainLoop();

/*---------------------------------------------------------------------------*/

	void locateStartPointObjects();

	bool shouldStoreResources( const Object& _holder, boost::shared_ptr< Object > _storage );

/*---------------------------------------------------------------------------*/

	void initPlayers();

	void setupMyPlayer();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	DECLARE_PROCESSOR( ChangeVictoryCondition )
	DECLARE_PROCESSOR( StartSimulation )
	DECLARE_PROCESSOR( StopSimulation )
	DECLARE_PROCESSOR( SetSurfaceItem )
	DECLARE_PROCESSOR( SelectById )
	DECLARE_PROCESSOR( SelectByRect )
	DECLARE_PROCESSOR( Send )
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

	typedef
		std::map< Object::Id, boost::shared_ptr< Object > >
		WorkersCollection;
	typedef
		WorkersCollection::const_iterator
		WorkersCollectionIterator;

	typedef
		std::map< IPlayer::Id, boost::intrusive_ptr< Player > >
		PlayersMap;
	typedef
		PlayersMap::const_iterator
		PlayersMapIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

	Framework::Core::MultithreadingManager::TaskHandle m_actionsProcessingTaskHandle;

	Tools::Core::Time::Milliseconds m_simulationStartTimeStamp;

	boost::intrusive_ptr< ILandscape > m_landscape;

	QString m_landscapeFilePath;

	PlayersMap m_players;

	IPlayer::Id m_myPlayerId;

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
