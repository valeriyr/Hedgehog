
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/commands/lv_stop_game_command.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_viewer/sources/game_initializer/lv_igame_initializer.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


StopGameCommand::StopGameCommand( const IEnvironment& _environment )
	:	BaseCommand( _environment )
{
} // StopGameCommand::StopGameCommand


/*---------------------------------------------------------------------------*/


StopGameCommand::~StopGameCommand()
{
} // StopGameCommand::~StopGameCommand


/*---------------------------------------------------------------------------*/


void
StopGameCommand::execute()
{
	m_environment.getGameInitializer()->stop();

} // StopGameCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
