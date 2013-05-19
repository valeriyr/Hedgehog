
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/main_view/con_main_view.hpp"

#include "console/sources/main_widget/con_main_widget.hpp"
#include "console/sources/environment/con_ienvironment.hpp"
#include "console/sources/resources/con_internal_resources.hpp"

#include "commands_manager/ih/cm_icommand_executor.hpp"
#include "commands_manager/ih/cm_iexceptions.hpp"

#include "con_main_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/


MainView::MainView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_consoleView( new MainWidget() )
	,	m_viewTitle( Resources::ConsoleViewTitle )
{
	connect(
			m_consoleView.get()
		,	SIGNAL( commandWasEntered( const QString& ) )
		,	this
		,	SLOT( onCommandWasEntered( const QString& ) ) );

} // MainView::MainView


/*---------------------------------------------------------------------------*/


MainView::~MainView()
{
	assert( !m_consoleView );

} // MainView::~MainView


/*---------------------------------------------------------------------------*/


const QString&
MainView::getViewTitle() const
{
	return m_viewTitle;

} // MainView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
MainView::getViewWidget()
{
	return m_consoleView.get();

} // MainView::getViewWidget


/*---------------------------------------------------------------------------*/


void
MainView::viewWasClosed()
{
	disconnect(
			m_consoleView.get()
		,	SIGNAL( commandWasEntered( const QString& ) )
		,	this
		,	SLOT( onCommandWasEntered( const QString& ) ) );

	m_consoleView.reset();

} // MainView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
MainView::printMessage(
		const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
	,	const QString& _message )
{
	if ( !m_consoleView )
		return;

	const char* messageFormat = Resources::InfoMessageFormat;

	switch ( _messageLevel )
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
		break;
	}

	m_consoleView->pushMessage( QString( messageFormat ).arg( _message ) );
}


/*---------------------------------------------------------------------------*/


void
MainView::printMessage( const QString& _message )
{
	if ( !m_consoleView )
		return;

	m_consoleView->pushMessage(
		QString( Resources::MessageWithoutPrefixFormat ).arg( _message ) );
}


/*---------------------------------------------------------------------------*/


void
MainView::onCommandWasEntered( const QString& _command )
{
	try
	{
		m_environment.getCommandExecutor()->executeCommand( _command );
		printMessage( _command );
	}
	catch( const Framework::Core::CommandsManager::IException& _exception )
	{
		printMessage(
				Tools::Core::IMessenger::MessegeLevel::Error
			,	_exception.what() );
	}

} // MainView::onCommandWasEntered


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
