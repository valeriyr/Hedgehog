
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/environment/wm_environment.hpp"

#include "window_manager/sources/plugin/wm_plugin_instance.hpp"

#include "commands_manager/ih/cm_icommand_executor.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

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

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
