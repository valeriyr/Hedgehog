
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_open_landscape_command.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


OpenLandscapeCommand::OpenLandscapeCommand( const IEnvironment& _environment )
	:	BaseCommand( _environment )
{
} // OpenLandscapeCommand::OpenLandscapeCommand


/*---------------------------------------------------------------------------*/


OpenLandscapeCommand::~OpenLandscapeCommand()
{
} // OpenLandscapeCommand::~OpenLandscapeCommand


/*---------------------------------------------------------------------------*/


void
OpenLandscapeCommand::execute()
{
	m_environment.getLandscapeEditorController()->openLandscape();

} // OpenLandscapeCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
