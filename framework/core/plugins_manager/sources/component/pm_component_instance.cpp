
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/component/pm_component_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "plugins_manager/sources/plugins_manager/pm_plugins_manager.hpp"
#include "plugins_manager/sources/plugins_serializer/pm_plugins_serializer.hpp"
#include "plugins_manager/sources/system_information/pm_system_information.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


ComponentInstance::ComponentInstance()
{
} // ComponentInstance::ComponentInstance


/*---------------------------------------------------------------------------*/


ComponentInstance::~ComponentInstance()
{
} // ComponentInstance::~ComponentInstance


/*---------------------------------------------------------------------------*/


void
ComponentInstance::initialize( const SystemData& _systemData )
{
	m_systemInformation.reset( new SystemInformation( _systemData ) );

	m_pluginsManager.reset( new PluginsManager( m_systemInformation ) );

	PluginsSerializer pluginsSerializer( *m_pluginsManager, *m_systemInformation );
	pluginsSerializer.loadPluginsList();

	m_pluginsManager->loadPlugins();

} // ComponentInstance::initialize


/*---------------------------------------------------------------------------*/


void
ComponentInstance::close()
{
	m_pluginsManager->closePlugins();
	m_pluginsManager.reset();

	m_systemInformation.reset();

} // ComponentInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

extern "C" __declspec( dllexport )
IComponentInstance*
getComponentInstance()
{
	return new ComponentInstance();
}

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
