
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/commands/lv_commands.hpp"

#include "landscape_viewer/sources/commands_executor/lv_icommands_executor.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


#define DEFINE_COMMAND( COMMAND_NAME, EXECUTOR )								\
																				\
COMMAND_NAME::COMMAND_NAME( ICommandsExecutor& _commandsExecutor )				\
	:	BaseCommand( _commandsExecutor )										\
{																				\
}																				\
																				\
COMMAND_NAME::~COMMAND_NAME()													\
{																				\
}																				\
																				\
void																			\
COMMAND_NAME::execute()															\
{																				\
	m_commandsExecutor.EXECUTOR();												\
}																				\

/*---------------------------------------------------------------------------*/

DEFINE_COMMAND( NewLandscapeCommand, newLandscape )
DEFINE_COMMAND( OpenLandscapeCommand, openLandscape )
DEFINE_COMMAND( CloseLandscapeCommand, closeLandscape )
DEFINE_COMMAND( SaveLandscapeCommand, saveLandscape )
DEFINE_COMMAND( SaveAsLandscapeCommand, saveAsLandscape )

DEFINE_COMMAND( StartGameCommand, startGame )

DEFINE_COMMAND( StartReplayCommand, startReplay )
DEFINE_COMMAND( SaveReplayCommand, saveReplay )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
