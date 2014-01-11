
#ifndef __LM_LANDSCAPE_MODEL_HPP__
#define __LM_LANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_model.hpp"

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
struct ILandscapeHandle;
struct IPathFinder;

/*---------------------------------------------------------------------------*/

class LandscapeModel
	:	public Tools::Core::BaseWrapper< ILandscapeModel >
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

	/*virtual*/ void initCurrentLandscape ( const QString& _filePath );

	/*virtual*/ void closeCurrentLandscape();

	/*virtual*/ void saveLandscape( const QString& _filePath ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscapeHandle > getCurrentLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void selectObjects( const QRect& _rect );

	/*virtual*/ void selectObject( const Object::UniqueId& _id );

	/*virtual*/ void moveSelectedObjects( const QPoint& _to );

	/*virtual*/ void createObject( const QPoint& _location, const QString& _objectName );

	/*virtual*/ void setSurfaceItem(
			const QPoint& _location
		,	const Core::LandscapeModel::ISurfaceItem::Id& _id );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void gameMainLoop();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const ILandscapeSerializer& m_landscapeSerializer;

	const ISurfaceItemsCache& m_surfaceItemsCache;

	const IStaticData& m_staticData;

/*---------------------------------------------------------------------------*/

	Framework::Core::MultithreadingManager::TaskHandle m_actionsProcessingTaskHandle;

	boost::intrusive_ptr< ILandscape > m_currentLandscape;

	boost::intrusive_ptr< IPlayer > m_player;

	QMutex m_landscapeLocker;

	boost::intrusive_ptr< IPathFinder > m_pathFinder;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_MODEL_HPP__
