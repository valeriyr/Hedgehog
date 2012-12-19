
#ifndef __CON_CONSOLE_MESSENGER_HPP__
#define __CON_CONSOLE_MESSENGER_HPP__

/*---------------------------------------------------------------------------*/

#include "messenger/ms_imessenger.hpp"

#include "console/sources/main_view/con_main_view.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {


/*---------------------------------------------------------------------------*/

class ConsoleMessenger
	:	public Tools::Core::IMessenger
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ConsoleMessenger();

	virtual ~ConsoleMessenger();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessege(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messegeLevel
		,	const std::string& _messege );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::intrusive_ptr< MainView > m_mainView;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // Console
} // GUI
} // Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_CONSOLE_MESSENGER_HPP__