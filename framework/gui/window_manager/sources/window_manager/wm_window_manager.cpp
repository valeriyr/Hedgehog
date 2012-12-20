
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/window_manager/wm_window_manager.hpp"

#include "window_manager/ih/wm_iview.hpp"

#include "window_manager/sources/internal_resources/wm_internal_resources.hpp"

#include "wm_window_manager.moc"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/


WindowManager::WindowManager( const std::string& _applicationName )
	:	m_mainWindow( new QMainWindow() )
	,	m_centralWidget( new QTabWidget() )
	,	m_dockWidgetByViewCollection()
	,	m_centralViewsCollection()
{
	// m_centralWidget->setTabsClosable( true );

	m_mainWindow->setWindowTitle( _applicationName.c_str() );
	m_mainWindow->setCentralWidget( m_centralWidget );
	m_mainWindow->showMaximized();

} // WindowManager::WindowManager


/*---------------------------------------------------------------------------*/


WindowManager::~WindowManager()
{
	assert( m_dockWidgetByViewCollection.empty() );
	assert( m_centralViewsCollection.empty() );

	m_centralViewsCollection.clear();

	m_mainWindow.reset();

} // WindowManager::~WindowManager


/*---------------------------------------------------------------------------*/


void
WindowManager::addView(
		boost::intrusive_ptr< IView > _view
	,	const ViewPosition::Enum _position )
{
	assert( m_dockWidgetByViewCollection.find( _view ) == m_dockWidgetByViewCollection.end() );

	if ( _position == ViewPosition::Center )
	{
		m_centralWidget->addTab( _view->getViewWidget(), _view->getViewTitle().c_str() );
		m_centralViewsCollection.insert( _view );
	}
	else
	{
		Qt::DockWidgetArea viewPossition( getQtViewPossition( _position ) );

		QDockWidget* docWidget( new QDockWidget() );

		docWidget->setWindowTitle( _view->getViewTitle().c_str() );
		docWidget->setWidget( _view->getViewWidget() );

		m_mainWindow->addDockWidget( viewPossition, docWidget );

		m_dockWidgetByViewCollection.insert( std::make_pair( _view, docWidget ) );
	}

} // WindowManager::addView


/*---------------------------------------------------------------------------*/


void
WindowManager::removeView( boost::intrusive_ptr< IView > _view )
{
	DockWidgetByViewCollectionIterator iterator = m_dockWidgetByViewCollection.find( _view );

	if ( iterator != m_dockWidgetByViewCollection.end() )
	{
		_view->getViewWidget()->setParent( NULL );
		m_mainWindow->removeDockWidget( iterator->second );

		_view->viewWasClosed();

		m_dockWidgetByViewCollection.erase( _view );
	}

	CentralViewsCollectionIterator centralViewiterator = m_centralViewsCollection.find( _view );

	if ( centralViewiterator != m_centralViewsCollection.end() )
	{
		_view->getViewWidget()->setParent( NULL );
		m_centralWidget->removeTab( m_centralWidget->indexOf( _view->getViewWidget() ) );

		_view->viewWasClosed();

		m_centralViewsCollection.erase( _view );
	}

} // WindowManager::removeView


/*---------------------------------------------------------------------------*/


void
WindowManager::addCommandToMenu( const std::string& _menuPath, const std::string& _commandName )
{
	QString menuPath( _menuPath.c_str() );
	QStringList menus( menuPath.split( Resources::MenuItemsSeparator ) );

	assert( menus.size() > 1 );

	QMenu* currentMenu = m_mainWindow->menuBar()->addMenu( menus[ 0 ] );

	for ( int i = 1; i < menus.size() - 1; ++i )
		currentMenu = currentMenu->addMenu( menus[ i ] );

	currentMenu->addAction( menus[ menus.size() - 1 ] );

} // WindowManager::addCommandToMenu


/*---------------------------------------------------------------------------*/


void
WindowManager::removeCommandFromMenu( const std::string& _menuPath )
{
} // WindowManager::removeCommandFromMenu


/*---------------------------------------------------------------------------*/


QWidget&
WindowManager::getMainWindow() const
{
	return *m_mainWindow;

} // WindowManager::getMainWindow


/*---------------------------------------------------------------------------*/


Qt::DockWidgetArea
WindowManager::getQtViewPossition( const ViewPosition::Enum _viewPossition )
{
	switch( _viewPossition )
	{
	case ViewPosition::Left:
		return Qt::LeftDockWidgetArea;
	case ViewPosition::Right:
		return Qt::RightDockWidgetArea;
	case ViewPosition::Top:
		return Qt::TopDockWidgetArea;
	case ViewPosition::Bottom:
		return Qt::BottomDockWidgetArea;
	default:
		assert( !"Unsupported view possition!" );
		return Qt::NoDockWidgetArea;
	};

} // WindowManager::getQtViewPossition


/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
