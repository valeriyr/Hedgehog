
#include "commands_manager/sources/ph/cm_ph.hpp"

#include "commands_manager/sources/commands_registry/cm_commands_registry.hpp"

#include "commands_manager/ih/cm_icommand.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/


CommandsRegistry::CommandsRegistry()
	:	m_commandsCollection()
{
} // CommandsRegistry::CommandsRegistry


/*---------------------------------------------------------------------------*/


CommandsRegistry::~CommandsRegistry()
{
	assert( m_commandsCollection.empty() );

} // CommandsRegistry::~CommandsRegistry


/*---------------------------------------------------------------------------*/


void
CommandsRegistry::registerCommand(
		const std::string& _commandName
	,	boost::intrusive_ptr< ICommand > _command )
{
	assert( m_commandsCollection.find( _commandName ) == m_commandsCollection.end() );
	m_commandsCollection.insert( std::make_pair( _commandName, _command ) );

} // CommandsRegistry::registerCommand


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ICommand >
CommandsRegistry::unregisterCommand( const std::string& _commandName )
{
	CommandsCollectionIteratorType iterator = m_commandsCollection.find( _commandName );

	assert( iterator != m_commandsCollection.end() );

	boost::intrusive_ptr< ICommand > command = iterator->second;

	m_commandsCollection.erase( iterator );

	return command;

} // CommandsRegistry::unregisterCommand


/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
