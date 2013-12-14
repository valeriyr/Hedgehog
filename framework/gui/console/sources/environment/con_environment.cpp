
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/environment/con_environment.hpp"

#include "console/sources/plugin/con_plugin_instance.hpp"

#include "script_engine/ih/se_iscripts_executor.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/


Environment::Environment( const PluginInstance& _pluginInstance )
	:	m_pluginInstance( _pluginInstance )
{
} // Environment::Environment


/*---------------------------------------------------------------------------*/


Environment::~Environment()
{
} // Environment::~Environment


/*---------------------------------------------------------------------------*/


void
Environment::executeScript( const QString& _script ) const
{
	m_pluginInstance.getScriptsExecutor()->executeScript( _script );

} // Environment::executeCommand


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
