
#ifndef __LE_OPEN_LANDSCAPE_COMMAND_HPP__
#define __LE_OPEN_LANDSCAPE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/commands/le_base_command.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class OpenLandscapeCommand
	:	public BaseCommand
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	OpenLandscapeCommand( const IEnvironment& _environment );

	virtual ~OpenLandscapeCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void execute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_OPEN_LANDSCAPE_COMMAND_HPP__
