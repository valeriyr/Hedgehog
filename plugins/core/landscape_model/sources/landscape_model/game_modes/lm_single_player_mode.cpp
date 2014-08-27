
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_single_player_mode.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SinglePlayerMode::SinglePlayerMode( ILandscapeModel& _landscapeModel)
	:	m_landscapeModel( _landscapeModel )
{
} // SinglePlayerMode::SinglePlayerMode


/*---------------------------------------------------------------------------*/


SinglePlayerMode::~SinglePlayerMode()
{
} // SinglePlayerMode::~SinglePlayerMode


/*---------------------------------------------------------------------------*/


void
SinglePlayerMode::processCommand( const Command& _command )
{
	m_landscapeModel.processCommand( _command );

} // SinglePlayerMode::processCommand


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
