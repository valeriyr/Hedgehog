
#ifndef __CM_COMMANDS_REGISTRY_HPP__
#define __CM_COMMANDS_REGISTRY_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_icommands_registry.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/

class CommandsRegistry
	:	public Tools::Core::BaseWrapper< ICommandsRegistry >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CommandsRegistry();

	virtual ~CommandsRegistry();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void registerCommand(
			const std::string& _commandName
		,	boost::intrusive_ptr< ICommand > _command );

	/*virtual*/ boost::intrusive_ptr< ICommand >
		unregisterCommand( const std::string& _commandName );

	/*virtual*/ boost::intrusive_ptr< ICommand >
		getCommand( const std::string& _commandName );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::hash_map< std::string, boost::intrusive_ptr< ICommand > >
		CommandsCollectionType;
	typedef
		CommandsCollectionType::iterator
		CommandsCollectionIteratorType;

/*---------------------------------------------------------------------------*/

	CommandsCollectionType m_commandsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CM_COMMANDS_REGISTRY_HPP__
