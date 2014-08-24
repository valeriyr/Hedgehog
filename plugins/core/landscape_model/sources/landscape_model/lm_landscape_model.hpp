
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
struct IPlayer;
struct IModelLocker;
struct IPathFinder;
struct IGameMode;

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

	/*virtual*/ void setStartPointRace( const StartPoint::Id& _id, const QString& _race );

	/*virtual*/ void setStartPointType( const StartPoint::Id& _id, const PlayerType::Enum& _type );

	/*virtual*/ QString getStartPointDataRace( const StartPoint::Id& _id );

	/*virtual*/ PlayerType::Enum getStartPointDataType( const StartPoint::Id& _id );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void selectObjects( const QRect& _rect );

	/*virtual*/ void selectObject( const Object::Id& _id );

	/*virtual*/ void sendSelectedObjects( const QPoint& _to, const bool _flush );

	/*virtual*/ void createObject( const QPoint& _location, const QString& _objectName, const IPlayer::Id& _playerId );

	/*virtual*/ void setSurfaceItem(
			const QPoint& _location
		,	const Core::LandscapeModel::ISurfaceItem::Id& _id );

	/*virtual*/ void trainObject( const Object::Id& _parentObject, const QString& _objectName );

	/*virtual*/ void buildObject(
			const Object::Id& _builder
		,	const QString& _objectName
		,	const QPoint& _atLocation
		,	const bool _flush );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void getTrainObjectsList(
			boost::shared_ptr< Object > _forObject
		,	ILandscapeModel::TrainObjectsList& _list ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getLandscape() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const IPlayer::Id& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayer( const Object& _object ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getPlayerByStartPoint( const StartPoint::Id& _id ) const;

	/*virtual*/ boost::intrusive_ptr< IPlayer > getMyPlayer() const;

	/*virtual*/ ILandscapeModel::PlayersIterator getPlayersIterator() const;

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

	void fillStartPointDefaultData();

	void initPlayers();

	void locateStartPointObjects();

	bool shouldStoreResources( boost::shared_ptr< Object > _holder, boost::shared_ptr< Object > _storage );

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
		std::map< IPlayer::Id, boost::intrusive_ptr< IPlayer > >
		PlayersCollection;
	typedef
		PlayersCollection::const_iterator
		PlayersCollectionIterator;

/*---------------------------------------------------------------------------*/

	struct StartPointData
	{
		StartPointData(
				const PlayerType::Enum _playerType
			,	const QString& _race
			)
			:	m_playerType( _playerType )
			,	m_race( _race )
		{}

		PlayerType::Enum m_playerType;
		QString m_race;
	};

	typedef
		std::map< StartPoint::Id, StartPointData >
		StartPointDataCollection;
	typedef
		StartPointDataCollection::iterator
		StartPointDataCollectionIterator;

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

	PlayersCollection m_players;

	StartPointDataCollection m_startPointData;

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
