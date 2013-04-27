
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_save_landscape_command.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/landscape_editor/le_ilandscape_editor_internal.hpp"


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
	m_environment.getGUILandscapeEditor()->saveLandscape();

} // SaveLandscapeCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
