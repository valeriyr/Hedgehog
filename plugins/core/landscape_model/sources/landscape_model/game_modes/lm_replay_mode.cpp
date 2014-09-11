
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_replay_mode.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ReplayMode::ReplayMode( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_commandsQueue()
{
} // ReplayMode::ReplayMode


/*---------------------------------------------------------------------------*/


ReplayMode::~ReplayMode()
{
} // ReplayMode::~ReplayMode


/*---------------------------------------------------------------------------*/


void
ReplayMode::processCommand( const Command& _command )
{
} // ReplayMode::processCommand


/*---------------------------------------------------------------------------*/


bool
ReplayMode::prepareToTick( const TickType& _tick )
{
	return true;

} // ReplayMode::prepareToTick


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
