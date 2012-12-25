
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_save_as_landscape_command.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


SaveAsLandscapeCommand::SaveAsLandscapeCommand( const IEnvironment& _environment )
	:	BaseCommand( _environment )
{
} // SaveAsLandscapeCommand::SaveAsLandscapeCommand


/*---------------------------------------------------------------------------*/


SaveAsLandscapeCommand::~SaveAsLandscapeCommand()
{
} // SaveAsLandscapeCommand::~SaveAsLandscapeCommand


/*---------------------------------------------------------------------------*/


void
SaveAsLandscapeCommand::execute()
{
	m_environment.getLandscapeEditorController()->saveAsLandscape();

} // SaveAsLandscapeCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
