
#ifndef __WM_WINDOW_MANAGER_HPP__
#define __WM_WINDOW_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iwindow_manager.hpp"

#include "window_manager/h/wm_view_position.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

class WindowManager
	:	public Tools::Core::BaseWrapper< IWindowManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	WindowManager( const std::string& _applicationName );

	virtual ~WindowManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addView( boost::intrusive_ptr< IView > _view );

	/*virtual*/ void removeView( boost::intrusive_ptr< IView > _view );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static Qt::DockWidgetArea getQtViewPossition( const ViewPosition::Enum _viewPossition );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< QMainWindow > m_mainWindow;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_WINDOW_MANAGER_HPP__
