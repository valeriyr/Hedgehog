
#ifndef __LM_SINGLE_PLAYER_MODE_HPP__
#define __LM_SINGLE_PLAYER_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/game_modes/lm_igame_mode.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModel;

/*---------------------------------------------------------------------------*/

class SinglePlayerMode
	:	public Tools::Core::BaseWrapper< IGameMode >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SinglePlayerMode( ILandscapeModel& _landscapeModel );

	virtual ~SinglePlayerMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processCommand( const Command& _command );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	ILandscapeModel& m_landscapeModel;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SINGLE_PLAYER_MODE_HPP__
