
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_close_landscape_command.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


CloseLandscapeCommand::CloseLandscapeCommand( const IEnvironment& _environment )
	:	BaseCommand( _environment )
{
} // CloseLandscapeCommand::CloseLandscapeCommand


/*---------------------------------------------------------------------------*/


CloseLandscapeCommand::~CloseLandscapeCommand()
{
} // CloseLandscapeCommand::~CloseLandscapeCommand


/*---------------------------------------------------------------------------*/


void
CloseLandscapeCommand::execute()
{
	m_environment.getLandscapeEditorController()->closeLandscape();

} // CloseLandscapeCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
