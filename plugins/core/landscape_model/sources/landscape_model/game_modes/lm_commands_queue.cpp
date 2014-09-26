
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_commands_queue.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


CommandsQueue::CommandsQueue()
	:	m_mutex()
	,	m_commands()
{
} // CommandsQueue::CommandsQueue


/*---------------------------------------------------------------------------*/


CommandsQueue::~CommandsQueue()
{
} // CommandsQueue::~CommandsQueue


/*---------------------------------------------------------------------------*/


void
CommandsQueue::pushCommand( const Command& _command )
{
	pushCommand( _command.m_playerId, _command.m_targetTick, _command );

} // CommandsQueue::pushCommand


/*---------------------------------------------------------------------------*/


void
CommandsQueue::pushCommand( const Tools::Core::Generators::IGenerator::IdType& _playerId, const TickType& _targetTick, const Command& _command )
{
	QMutexLocker locker( &m_mutex );

	assert( _playerId != Tools::Core::Generators::IGenerator::ms_wrongId );
	assert( _playerId == _command.m_playerId );

	CommandsByTickCollectionIterator iteratorByTick = m_commands.find( _targetTick );

	if ( iteratorByTick == m_commands.end() )
		iteratorByTick = m_commands.insert( std::make_pair( _targetTick, CommandsByPlayerCollection() ) ).first;

	CommandsByPlayerCollectionIterator iteratorByPlayer = iteratorByTick->second.find( _playerId );

	if ( iteratorByPlayer == iteratorByTick->second.end() )
		iteratorByPlayer = iteratorByTick->second.insert( std::make_pair( _playerId, CommandsCollection() ) ).first;

	iteratorByPlayer->second.push_back( _command );

} // CommandsQueue::pushCommand


/*---------------------------------------------------------------------------*/


void
CommandsQueue::ensureCommandsList( const Tools::Core::Generators::IGenerator::IdType& _playerId, const TickType& _targetTick )
{
	QMutexLocker locker( &m_mutex );

	CommandsByTickCollectionIterator iteratorByTick = m_commands.find( _targetTick );

	if ( iteratorByTick == m_commands.end() )
		iteratorByTick = m_commands.insert( std::make_pair( _targetTick, CommandsByPlayerCollection() ) ).first;

	CommandsByPlayerCollectionIterator iteratorByPlayer = iteratorByTick->second.find( _playerId );

	if ( iteratorByPlayer == iteratorByTick->second.end() )
		iteratorByPlayer = iteratorByTick->second.insert( std::make_pair( _playerId, CommandsCollection() ) ).first;

} // CommandsQueue::ensureCommandsList


/*---------------------------------------------------------------------------*/


void
CommandsQueue::fetchCommands( CommandsByTickCollection& _collection ) const
{
	QMutexLocker locker( &const_cast< CommandsQueue* >( this )->m_mutex );

	_collection = m_commands;

} // CommandsQueue::fetchCommands


/*---------------------------------------------------------------------------*/


void
CommandsQueue::fetchPlayerCommands(
		const Tools::Core::Generators::IGenerator::IdType& _playerId
	,	const TickType& _targetTick
	,	CommandsCollection& _collection ) const
{
	QMutexLocker locker( &const_cast< CommandsQueue* >( this )->m_mutex );

	_collection.clear();

	CommandsByTickCollectionConstIterator commandsByTickIterator = m_commands.find( _targetTick );

	if ( commandsByTickIterator == m_commands.end() )
		return;

	CommandsByPlayerCollectionConstIterator commandsByPlayerIterator = commandsByTickIterator->second.find( _playerId );

	if ( commandsByPlayerIterator == commandsByTickIterator->second.end() )
		return;

	_collection = commandsByPlayerIterator->second;

} // CommandsQueue::fetchPlayerCommands


/*---------------------------------------------------------------------------*/


void
CommandsQueue::fetchCommandsByTime(
		const TickType& _targetTick
	,	CommandsByTimeCollection& _collection ) const
{
	QMutexLocker locker( &const_cast< CommandsQueue* >( this )->m_mutex );

	_collection.clear();

	CommandsByTickCollectionConstIterator commandsByTickIterator = m_commands.find( _targetTick );

	if ( commandsByTickIterator == m_commands.end() )
		return;

	CommandsByPlayerCollectionConstIterator
			begin = commandsByTickIterator->second.begin()
		,	end = commandsByTickIterator->second.end();

	for ( ; begin != end; ++begin )
	{
		CommandsCollectionConstIterator
				commandsBegin = begin->second.begin()
			,	commandsEnd = begin->second.end();

		for ( ; commandsBegin != commandsEnd; ++commandsBegin )
		{
			_collection.insert( std::make_pair( commandsBegin->m_timeStamp, *commandsBegin ) );
		}
	}

} // CommandsQueue::fetchCommandsByTime


/*---------------------------------------------------------------------------*/


bool
CommandsQueue::hasCommands( const TickType& _targetTick ) const
{
	QMutexLocker locker( &const_cast< CommandsQueue* >( this )->m_mutex );

	return m_commands.find( _targetTick ) != m_commands.end();

} // CommandsQueue::hasCommands


/*---------------------------------------------------------------------------*/


bool
CommandsQueue::hasCommandsFrom( const TickType& _targetTick ) const
{
	QMutexLocker locker( &const_cast< CommandsQueue* >( this )->m_mutex );

	if ( m_commands.empty() )
		return false;

	CommandsByTickCollectionConstIterator iterator = m_commands.end();
	--iterator;

	return iterator->first > _targetTick;

} // CommandsQueue::hasCommandsFrom


/*---------------------------------------------------------------------------*/


bool
CommandsQueue::hasCommands( const Tools::Core::Generators::IGenerator::IdType& _playerId, const TickType& _targetTick ) const
{
	QMutexLocker locker( &const_cast< CommandsQueue* >( this )->m_mutex );

	CommandsByTickCollectionConstIterator byTickIterator = m_commands.find( _targetTick );

	if ( byTickIterator == m_commands.end() )
		return false;

	CommandsByPlayerCollectionConstIterator byPlayerIterator = byTickIterator->second.find( _playerId );

	if ( byPlayerIterator == byTickIterator->second.end() )
		return false;

	return true;

} // CommandsQueue::hasCommands


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
