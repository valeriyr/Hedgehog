
#ifndef __LE_CLOSE_LANDSCAPE_COMMAND_HPP__
#define __LE_CLOSE_LANDSCAPE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/commands/le_base_command.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class CloseLandscapeCommand
	:	public BaseCommand
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CloseLandscapeCommand( const IEnvironment& _environment );

	virtual ~CloseLandscapeCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void execute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_CLOSE_LANDSCAPE_COMMAND_HPP__
