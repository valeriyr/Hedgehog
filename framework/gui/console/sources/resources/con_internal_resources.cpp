
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/resources/con_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const char* const ConsoleViewTitle = "Console";

	const char* const ConsolePlaceHolderText = "You can enter some commands or any lua code here. To see the list of all commands enter 'cm.commands.list'.";

/*---------------------------------------------------------------------------*/

	const char* const ErrorMessageFormat = "&gt; <font color = 'red' >%1: %2</font>";

	const char* const WarningMessageFormat = "&gt; <font color = 'blue' >%1: %2</font>";

	const char* const InfoMessageFormat = "&gt; <font>%1: %2</font>";

	const char* const ErrorMessageWithModuleNameFormat = "&gt; <font color = 'red' >%1: %2. %3</font>";

	const char* const WarningMessageWithModuleNameFormat = "&gt; <font color = 'blue' >%1: %2. %3</font>";

	const char* const InfoMessageWithModuleNameFormat = "&gt; <font>%1: %2. %3</font>";

	const char* const MessageWithoutPrefixFormat = "&gt; <font>%1</font>";

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
