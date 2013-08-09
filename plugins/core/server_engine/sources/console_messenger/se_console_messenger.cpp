
#include "server_engine/sources/ph/se_ph.hpp"

#include "server_engine/sources/console_messenger/se_console_messenger.hpp"

#include "server_engine/sources/internal_resources/se_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

/*---------------------------------------------------------------------------*/


ConsoleMessenger::ConsoleMessenger()
	:	m_outputStream( stdout )
{
} // ConsoleMessenger::ConsoleMessenger


/*---------------------------------------------------------------------------*/


ConsoleMessenger::~ConsoleMessenger()
{
} // ConsoleMessenger::~ConsoleMessenger


/*---------------------------------------------------------------------------*/


void
ConsoleMessenger::printMessage(
		const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
	,	const QString& _message )
{
	m_outputStream
		<< QString( Resources::Messanges::MessageWithLevelFormat )
				.arg( Tools::Core::IMessenger::MessegeLevel::toString( _messageLevel ) )
				.arg( _message );
	flush();

} // ConsoleMessenger::printMessage


/*---------------------------------------------------------------------------*/


void
ConsoleMessenger::printMessage( const QString& _message )
{
	m_outputStream << QString( Resources::Messanges::SimpleMessageFormat ).arg( _message );
	flush();

} // ConsoleMessenger::printMessage


/*---------------------------------------------------------------------------*/


void
ConsoleMessenger::flush()
{
	m_outputStream.flush();

} // ConsoleMessenger::flush


/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
