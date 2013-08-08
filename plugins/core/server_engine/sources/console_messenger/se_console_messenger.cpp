
#include "server_engine/sources/ph/se_ph.hpp"

#include "server_engine/sources/console_messenger/se_console_messenger.hpp"


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
		<< Tools::Core::IMessenger::MessegeLevel::toString( _messageLevel )
		<< ": "
		<< _message
		<< "/n";

} // ConsoleMessenger::printMessage


/*---------------------------------------------------------------------------*/


void
ConsoleMessenger::printMessage( const QString& _message )
{
	m_outputStream << _message << "/n";

} // ConsoleMessenger::printMessage


/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
