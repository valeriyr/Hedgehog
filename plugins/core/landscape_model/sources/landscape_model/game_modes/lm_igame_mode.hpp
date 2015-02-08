
#ifndef __LM_IGAME_MODE_HPP__
#define __LM_IGAME_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/h/lm_commands.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class CommandsQueue;

/*---------------------------------------------------------------------------*/

struct IGameMode
	: public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	struct Type
	{
		enum Enum : qint32
		{
				Undefined = 0

			,	SinglePlayer
			,	Multiplayer
			,	Replay
		};
	};

/*---------------------------------------------------------------------------*/

	virtual void processCommand( Command& _command ) = 0;

	virtual bool prepareToTick( const TickType& _tick ) = 0;

/*---------------------------------------------------------------------------*/

	virtual const CommandsQueue& getCommands() const = 0;

/*---------------------------------------------------------------------------*/

	virtual Type::Enum getType() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IGAME_MODE_HPP__
