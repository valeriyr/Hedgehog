
#ifndef __LM_ILANDSCAPE_MODEL_INTERNAL_HPP__
#define __LM_ILANDSCAPE_MODEL_INTERNAL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_model.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	struct ILandscape;

/*---------------------------------------------------------------------------*/

struct ILandscapeModelInternal
	:	public ILandscapeModel
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ILandscape > getCurrentLandscapeInternal() const = 0;

	virtual QMutex& getLandscapeLocker() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_MODEL_INTERNAL_HPP__
