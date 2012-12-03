
#ifndef __WM_IWINDOW_MANAGER_HPP__
#define __WM_IWINDOW_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "window_manager/ih/wm_iview.hpp"
#include "window_manager/h/wm_view_position.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_WINDOW_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IWindowManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void addView( IView::Ptr _view, const ViewPosition::Enum _position ) = 0;

	virtual void removeView( IView::Ptr _view ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_IWINDOW_MANAGER_HPP__
