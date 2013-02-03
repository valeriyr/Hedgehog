
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
		const QString& _commandName
	,	boost::intrusive_ptr< ICommand > _command )
{
	assert( m_commandsCollection.find( _commandName ) == m_commandsCollection.end() );
	m_commandsCollection.insert( std::make_pair( _commandName, _command ) );

} // CommandsRegistry::registerCommand


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ICommand >
CommandsRegistry::unregisterCommand( const QString& _commandName )
{
	CommandsCollectionIteratorType iterator = m_commandsCollection.find( _commandName );

	assert( iterator != m_commandsCollection.end() );

	boost::intrusive_ptr< ICommand > command = iterator->second;

	m_commandsCollection.erase( iterator );

	return command;

} // CommandsRegistry::unregisterCommand


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ICommand >
CommandsRegistry::getCommand( const QString& _commandName ) const
{
	CommandsCollectionConstIteratorType iterator = m_commandsCollection.find( _commandName );

	if ( iterator != m_commandsCollection.end() )
		return iterator->second;

	return boost::intrusive_ptr< ICommand >();

} // CommandsRegistry::getCommand


/*---------------------------------------------------------------------------*/


ICommandsRegistry::CommandsIteratorTypePtr
CommandsRegistry::getCommandsList() const
{
	return
		ICommandsRegistry::CommandsIteratorTypePtr(
			new ICommandsRegistry::CommandsIteratorType( m_commandsCollection ) );

} // CommandsRegistry::getCommandsList


/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
