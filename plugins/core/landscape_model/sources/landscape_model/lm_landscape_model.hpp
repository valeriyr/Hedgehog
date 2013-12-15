
#ifndef __LM_LANDSCAPE_MODEL_HPP__
#define __LM_LANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/lm_ilandscape_model_internal.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ISurfaceItemsCache;
struct IObjectTypesCache;
struct ILandscapeSerializer;
struct IEditableLandscape;
struct ILandscapeHandle;
struct IActionsQueue;

/*---------------------------------------------------------------------------*/

class LandscapeModel
	:	public Tools::Core::BaseWrapper< ILandscapeModelInternal >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeModel(
			const IEnvironment& _environment
		,	const ILandscapeSerializer& _landscapeSerializer
		,	const ISurfaceItemsCache& _surfaceItemsCache
		,	const IObjectTypesCache& _objectTypesCache );

	virtual ~LandscapeModel();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initCurrentLandscape ( const QString& _filePath );

	/*virtual*/ void closeCurrentLandscape();

	/*virtual*/ void saveLandscape( const QString& _filePath ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IEditableLandscape > getCurrentLandscapeInternal() const;

	/*virtual*/ boost::intrusive_ptr< ILandscapeHandle > getCurrentLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ QMutex& getLandscapeLocker();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void selectUnits( const QRect& _rect );

	/*virtual*/ void createObject(
			const QRect& _rect
		,	const QString& _objectName );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void runActionsProcessing();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static const int ms_actionsProcessPerisod = 100;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const ILandscapeSerializer& m_landscapeSerializer;

	const ISurfaceItemsCache& m_surfaceItemsCache;

	const IObjectTypesCache& m_objectTypesCache;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IEditableLandscape > m_currentLandscape;

	QMutex m_landscapeLocker;

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< IActionsQueue > m_actionsQueue;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_MODEL_HPP__
