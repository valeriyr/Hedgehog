
#include "commands_manager/sources/ph/cm_ph.hpp"

#include "commands_manager/sources/command_executor/cm_command_executor.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "commands_manager/ih/cm_icommand.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/


CommandExecutor::CommandExecutor( ICommandsRegistry& _commandsRegistry )
	:	m_commandsRegistry( _commandsRegistry )
{
} // CommandExecutor::CommandExecutor


/*---------------------------------------------------------------------------*/


CommandExecutor::~CommandExecutor()
{
} // CommandExecutor::~CommandExecutor


/*---------------------------------------------------------------------------*/


void
CommandExecutor::executeCommand( const QString& _command ) const
{
	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommand >
		command( m_commandsRegistry.getCommand( _command ) );

	if ( !command )
		throw std::exception();

	command->execute();

} // CommandExecutor::executeCommand


/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
