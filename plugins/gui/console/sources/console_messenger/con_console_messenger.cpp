
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

void ConsoleMessenger::printMessage(
		const Tools::Core::IMessenger::MessegeLevel::Enum _messegeLevel
	,	const std::string& _messege )
{
	m_mainView.printMessege( _messegeLevel, _messege );

} // ConsoleMessenger::printMessage

/*---------------------------------------------------------------------------*/

} // Console
} // GUI
} // Plugins

