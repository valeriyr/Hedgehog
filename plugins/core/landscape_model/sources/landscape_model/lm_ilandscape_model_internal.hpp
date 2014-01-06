
#ifndef __LM_ILANDSCAPE_MODEL_INTERNAL_HPP__
#define __LM_ILANDSCAPE_MODEL_INTERNAL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_model.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeHandleInternal;
struct IEditableLandscape;

/*---------------------------------------------------------------------------*/

struct ILandscapeModelInternal
	:	public ILandscapeModel
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IEditableLandscape > getCurrentLandscapeInternal() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ILandscapeHandleInternal > getCurrentEditableLandscape() = 0;

	virtual QMutex& getLandscapeLocker() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MODEL_INTERNAL_HPP__
