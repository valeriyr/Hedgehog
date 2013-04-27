
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_new_landscape_command.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/landscape_editor/le_ilandscape_editor_internal.hpp"


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
	m_environment.getGUILandscapeEditor()->newLandscape();

} // NewLandscapeCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
