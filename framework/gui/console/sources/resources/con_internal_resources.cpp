
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/resources/con_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const QString ConsoleViewTitle = "Console";

	const QString ConsolePlaceHolderText = "You can enter some commands or any lua code here. To see the list of all commands enter 'cm.commands.list'.";

/*---------------------------------------------------------------------------*/

	const QString ErrorMessageFormat = "&gt; <font color = 'red' >%1: %2</font>";

	const QString WarningMessageFormat = "&gt; <font color = 'blue' >%1: %2</font>";

	const QString InfoMessageFormat = "&gt; <font>%1: %2</font>";

	const QString SuccessMessageFormat = "&gt; <font color = 'green' >%1: %2</font>";

	const QString ErrorMessageWithModuleNameFormat = "&gt; <font color = 'red' ><b>%1:</b> %2. %3</font>";

	const QString WarningMessageWithModuleNameFormat = "&gt; <font color = 'blue' ><b>%1:</b> %2. %3</font>";

	const QString InfoMessageWithModuleNameFormat = "&gt; <font><b>%1:</b> %2. %3</font>";

	const QString SuccessMessageWithModuleNameFormat = "&gt; <font color = 'green' ><b>%1:</b> %2. %3</font>";

	const QString MessageWithoutPrefixFormat = "&gt; <font>%1</font>";

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
