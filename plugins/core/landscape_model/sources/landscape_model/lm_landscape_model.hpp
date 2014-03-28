
#ifndef __LM_LANDSCAPE_MODEL_HPP__
#define __LM_LANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/landscape/lm_iobjects_creator.hpp"

#include "multithreading_manager/h/mm_task_handle.hpp"

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

/*---------------------------------------------------------------------------*/

class LandscapeModel
	:	public Tools::Core::BaseWrapper< ILandscapeModel >
	,	public IObjectCreator
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeModel(
			const IEnvironment& _environment
		,	const ILandscapeSerializer& _landscapeSerializer
		,	const ISurfaceItemsCache& _surfaceItemsCache
		,	const IStaticData& _staticData );

	virtual ~LandscapeModel();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initModel( const QString& _filePath );

	/*virtual*/ void resetModel();

	/*virtual*/ void saveModel( const QString& _filePath );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IModelLocker > lockModel();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void selectObjects( const QRect& _rect );

	/*virtual*/ void selectObject( const Object::Id& _id );

	/*virtual*/ void sendSelectedObjects( const QPoint& _to, const bool _flush );

	/*virtual*/ void createObject( const QPoint& _location, const QString& _objectName );

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

	/*virtual*/ void startBuild(
			const Object::Id& _id
		,	const QString& _objectName
		,	const QPoint& _location );

	/*virtual*/ void stopBuild( const Object::Id& _id );

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< Object > create(
			const QPoint& _location
		,	const QString& _objectName );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void gameMainLoop();

	void initTask( const QString& _filePath );

	void resetTask();

	void saveTask( const QString& _filePath );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< Object::Id, boost::shared_ptr< Object > >
		BuildersCollection;
	typedef
		BuildersCollection::iterator
		BuildersCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const ILandscapeSerializer& m_landscapeSerializer;

	const ISurfaceItemsCache& m_surfaceItemsCache;

	const IStaticData& m_staticData;

/*---------------------------------------------------------------------------*/

	Framework::Core::MultithreadingManager::TaskHandle m_actionsProcessingTaskHandle;

	boost::intrusive_ptr< ILandscape > m_currentLandscape;

	boost::intrusive_ptr< IPlayer > m_player;

	QMutex m_mutex;

/*---------------------------------------------------------------------------*/

	BuildersCollection m_builders;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_MODEL_HPP__
