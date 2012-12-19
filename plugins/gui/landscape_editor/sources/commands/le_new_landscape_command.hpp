
#ifndef __LE_NEW_LANDSCAPE_COMMAND_HPP__
#define __LE_NEW_LANDSCAPE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_icommand.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class NewLandscapeCommand
	:	public Tools::Core::BaseWrapper< Framework::Core::CommandsManager::ICommand >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	NewLandscapeCommand();

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
