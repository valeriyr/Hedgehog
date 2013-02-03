
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/environment/con_environment.hpp"

#include "console/sources/plugin/con_plugin_instance.hpp"

#include "commands_manager/ih/cm_icommand_executor.hpp"


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


boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandExecutor >
Environment::getCommandExecutor() const
{
	return m_pluginInstance.getCommandExecutor();

} // Environment::getCommandExecutor


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
