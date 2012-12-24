
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_open_landscape_command.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_manager.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"


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
	QString fileName( m_environment.getDialogsManager()->getOpenFileName( "*.hmap" ) );

	m_environment.getLandscapeManager()->initCurrentLandscape( fileName );

} // OpenLandscapeCommand::execute


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
