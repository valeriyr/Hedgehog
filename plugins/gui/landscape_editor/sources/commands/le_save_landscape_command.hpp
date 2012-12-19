
#ifndef __LE_SAVE_LANDSCAPE_COMMAND_HPP__
#define __LE_SAVE_LANDSCAPE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_icommand.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class SaveLandscapeCommand
	:	public Tools::Core::BaseWrapper< Framework::Core::CommandsManager::ICommand >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SaveLandscapeCommand();

	virtual ~SaveLandscapeCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void execute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_SAVE_LANDSCAPE_COMMAND_HPP__
