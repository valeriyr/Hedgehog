
#ifndef __CON_CONSOLE_MESSENGER_HPP__
#define __CON_CONSOLE_MESSENGER_HPP__

/*---------------------------------------------------------------------------*/

#include "messenger/ms_imessenger.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/

	class MainView;

/*---------------------------------------------------------------------------*/

class ConsoleMessenger
	:	public Tools::Core::BaseWrapper< Tools::Core::IMessenger >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ConsoleMessenger( MainView& _mainView );

	virtual ~ConsoleMessenger();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message );

	/*virtual*/ void printMessage( const QString& _message );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	MainView& m_mainView;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // Console
} // GUI
} // Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_CONSOLE_MESSENGER_HPP__
