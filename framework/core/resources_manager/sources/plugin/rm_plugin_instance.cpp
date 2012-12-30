
#include "resources_manager/sources/ph/rm_ph.hpp"

#include "resources_manager/sources/plugin/rm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "resources_manager/sources/resources_manager/rm_resources_manager.hpp"

#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace ResourcesManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_RESOURCES_MANAGER, m_resourcesManager.get() )

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
	m_resourcesManager.reset( new ResourcesManager( getSystemInformation()->getResourcesDirectory() ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_resourcesManager.reset();

} // PluginInstance::close


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

} // namespace ResourcesManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
