
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/window_manager/wm_window_manager.hpp"

#include "window_manager/ih/wm_iview.hpp"

#include <QtGui/QTextEdit>


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/


WindowManager::WindowManager( const std::string& _applicationName )
	:	m_mainWindow( new QMainWindow() )
{
	m_mainWindow->setWindowTitle( _applicationName.c_str() );
	m_mainWindow->showMaximized();

	m_mainWindow->setCentralWidget( new QTextEdit() );

} // WindowManager::WindowManager


/*---------------------------------------------------------------------------*/


WindowManager::~WindowManager()
{
	m_mainWindow.reset();

} // WindowManager::~WindowManager


/*---------------------------------------------------------------------------*/


void
WindowManager::addView( boost::intrusive_ptr< IView > _view )
{
	Qt::DockWidgetArea viewPossition( getQtViewPossition( _view->getViewPossition() ) );

	if ( viewPossition == Qt::NoDockWidgetArea )
	{
		m_mainWindow->setCentralWidget( _view->getViewWidget() );
	}
	else
	{
		QDockWidget* docWidget( new QDockWidget() );

		docWidget->setWindowTitle( _view->getViewTitle().c_str() );
		docWidget->setWidget( _view->getViewWidget() );

		m_mainWindow->addDockWidget( viewPossition, docWidget );
	}

} // WindowManager::addView


/*---------------------------------------------------------------------------*/


void
WindowManager::removeView( boost::intrusive_ptr< IView > _view )
{
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
	};

	return Qt::NoDockWidgetArea;

} // WindowManager::getQtViewPossition


/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
