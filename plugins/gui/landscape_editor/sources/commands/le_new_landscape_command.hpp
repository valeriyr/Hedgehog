
#ifndef __LE_NEW_LANDSCAPE_COMMAND_HPP__
#define __LE_NEW_LANDSCAPE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/commands/le_base_command.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class NewLandscapeCommand
	:	public BaseCommand
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	NewLandscapeCommand( const IEnvironment& _environment );

	virtual ~NewLandscapeCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void execute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_NEW_LANDSCAPE_COMMAND_HPP__
