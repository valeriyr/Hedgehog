
#ifndef __LV_IGAME_INITIALIZER_HPP__
#define __LV_IGAME_INITIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IGameInitializer
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void run() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IGAME_INITIALIZER_HPP__
