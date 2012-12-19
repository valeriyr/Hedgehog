
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
} // MainView::~MainView


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

} // MainView::getViewWidget


/*---------------------------------------------------------------------------*/


void
MainView::viewWasClosed()
{
	m_consoleView.reset();

} // MainView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
MainView::printMessege(
		const Tools::Core::IMessenger::MessegeLevel::Enum _messegeLevel
	,	const std::string& _messege )
{
	switch (_messegeLevel)
	{
	case Tools::Core::IMessenger::MessegeLevel::Enum::Error:
		m_consoleView->setHtml("> <font color=red><b>[ ERROR ]</b> .</font>");
	case Tools::Core::IMessenger::MessegeLevel::Enum::Warning:
		m_consoleView->setHtml("> <font color=blue><b>[ WARNING ]</b> .</font>");
	case Tools::Core::IMessenger::MessegeLevel::Enum::Info:
		m_consoleView->setHtml("> <b>[ INFO ]</b> .");
	default:
		throw("Unrecognized messege level");
	}
}


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
