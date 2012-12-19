
#ifndef __CM_ICOMMANDS_REGISTRY_HPP__
#define __CM_ICOMMANDS_REGISTRY_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

struct ICommand;

/*---------------------------------------------------------------------------*/

	const unsigned int IID_COMMANDS_REGISTRY = 0;

/*---------------------------------------------------------------------------*/

struct ICommandsRegistry
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void registerCommand(
			const std::string& _commandName
		,	boost::intrusive_ptr< ICommand > _command ) = 0;

	virtual boost::intrusive_ptr< ICommand >
		unregisterCommand( const std::string& _commandName ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_ICOMMANDS_REGISTRY_HPP__
