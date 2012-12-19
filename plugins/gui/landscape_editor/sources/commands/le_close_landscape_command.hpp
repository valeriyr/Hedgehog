
#ifndef __LE_CLOSE_LANDSCAPE_COMMAND_HPP__
#define __LE_CLOSE_LANDSCAPE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_icommand.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class CloseLandscapeCommand
	:	public Tools::Core::BaseWrapper< Framework::Core::CommandsManager::ICommand >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	CloseLandscapeCommand();

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
