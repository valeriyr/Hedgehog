
#ifndef __WM_IWINDOW_MANAGER_HPP__
#define __WM_IWINDOW_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "window_manager/h/wm_view_position.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

	const quint32 IID_WINDOW_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IView;

/*---------------------------------------------------------------------------*/

struct IWindowManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void addView(
			boost::intrusive_ptr< IView > _view
		,	const ViewPosition::Enum _position ) = 0;

	virtual void removeView( boost::intrusive_ptr< IView > _view ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void addCommandToMenu(
			const QString& _menuPath
		,	const QString& _commandName ) = 0;

	virtual void removeCommandFromMenu( const QString& _menuPath ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_IWINDOW_MANAGER_HPP__
