
#ifndef __LM_COMMANDS_QUEUE_HPP__
#define __LM_COMMANDS_QUEUE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iplayer.hpp"

#include "landscape_model/h/lm_commands.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class CommandsQueue
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< Command >
		CommandsCollection;
	typedef
		CommandsCollection::const_iterator
		CommandsCollectionIterator;

	typedef
		std::map< IPlayer::Id, CommandsCollection >
		CommandsByPlayerCollection;
	typedef
		CommandsByPlayerCollection::iterator
		CommandsByPlayerCollectionIterator;
	typedef
		CommandsByPlayerCollection::const_iterator
		CommandsByPlayerCollectionConstIterator;

	typedef
		std::map< Tools::Core::Time::Milliseconds, Command >
		CommandsByTimeCollection;
	typedef
		CommandsByTimeCollection::iterator
		CommandsByTimeCollectionIterator;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CommandsQueue();

	virtual ~CommandsQueue();

/*---------------------------------------------------------------------------*/

	void pushCommand( const TickType& _targetTick, const Command& _command );

	void pushCommand( const IPlayer::Id& _playerId, const TickType& _targetTick, const Command& _command );

	void ensureCommandsList( const IPlayer::Id& _playerId, const TickType& _targetTick );

	void fetchPlayerCommands(
			const IPlayer::Id& _playerId
		,	const TickType& _targetTick
		,	CommandsCollection& _collection );

	void fetchCommandsByTime(
			const TickType& _targetTick
		,	CommandsByTimeCollection& _collection );

/*---------------------------------------------------------------------------*/

	bool hasCommands( const TickType& _targetTick ) const;

	bool hasCommands( const IPlayer::Id& _playerId, const TickType& _targetTick ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< TickType, CommandsByPlayerCollection >
		CommandsByTickCollection;
	typedef
		CommandsByTickCollection::iterator
		CommandsByTickCollectionIterator;
	typedef
		CommandsByTickCollection::const_iterator
		CommandsByTickCollectionConstIterator;

/*---------------------------------------------------------------------------*/

	CommandsByTickCollection m_commands;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COMMANDS_QUEUE_HPP__
