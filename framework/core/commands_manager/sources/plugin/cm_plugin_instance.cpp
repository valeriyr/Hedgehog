
#include "commands_manager/sources/ph/cm_ph.hpp"

#include "commands_manager/sources/plugin/cm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"

#include "messenger/ms_imessenger.hpp"

#include "commands_manager/sources/commands_registry/cm_commands_registry.hpp"
#include "commands_manager/sources/command_executor/cm_command_executor.hpp"

#include "commands_manager/sources/resources/cm_internal_resources.hpp"

#include "commands_manager/sources/commands/cm_commands_list_command.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_COMMANDS_REGISTRY, m_commandsRegistry )
	INTERFACE_DECLARATION( IID_COMMAND_EXECUTOR, m_commandExecutor )

END_INTERFACE_MAP()


/*---------------------------------------------------------------------------*/


PluginInstance::PluginInstance()
{
} // PluginInstance::PluginInstance


/*---------------------------------------------------------------------------*/


PluginInstance::~PluginInstance()
{
} // PluginInstance::~PluginInstance


/*---------------------------------------------------------------------------*/


void
PluginInstance::initialize()
{
	m_commandsRegistry.reset( new CommandsRegistry() );
	m_commandExecutor.reset( new CommandExecutor( *m_commandsRegistry ) );

	m_commandsRegistry->registerCommand(
			Resources::Commands::CommandsListCommandName
		,	boost::intrusive_ptr< ICommand >( new CommandsListCommand( *m_commandsRegistry, *getSystemMessenger() ) ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_commandsRegistry->unregisterCommand( Resources::Commands::CommandsListCommandName );

	m_commandExecutor.reset();
	m_commandsRegistry.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Tools::Core::IMessenger >
PluginInstance::getSystemMessenger() const
{
	return
		getPluginInterface< Tools::Core::IMessenger >(
				Framework::Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Tools::Core::IID_MESSENGER );

} // PluginInstance::getSystemMessenger


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
