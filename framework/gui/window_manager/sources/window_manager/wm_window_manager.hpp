
#ifndef __WM_WINDOW_MANAGER_HPP__
#define __WM_WINDOW_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iwindow_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

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

	WindowManager( const QString& _applicationName, IEnvironment& _environment );

	virtual ~WindowManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addView(
			boost::intrusive_ptr< IView > _view
		,	const ViewPosition::Enum _position );

	/*virtual*/ void removeView( boost::intrusive_ptr< IView > _view );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addCommandToMenu(
			const QString& _menuPath
		,	const QString& _commandName );

	/*virtual*/ void removeCommandFromMenu( const QString& _menuPath );

/*---------------------------------------------------------------------------*/

	QWidget& getMainWindow() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static Qt::DockWidgetArea getQtViewPossition( const ViewPosition::Enum _viewPossition );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< boost::intrusive_ptr< IView >, QDockWidget* >
		DockWidgetByViewCollection;
	typedef
		DockWidgetByViewCollection::const_iterator
		DockWidgetByViewCollectionIterator;

	typedef
		std::set< boost::intrusive_ptr< IView > >
		CentralViewsCollection;
	typedef
		CentralViewsCollection::const_iterator
		CentralViewsCollectionIterator;

/*---------------------------------------------------------------------------*/

	IEnvironment& m_environment;

	boost::shared_ptr< QMainWindow > m_mainWindow;

	QTabWidget* m_centralWidget;

	DockWidgetByViewCollection m_dockWidgetByViewCollection;

	CentralViewsCollection m_centralViewsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_WINDOW_MANAGER_HPP__
