
#ifndef __LV_RUN_GAME_COMMAND_HPP__
#define __LV_RUN_GAME_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/commands/lv_base_command.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class RunGameCommand
	:	public BaseCommand
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	RunGameCommand( const IEnvironment& _environment );

	virtual ~RunGameCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void execute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_RUN_GAME_COMMAND_HPP__
