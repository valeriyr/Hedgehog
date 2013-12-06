
#ifndef __LM_LANDSCAPE_MANAGER_HPP__
#define __LM_LANDSCAPE_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_manager/lm_ilandscape_manager_internal.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemsCache;
struct ILandscapeSerializer;

/*---------------------------------------------------------------------------*/

class LandscapeManager
	:	public Tools::Core::BaseWrapper< ILandscapeManagerInternal >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeManager(
			const ILandscapeSerializer& _landscapeSerializer
		,	const ISurfaceItemsCache& _surfaceItemsCache );

	virtual ~LandscapeManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initCurrentLandscape ( const QString& _filePath );

	/*virtual*/ void closeCurrentLandscape();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IEditableLandscape > getCurrentLandscape() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ QMutex& getLandscapeLocker();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeSerializer& m_landscapeSerializer;

	const ISurfaceItemsCache& m_surfaceItemsCache;

	boost::intrusive_ptr< IEditableLandscape > m_currentLandscape;

	QMutex m_landscapeLocker;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_MANAGER_HPP__
