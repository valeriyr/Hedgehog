
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_save_landscape_command.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


SaveLandscapeCommand::SaveLandscapeCommand( const IEnvironment& _environment )
	:	BaseCommand( _environment )
{
} // SaveLandscapeCommand::SaveLandscapeCommand


/*---------------------------------------------------------------------------*/


SaveLandscapeCommand::~SaveLandscapeCommand()
{
} // SaveLandscapeCommand::~SaveLandscapeCommand


/*---------------------------------------------------------------------------*/


void
SaveLandscapeCommand::execute()
{
	int i = 0;

} // SaveLandscapeCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
