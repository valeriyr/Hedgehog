
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/main_view/con_main_view.hpp"

#include "console/sources/main_widget/con_main_widget.hpp"
#include "console/sources/environment/con_ienvironment.hpp"
#include "console/sources/resources/con_internal_resources.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "commands_manager/ih/cm_icommand.hpp"

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
	,	const std::string& _message )
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

	m_consoleView->pushMessage( QString( messageFormat ).arg( _message.c_str() ) );
}


/*---------------------------------------------------------------------------*/


void
MainView::printMessage( const std::string& _message )
{
	if ( !m_consoleView )
		return;

	m_consoleView->pushMessage( QString( Resources::MessageWithoutPrefixFormat )
		.arg( _message.c_str() ) );
}


/*---------------------------------------------------------------------------*/


void
MainView::onCommandWasEntered( const QString& _command )
{
	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
		commandsRegistry( m_environment.getCommandsRegistry() );

	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommand >
		command( commandsRegistry->getCommand( _command.toLocal8Bit().data() ) );

	if ( command )
	{
		printMessage( _command.toLocal8Bit().data() );
		command->execute();
	}
	else
	{
		printMessage(
				Tools::Core::IMessenger::MessegeLevel::Error
			,	QString( Resources::SyntaxErrorMessageFormat ).arg( _command ).toLocal8Bit().data() );
	}

} // MainView::onCommandWasEntered


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
