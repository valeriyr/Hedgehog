
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

struct IGameMode
	: public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void processCommand( const Command& _command ) = 0;

	virtual bool prepareToTick( const TickType& _tick ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IGAME_MODE_HPP__
