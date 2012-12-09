
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/window_manager/wm_window_manager.hpp"

#include "window_manager/ih/wm_iview.hpp"

#include "wm_window_manager.moc"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/


WindowManager::WindowManager( const std::string& _applicationName )
	:	m_centralWidget( new QTabWidget() )
	,	m_mainWindow( new QMainWindow() )
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
	DockWidgetByViewCollectionIterator
			beginDockViews = m_dockWidgetByViewCollection.begin()
		,	endDockViews = m_dockWidgetByViewCollection.end();

	for ( ; beginDockViews != endDockViews; ++beginDockViews )
		tryToRemoveViewFromDock( beginDockViews->first );

	m_dockWidgetByViewCollection.clear();

	CentralViewsCollectionIterator
			beginCentralViews = m_centralViewsCollection.begin()
		,	endCentralViews = m_centralViewsCollection.end();

	for ( ; beginCentralViews != endCentralViews; ++beginCentralViews )
		tryToRemoveViewFromCenter( *beginCentralViews );

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
	if ( tryToRemoveViewFromDock( _view ) )
		m_dockWidgetByViewCollection.erase( _view );
	else if ( tryToRemoveViewFromCenter( _view ) )
		m_centralViewsCollection.erase( _view );

} // WindowManager::removeView


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


bool
WindowManager::tryToRemoveViewFromDock( boost::intrusive_ptr< IView > _view )
{
	DockWidgetByViewCollectionIterator iterator = m_dockWidgetByViewCollection.find( _view );

	if ( iterator != m_dockWidgetByViewCollection.end() )
	{
		_view->getViewWidget()->setParent( NULL );
		m_mainWindow->removeDockWidget( iterator->second );

		_view->viewWasClosed();

		return true;
	}

	return false;

} // WindowManager::tryToRemoveViewFromDock


/*---------------------------------------------------------------------------*/


bool
WindowManager::tryToRemoveViewFromCenter( boost::intrusive_ptr< IView > _view )
{
	CentralViewsCollectionIterator centralViewiterator = m_centralViewsCollection.find( _view );

	if ( centralViewiterator != m_centralViewsCollection.end() )
	{
		_view->getViewWidget()->setParent( NULL );
		m_centralWidget->removeTab( m_centralWidget->indexOf( _view->getViewWidget() ) );

		_view->viewWasClosed();

		return true;
	}

	return false;

} // WindowManager::tryToRemoveViewFromCenter


/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
