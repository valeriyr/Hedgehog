
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/console_messenger/con_console_messenger.hpp"

#include "console/sources/main_view/con_main_view.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/


ConsoleMessenger::ConsoleMessenger( MainView& _mainView )
	:	m_mainView( _mainView )
{
} // ConsoleMessenger::ConsoleMessenger


/*---------------------------------------------------------------------------*/


ConsoleMessenger::~ConsoleMessenger()
{
} // ConsoleMessenger::~ConsoleMessenger


/*---------------------------------------------------------------------------*/


void
ConsoleMessenger::printMessage(
		const Tools::Core::IMessenger::MessegeLevel::Enum _messegeLevel
	,	const QString& _messege )
{
	m_mainView.printMessage( _messegeLevel, _messege );

} // ConsoleMessenger::printMessage


/*---------------------------------------------------------------------------*/


void
ConsoleMessenger::printMessage(
		const QString& _moduleName
	,	const Tools::Core::IMessenger::MessegeLevel::Enum _messegeLevel
	,	const QString& _messege )
{
	m_mainView.printMessage( _moduleName, _messegeLevel, _messege );

} // ConsoleMessenger::printMessage


/*---------------------------------------------------------------------------*/


void
ConsoleMessenger::printMessage( const QString& _messege )
{
	m_mainView.printMessage( _messege );

} // ConsoleMessenger::printMessage


/*---------------------------------------------------------------------------*/

} // Console
} // GUI
} // Plugins

/*---------------------------------------------------------------------------*/
