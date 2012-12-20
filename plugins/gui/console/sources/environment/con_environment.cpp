
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/environment/con_environment.hpp"

#include "console/sources/plugin/con_plugin_instance.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"


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


boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
Environment::getCommandsRegistry() const
{
	return m_pluginInstance.getCommandsRegistry();

} // Environment::getCommandsRegistry


/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
