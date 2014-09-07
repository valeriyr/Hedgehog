
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_commands_queue.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


CommandsQueue::CommandsQueue()
	:	m_commands()
{
} // CommandsQueue::CommandsQueue


/*---------------------------------------------------------------------------*/


CommandsQueue::~CommandsQueue()
{
} // CommandsQueue::~CommandsQueue


/*---------------------------------------------------------------------------*/


void
CommandsQueue::pushCommand( const TickType& _targetTick, const Command& _command )
{
	pushCommand( _command.m_playerId, _targetTick, _command );

} // CommandsQueue::pushCommand


/*---------------------------------------------------------------------------*/


void
CommandsQueue::pushCommand( const IPlayer::Id& _playerId, const TickType& _targetTick, const Command& _command )
{
	assert( _playerId != IPlayer::ms_wrondId );
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
CommandsQueue::fetchPlayerCommands(
		const IPlayer::Id& _playerId
	,	const TickType& _targetTick
	,	CommandsCollection& _collection )
{
	CommandsByTickCollectionIterator commandsByTickIterator = m_commands.find( _targetTick );

	if ( commandsByTickIterator == m_commands.end() )
		commandsByTickIterator = m_commands.insert( std::make_pair( _targetTick, CommandsByPlayerCollection() ) ).first;

	CommandsByPlayerCollectionIterator commandsByPlayerIterator = commandsByTickIterator->second.find( _playerId );

	if ( commandsByPlayerIterator == commandsByTickIterator->second.end() )
		commandsByPlayerIterator = commandsByTickIterator->second.insert( std::make_pair( _playerId, CommandsCollection() ) ).first;

	_collection = commandsByPlayerIterator->second;

} // CommandsQueue::fetchPlayerCommands


/*---------------------------------------------------------------------------*/


void
CommandsQueue::fetchCommandsByTime(
		const TickType& _targetTick
	,	CommandsByTimeCollection& _collection )
{
	_collection.clear();

	CommandsByTickCollectionIterator commandsByTickIterator = m_commands.find( _targetTick );

	if ( commandsByTickIterator == m_commands.end() )
		return;

	CommandsByPlayerCollectionIterator
			begin = commandsByTickIterator->second.begin()
		,	end = commandsByTickIterator->second.end();

	for ( ; begin != end; ++begin )
	{
		CommandsCollectionIterator
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
	return m_commands.find( _targetTick ) != m_commands.end();

} // CommandsQueue::hasCommands


/*---------------------------------------------------------------------------*/


bool
CommandsQueue::hasCommands( const IPlayer::Id& _playerId, const TickType& _targetTick ) const
{
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
