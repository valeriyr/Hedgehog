
#ifndef __LE_IBASE_VIEW_HPP__
#define __LE_IBASE_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IBaseView
	:	public Framework::GUI::WindowManager::IView
{

/*---------------------------------------------------------------------------*/

	virtual void landscapeWasOpened() = 0;

	virtual void landscapeWasClosed() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_IBASE_VIEW_HPP__
