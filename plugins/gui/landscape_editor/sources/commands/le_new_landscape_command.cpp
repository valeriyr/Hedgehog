
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_new_landscape_command.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


NewLandscapeCommand::NewLandscapeCommand( const IEnvironment& _environment )
	:	BaseCommand( _environment )
{
} // NewLandscapeCommand::NewLandscapeCommand


/*---------------------------------------------------------------------------*/


NewLandscapeCommand::~NewLandscapeCommand()
{
} // NewLandscapeCommand::~NewLandscapeCommand


/*---------------------------------------------------------------------------*/


void
NewLandscapeCommand::execute()
{
	int i = 0;

} // NewLandscapeCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
