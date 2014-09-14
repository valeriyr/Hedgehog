
#ifndef __LM_REPLAY_MODE_HPP__
#define __LM_REPLAY_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/game_modes/lm_igame_mode.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_commands_queue.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class ReplayMode
	:	public Tools::Core::BaseWrapper< IGameMode >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ReplayMode( const IEnvironment& _environment );

	virtual ~ReplayMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processCommand( Command& _command );

	/*virtual*/ bool prepareToTick( const TickType& _tick );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const CommandsQueue& getCommands() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ IGameMode::Type::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	CommandsQueue m_commandsQueue;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_REPLAY_MODE_HPP__
