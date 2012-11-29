
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/main_view/con_main_view.hpp"

#include "console/sources/resources/con_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/


MainView::MainView()
	:	m_consoleView( new QTextEdit() )
{
	m_consoleView->setText( ">" );

} // MainView::MainView


/*---------------------------------------------------------------------------*/


MainView::~MainView()
{
} // MainView::MainView


/*---------------------------------------------------------------------------*/


const Framework::GUI::WindowManager::ViewPosition::Enum
MainView::getViewPossition() const
{
	return Framework::GUI::WindowManager::ViewPosition::Bottom;

} // MainView::MainView


/*---------------------------------------------------------------------------*/


const std::string&
MainView::getViewTitle() const
{
	return Resources::ConsoleViewTitle;

} // MainView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
MainView::getViewWidget() const
{
	return m_consoleView;

} // MainView::MainView


/*---------------------------------------------------------------------------*/


void
MainView::viewWasClosed()
{
} // MainView::MainView


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
