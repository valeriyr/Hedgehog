
#include "commands_manager/sources/ph/cm_ph.hpp"

#include "commands_manager/sources/commands/cm_commands_list_command.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "messenger/ms_imessenger.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/


CommandsListCommand::CommandsListCommand(
		const ICommandsRegistry& _commandsRegistry
	,	Tools::Core::IMessenger& _messenger
	)
	:	m_commandsRegistry( _commandsRegistry )
	,	m_messenger( _messenger )
{
} // CommandsListCommand::CommandsListCommand


/*---------------------------------------------------------------------------*/


CommandsListCommand::~CommandsListCommand()
{
} // CommandsListCommand::~CommandsListCommand


/*---------------------------------------------------------------------------*/


void
CommandsListCommand::execute()
{
	ICommandsRegistry::CommandsIteratorTypePtr commandsIterator
		= m_commandsRegistry.getCommandsList();

	while ( commandsIterator->isValid() )
	{
		m_messenger.printMessage( commandsIterator->current() );
		commandsIterator->next();
	}

} // CommandsListCommand::execute


/*---------------------------------------------------------------------------*/


bool
CommandsListCommand::isEnabled() const
{
	return true;

} // CommandsListCommand::isEnabled


/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
