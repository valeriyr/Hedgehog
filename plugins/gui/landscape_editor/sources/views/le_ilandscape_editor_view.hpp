
#ifndef __LE_LANDSCAPE_EDITOR_VIEW_HPP__
#define __LE_LANDSCAPE_EDITOR_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct ILandscapeEditorView
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

#endif // __LE_LANDSCAPE_EDITOR_VIEW_HPP__
