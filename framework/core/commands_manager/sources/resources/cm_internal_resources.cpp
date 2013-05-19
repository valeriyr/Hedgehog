
#include "commands_manager/sources/ph/cm_ph.hpp"

#include "commands_manager/sources/resources/cm_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {
namespace Resources {

/*---------------------------------------------------------------------------*/

namespace Commands {

/*---------------------------------------------------------------------------*/

	const char* const CommandsListCommandName = "cm.commands.list";

/*---------------------------------------------------------------------------*/

} // namespace Commands

/*---------------------------------------------------------------------------*/

namespace Exceptions {

/*---------------------------------------------------------------------------*/

	const char* const UnknownCommandMessageFormat = "Unknown command '%1'.";

	const char* const DisabledCommandMessageFormat = "'%1' command is disabled in this time.";

/*---------------------------------------------------------------------------*/

} // namespace Exceptions

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
