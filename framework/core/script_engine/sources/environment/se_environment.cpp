
#include "script_engine/sources/ph/se_ph.hpp"

#include "script_engine/sources/environment/se_environment.hpp"

#include "script_engine/sources/plugin/se_plugin_instance.hpp"

#include "plugins_manager/ih/pm_isystem_information.hpp"

#include "messenger/ms_imessenger.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ScriptEngine {

/*---------------------------------------------------------------------------*/


Environment::Environment( PluginInstance& _pluginInstance )
	:	m_pluginInstance( _pluginInstance )
{
} // Environment::Environment


/*---------------------------------------------------------------------------*/


Environment::~Environment()
{
} // Environment::~Environment


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Tools::Core::IMessenger >
Environment::getSystemMessenger() const
{
	return m_pluginInstance.getSystemMessenger();

} // Environment::getSystemMessenger


/*---------------------------------------------------------------------------*/


const QString&
Environment::getSystemConfigDirectory() const
{
	return m_pluginInstance.getSystemInformation()->getConfigDirectory();

} // Environment::getSystemConfigDirectory


/*---------------------------------------------------------------------------*/

} // namespace ScriptEngine
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
