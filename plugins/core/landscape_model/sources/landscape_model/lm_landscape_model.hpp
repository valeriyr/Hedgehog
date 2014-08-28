
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
struct ISurfaceItemsCache;
struct IStaticData;
struct ILandscapeSerializer;
struct ILandscape;
struct IModelLocker;
struct IPathFinder;
struct IGameMode;

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

	LandscapeModel(
			const IEnvironment& _environment
		,	ILandscapeSerializer& _landscapeSerializer
		,	const ISurfaceItemsCache& _surfaceItemsCache
		,	const IStaticData& _staticData );

	virtual ~LandscapeModel();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initLandscape( const QString& _filePath );

	/*virtual*/ void setupMultiPlayerGame();

	/*virtual*/ void connectToMultiPlayerGame( const Framework::Core::NetworkManager::ConnectionInfo& _connectTo );

	/*virtual*/ void setupSinglePlayerGame();

	/*virtual*/ void resetModel();

	/*virtual*/ void saveModel( const QString& _filePath );

	/*virtual*/ void startSimulation();

	/*virtual*/ bool isSimulationRunning() const;

	/*virtual*/ bool isConfigurated() const;

	/*virtual*/ const QString& getFilePath() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushCommand( const Command& _command );

	COMMAND_MAP_DECLARE()

/*---------------------------------------------------------------------------*/

	/*virtual*/ void getTrainObjectsList(
			boost::shared_ptr< Object > _forObject
		,	ILandscapeModel::TrainObjectsList& _list ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getLandscape() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const IPlayer::Id& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const Object& _object ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const QString& _name ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayerByStartPoint( const StartPoint::Id& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getMyPlayer() const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getFirstFreePlayer() const;

	/*virtual*/ void fetchPlayers( ILandscapeModel::PlayersCollection& _collection ) const;

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

	void onChangePlayerRaceProcessor( const Command& _command );

	void onChangePlayerTypeProcessor( const Command& _command );

	void onChangePlayerNameProcessor( const Command& _command );

	void onSelectByRectProcessor( const Command& _command );

	void onSelectByIdProcessor( const Command& _command );

	void onSendProcessor( const Command& _command );

	void onCreateObjectProcessor( const Command& _command );

	void onSetSurfaceItemProcessor( const Command& _command );

	void onTrainObjectProcessor( const Command& _command );

	void onBuildObjectProcessor( const Command& _command );

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

	ILandscapeSerializer& m_landscapeSerializer;

	const ISurfaceItemsCache& m_surfaceItemsCache;

	const IStaticData& m_staticData;

/*---------------------------------------------------------------------------*/

	Framework::Core::MultithreadingManager::TaskHandle m_actionsProcessingTaskHandle;

	Tools::Core::Time::Milliseconds m_simulationStartTimeStamp;

	boost::intrusive_ptr< ILandscape > m_landscape;

	QString m_filePath;

	PlayersMap m_players;

	IPlayer::Id m_myPlayerId;

	QMutex m_mutex;

	TickType m_ticksCounter;

	WorkersCollection m_workers;

	boost::intrusive_ptr< IGameMode > m_gameMode;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_MODEL_HPP__
