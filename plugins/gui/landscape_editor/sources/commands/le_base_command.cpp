
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/commands/le_base_command.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

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

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
