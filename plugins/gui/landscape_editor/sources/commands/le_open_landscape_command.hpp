
#ifndef __LE_OPEN_LANDSCAPE_COMMAND_HPP__
#define __LE_OPEN_LANDSCAPE_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "commands_manager/ih/cm_icommand.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class OpenLandscapeCommand
	:	public Tools::Core::BaseWrapper< Framework::Core::CommandsManager::ICommand >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	OpenLandscapeCommand();

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
