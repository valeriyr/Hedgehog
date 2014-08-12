
#ifndef __LV_COMMANDS_HPP__
#define __LV_COMMANDS_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/commands/lv_base_command.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

#define DECLARE_COMMAND( COMMAND_NAME )									\
																		\
class COMMAND_NAME														\
	:	public BaseCommand												\
{																		\
																		\
public:																	\
																		\
	COMMAND_NAME( ICommandsExecutor& _commandsExecutor );				\
																		\
	virtual ~COMMAND_NAME();											\
																		\
public:																	\
																		\
	/*virtual*/ void execute();											\
};																		\

/*---------------------------------------------------------------------------*/

DECLARE_COMMAND( NewLandscapeCommand )
DECLARE_COMMAND( OpenLandscapeCommand )
DECLARE_COMMAND( CloseLandscapeCommand )
DECLARE_COMMAND( SaveLandscapeCommand )
DECLARE_COMMAND( SaveAsLandscapeCommand )

DECLARE_COMMAND( StartMultiplayerGameCommand )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_COMMANDS_HPP__
