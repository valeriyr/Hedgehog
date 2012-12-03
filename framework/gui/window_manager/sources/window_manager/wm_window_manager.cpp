
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/window_manager/wm_window_manager.hpp"

#include "window_manager/ih/wm_iview.hpp"

#include "wm_window_manager.moc"

#include <QtGui/QTextEdit>


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/


WindowManager::WindowManager( const std::string& _applicationName )
	:	m_mainWindow( new QMainWindow() )
	,	m_dockWidgetByViewCollection()
{
	m_mainWindow->setWindowTitle( _applicationName.c_str() );
	m_mainWindow->showMaximized();

	m_mainWindow->setCentralWidget( new QTextEdit() );

} // WindowManager::WindowManager


/*---------------------------------------------------------------------------*/


WindowManager::~WindowManager()
{
	DockWidgetByViewCollectionIterator
			begin = m_dockWidgetByViewCollection.begin()
		,	end = m_dockWidgetByViewCollection.end();

	for ( ; begin != end; ++begin )
	{
		removeView( begin->first );
		begin->first->viewWasClosed();
	}

	m_dockWidgetByViewCollection.clear();

	m_mainWindow.reset();

} // WindowManager::~WindowManager


/*---------------------------------------------------------------------------*/


void
WindowManager::addView(
		IView::Ptr _view
	,	const ViewPosition::Enum _position )
{
	assert( m_dockWidgetByViewCollection.find( _view ) == m_dockWidgetByViewCollection.end() );

	Qt::DockWidgetArea viewPossition( getQtViewPossition( _position ) );

	QDockWidget* docWidget( new QDockWidget() );

	docWidget->setWindowTitle( _view->getViewTitle().c_str() );
	docWidget->setWidget( _view->getViewWidget() );

	m_mainWindow->addDockWidget( viewPossition, docWidget );

	m_dockWidgetByViewCollection.insert( std::make_pair( _view, docWidget ) );

} // WindowManager::addView


/*---------------------------------------------------------------------------*/


void
WindowManager::removeView( IView::Ptr _view )
{
	DockWidgetByViewCollectionIterator iterator = m_dockWidgetByViewCollection.find( _view );

	if ( iterator == m_dockWidgetByViewCollection.end() )
		return;

	_view->getViewWidget()->setParent( NULL );
	m_mainWindow->removeDockWidget( iterator->second );

	m_dockWidgetByViewCollection.erase( _view );

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

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
