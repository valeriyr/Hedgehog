
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_single_player_mode.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/sources/model_locker/lm_model_locker.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SinglePlayerMode::SinglePlayerMode( const IEnvironment& _environment )
	:	m_environment( _environment )
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
	m_environment.lockModel()->getLandscapeModel()->processCommand( _command );

} // SinglePlayerMode::processCommand


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
