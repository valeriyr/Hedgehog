
#include "script_engine/sources/ph/se_ph.hpp"

#include "script_engine/sources/plugin/se_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"

#include "script_engine/sources/scripts_executor/se_scripts_executor.hpp"
#include "script_engine/sources/environment/se_environment.hpp"

#include "messenger/ms_imessenger.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_SCRIPTS_EXECUTOR, m_scriptsExecutor.get() )

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
	m_environment.reset( new Environment( *this ) );
	m_scriptsExecutor.reset( new ScriptsExecutor( *m_environment ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_scriptsExecutor.reset();
	m_environment.reset();

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


boost::intrusive_ptr< Core::PluginsManager::ISystemInformation >
PluginInstance::getSystemInformation() const
{
	return
		getPluginInterface< Core::PluginsManager::ISystemInformation >(
				Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Core::PluginsManager::IID_SYSTEM_INFORMATION );

} // PluginInstance::getSystemInformation


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
