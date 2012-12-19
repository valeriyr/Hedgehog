
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
	if ( !m_consoleView )
		return;

	const char* messageFormat = Resources::InfoMessageFormat;

	switch ( _messegeLevel )
	{
	case Tools::Core::IMessenger::MessegeLevel::Error:
		messageFormat = Resources::ErrorMessageFormat;
		break;
	case Tools::Core::IMessenger::MessegeLevel::Warning:
		messageFormat = Resources::WarningMessageFormat;
		break;
	case Tools::Core::IMessenger::MessegeLevel::Info:
		break;
	default:
		assert( !"Unrecognized messege level" );
	}

	m_consoleView->append( ( boost::format( messageFormat ) % _messege ).str().c_str() );
}


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
