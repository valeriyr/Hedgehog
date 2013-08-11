
#include "logger/sources/ph/lg_ph.hpp"

#include "logger/sources/console_logger/lg_console_logger.hpp"

#include "logger/sources/internal_resources/lg_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Logger {

/*---------------------------------------------------------------------------*/


ConsoleLogger::ConsoleLogger()
	:	m_outputStream( stdout )
{
} // ConsoleLogger::ConsoleLogger


/*---------------------------------------------------------------------------*/


ConsoleLogger::~ConsoleLogger()
{
} // ConsoleLogger::~ConsoleLogger


/*---------------------------------------------------------------------------*/


void
ConsoleLogger::printMessage(
		const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
	,	const QString& _message )
{
	m_outputStream
		<< QString( Resources::Messanges::MessageWithLevelFormat )
				.arg( Tools::Core::IMessenger::MessegeLevel::toString( _messageLevel ) )
				.arg( _message );
	flush();

} // ConsoleLogger::printMessage


/*---------------------------------------------------------------------------*/


void
ConsoleLogger::printMessage( const QString& _message )
{
	m_outputStream << QString( Resources::Messanges::SimpleMessageFormat ).arg( _message );
	flush();

} // ConsoleLogger::printMessage


/*---------------------------------------------------------------------------*/


void
ConsoleLogger::flush()
{
	m_outputStream.flush();

} // ConsoleLogger::flush


/*---------------------------------------------------------------------------*/

} // namespace Logger
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
