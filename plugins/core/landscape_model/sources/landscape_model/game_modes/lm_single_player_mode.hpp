
#ifndef __LM_SINGLE_PLAYER_MODE_HPP__
#define __LM_SINGLE_PLAYER_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/game_modes/lm_igame_mode.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class SinglePlayerMode
	:	public Tools::Core::BaseWrapper< IGameMode >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SinglePlayerMode( const IEnvironment& _environment );

	virtual ~SinglePlayerMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processCommand( const Command& _command );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SINGLE_PLAYER_MODE_HPP__
