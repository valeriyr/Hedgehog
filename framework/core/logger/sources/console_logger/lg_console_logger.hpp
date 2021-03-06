
#ifndef __LG_CONSOLE_LOGGER_HPP__
#define __LG_CONSOLE_LOGGER_HPP__

/*---------------------------------------------------------------------------*/

#include "messenger/ms_imessenger.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Logger {

/*---------------------------------------------------------------------------*/

class ConsoleLogger
	:	public Tools::Core::BaseWrapper< Tools::Core::IMessenger >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ConsoleLogger();

	virtual ~ConsoleLogger();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message );

	/*virtual*/ void printMessage(
			const QString& _moduleName
		,	const MessegeLevel::Enum _messageLevel
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

	QMutex m_mutex;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Logger
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __LG_CONSOLE_LOGGER_HPP__
