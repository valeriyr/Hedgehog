
#ifndef __CM_COMMAND_EXECUTOR_HPP__
#define __CM_COMMAND_EXECUTOR_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_icommand_executor.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

struct ICommandsRegistry;

/*---------------------------------------------------------------------------*/

class CommandExecutor
	:	public Tools::Core::BaseWrapper< ICommandExecutor >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CommandExecutor( ICommandsRegistry& _commandsRegistry );

	virtual ~CommandExecutor();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void executeCommand( const QString& _command ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	ICommandsRegistry& m_commandsRegistry;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_COMMAND_EXECUTOR_HPP__
