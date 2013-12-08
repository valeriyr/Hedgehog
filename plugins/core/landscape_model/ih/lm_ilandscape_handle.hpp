
#ifndef __LM_ILANDSCAPE_HANDLE_HPP__
#define __LM_ILANDSCAPE_HANDLE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeHandle
	:	public Tools::Core::IBase
{
	virtual boost::intrusive_ptr< IEditableLandscape > getLandscape() const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HANDLE_HPP__
