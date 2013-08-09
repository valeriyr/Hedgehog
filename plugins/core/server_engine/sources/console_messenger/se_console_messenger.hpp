
#ifndef __SE_CONSOLE_MESSENGER_HPP__
#define __SE_CONSOLE_MESSENGER_HPP__

/*---------------------------------------------------------------------------*/

#include "messenger/ms_imessenger.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

/*---------------------------------------------------------------------------*/

class ConsoleMessenger
	:	public Tools::Core::BaseWrapper< Tools::Core::IMessenger >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ConsoleMessenger();

	virtual ~ConsoleMessenger();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message );

	/*virtual*/ void printMessage( const QString& _message );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void flush();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QTextStream m_outputStream;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __SE_CONSOLE_MESSENGER_HPP__
