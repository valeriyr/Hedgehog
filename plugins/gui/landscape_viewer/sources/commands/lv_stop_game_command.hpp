
#ifndef __LV_STOP_GAME_COMMAND_HPP__
#define __LV_STOP_GAME_COMMAND_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/commands/lv_base_command.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class StopGameCommand
	:	public BaseCommand
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	StopGameCommand( const IEnvironment& _environment );

	virtual ~StopGameCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void execute();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_STOP_GAME_COMMAND_HPP__
