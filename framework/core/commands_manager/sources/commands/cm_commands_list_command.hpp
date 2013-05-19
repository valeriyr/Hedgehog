
#ifndef __CM_COMMANDS_LIST_COMMAND_HPP__
#define __CM_COMMANDS_LIST_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_icommand.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools
{
	namespace Core
	{
		struct IMessenger;
	}
}

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

struct ICommandsRegistry;

/*---------------------------------------------------------------------------*/

class CommandsListCommand
	:	public Tools::Core::BaseWrapper< ICommand >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CommandsListCommand(
			const ICommandsRegistry& _commandsRegistry
		,	Tools::Core::IMessenger& _messenger );

	virtual ~CommandsListCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void execute();

	/*virtual*/ bool isEnabled() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ICommandsRegistry& m_commandsRegistry;

	Tools::Core::IMessenger& m_messenger;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_COMMANDS_LIST_COMMAND_HPP__
