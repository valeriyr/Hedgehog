
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
		CommandsCollection::iterator
		CommandsCollectionIterator;
	typedef
		CommandsCollection::const_iterator
		CommandsCollectionConstIterator;

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

public:

/*---------------------------------------------------------------------------*/

	CommandsQueue();

	virtual ~CommandsQueue();

/*---------------------------------------------------------------------------*/

	void pushCommand( const Command& _command );

	void pushCommand( const IPlayer::Id& _playerId, const TickType& _targetTick, const Command& _command );

	void ensureCommandsList( const IPlayer::Id& _playerId, const TickType& _targetTick );

	void fetchCommands( CommandsByTickCollection& _collection ) const;

	void fetchPlayerCommands(
			const IPlayer::Id& _playerId
		,	const TickType& _targetTick
		,	CommandsCollection& _collection ) const;

	void fetchCommandsByTime(
			const TickType& _targetTick
		,	CommandsByTimeCollection& _collection ) const;

/*---------------------------------------------------------------------------*/

	bool hasCommands( const TickType& _targetTick ) const;

	bool hasCommands( const IPlayer::Id& _playerId, const TickType& _targetTick ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QMutex m_mutex;

	CommandsByTickCollection m_commands;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COMMANDS_QUEUE_HPP__
