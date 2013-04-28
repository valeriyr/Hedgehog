
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/commands/lv_run_game_command.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_viewer/sources/game_initializer/lv_igame_initializer.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


RunGameCommand::RunGameCommand( const IEnvironment& _environment )
	:	BaseCommand( _environment )
{
} // RunGameCommand::RunGameCommand


/*---------------------------------------------------------------------------*/


RunGameCommand::~RunGameCommand()
{
} // RunGameCommand::~RunGameCommand


/*---------------------------------------------------------------------------*/


void
RunGameCommand::execute()
{
	m_environment.getGameInitializer()->run();

} // RunGameCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
