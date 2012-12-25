
#ifndef __LE_SAVE_AS_LANDSCAPE_COMMAND_HPP__
#define __LE_SAVE_AS_LANDSCAPE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/commands/le_base_command.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class SaveAsLandscapeCommand
	:	public BaseCommand
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SaveAsLandscapeCommand( const IEnvironment& _environment );

	virtual ~SaveAsLandscapeCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void execute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_SAVE_AS_LANDSCAPE_COMMAND_HPP__
