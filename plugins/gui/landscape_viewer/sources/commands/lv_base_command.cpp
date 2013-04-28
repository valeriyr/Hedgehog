
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/commands/lv_base_command.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


BaseCommand::BaseCommand( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // BaseCommand::BaseCommand


/*---------------------------------------------------------------------------*/


BaseCommand::~BaseCommand()
{
} // BaseCommand::~BaseCommand


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
