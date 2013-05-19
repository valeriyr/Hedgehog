
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/commands/lv_base_command.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


BaseCommand::BaseCommand( ICommandExecutor& _commandExecutor )
	:	m_commandExecutor( _commandExecutor )
	,	m_isEnabled( true )
{
} // BaseCommand::BaseCommand


/*---------------------------------------------------------------------------*/


BaseCommand::~BaseCommand()
{
} // BaseCommand::~BaseCommand


/*---------------------------------------------------------------------------*/


bool
BaseCommand::isEnabled() const
{
	return m_isEnabled;

} // BaseCommand::isEnabled


/*---------------------------------------------------------------------------*/


void
BaseCommand::enable()
{
	m_isEnabled = true;

} // BaseCommand::enable


/*---------------------------------------------------------------------------*/


void
BaseCommand::disable()
{
	m_isEnabled = false;

} // BaseCommand::disable


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
