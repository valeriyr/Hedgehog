
#ifndef __WM_WINDOW_MANAGER_HPP__
#define __WM_WINDOW_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iwindow_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

class WindowManager
	:	public QObject
	,	public Tools::Core::BaseWrapper< IWindowManager >
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	WindowManager( const std::string& _applicationName );

	virtual ~WindowManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addView(
			boost::intrusive_ptr< IView > _view
		,	const ViewPosition::Enum _position );

	/*virtual*/ void removeView( boost::intrusive_ptr< IView > _view );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static Qt::DockWidgetArea getQtViewPossition( const ViewPosition::Enum _viewPossition );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< QMainWindow > m_mainWindow;

	typedef
		std::map< boost::intrusive_ptr< IView >, QDockWidget* >
		DockWidgetByViewCollection;
	typedef
		DockWidgetByViewCollection::const_iterator
		DockWidgetByViewCollectionIterator;

	DockWidgetByViewCollection m_dockWidgetByViewCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_WINDOW_MANAGER_HPP__
