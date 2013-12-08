
#ifndef __LM_LANDSCAPE_MODEL_HPP__
#define __LM_LANDSCAPE_MODEL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/lm_ilandscape_model_internal.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemsCache;
struct IObjectTypesCache;
struct ILandscapeSerializer;
struct IEditableLandscape;
struct ILandscapeHandle;

/*---------------------------------------------------------------------------*/

class LandscapeModel
	:	public Tools::Core::BaseWrapper< ILandscapeModelInternal >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeModel(
			const ILandscapeSerializer& _landscapeSerializer
		,	const ISurfaceItemsCache& _surfaceItemsCache
		,	const IObjectTypesCache& _objectTypesCache );

	virtual ~LandscapeModel();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initCurrentLandscape ( const QString& _filePath );

	/*virtual*/ void closeCurrentLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ILandscape > getCurrentLandscapeInternal() const;

	/*virtual*/ boost::intrusive_ptr< ILandscapeHandle > getCurrentLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ QMutex& getLandscapeLocker();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeSerializer& m_landscapeSerializer;

	const ISurfaceItemsCache& m_surfaceItemsCache;

	const IObjectTypesCache& m_objectTypesCache;

	boost::intrusive_ptr< IEditableLandscape > m_currentLandscape;

	QMutex m_landscapeLocker;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_MODEL_HPP__
