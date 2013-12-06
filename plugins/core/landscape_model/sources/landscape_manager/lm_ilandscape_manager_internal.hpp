
#ifndef __LM_ILANDSCAPE_MANAGER_INTERNAL_HPP__
#define __LM_ILANDSCAPE_MANAGER_INTERNAL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeManagerInternal
	:	public ILandscapeManager
{

/*---------------------------------------------------------------------------*/

	virtual QMutex& getLandscapeLocker() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MANAGER_INTERNAL_HPP__
