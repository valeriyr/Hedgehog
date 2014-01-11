
#ifndef __LM_ILANDSCAPE_HANDLE_HPP__
#define __LM_ILANDSCAPE_HANDLE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_iplayer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeHandle
	:	public Tools::Core::IBase
{
	virtual boost::intrusive_ptr< ILandscape > getLandscape() const = 0;

	virtual boost::intrusive_ptr< IPlayer > getPlayer() const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HANDLE_HPP__
