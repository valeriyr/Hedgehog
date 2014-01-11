
#ifndef __LM_ILANDSCAPE_HANDLE_INTERNAL_HPP__
#define __LM_ILANDSCAPE_HANDLE_INTERNAL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/sources/landscape/lm_ieditable_landscape.hpp"
#include "landscape_model/sources/player/lm_ieditable_player.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeHandleInternal
	:	public ILandscapeHandle
{
/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IEditableLandscape > getEditableLandscape() const = 0;

	virtual boost::intrusive_ptr< IEditablePlayer > getEditablePlayer() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HANDLE_INTERNAL_HPP__
