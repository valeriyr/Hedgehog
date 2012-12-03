
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
	,	m_viewTitle( Resources::ConsoleViewTitle )
{
	m_consoleView->setReadOnly( true );

} // MainView::MainView


/*---------------------------------------------------------------------------*/


MainView::~MainView()
{
} // MainView::MainView


/*---------------------------------------------------------------------------*/


const std::string&
MainView::getViewTitle() const
{
	return m_viewTitle;

} // MainView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
MainView::getViewWidget() const
{
	return m_consoleView.get();

} // MainView::MainView


/*---------------------------------------------------------------------------*/


void
MainView::viewWasClosed()
{
	m_consoleView.reset();

} // MainView::MainView


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
