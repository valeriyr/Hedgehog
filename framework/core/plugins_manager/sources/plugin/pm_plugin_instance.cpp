
#include "plugins_manager/sources/ph/pm_ph.hpp"

#include "plugins_manager/sources/plugin/pm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "plugins_manager/sources/plugins_manager/pm_plugins_manager.hpp"
#include "plugins_manager/sources/plugins_serializer/pm_plugins_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

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
PluginInstance::initialize( const std::string& _pluginsDirectory )
{
	m_pluginsManager.reset( new PluginsManager( _pluginsDirectory ) );

	PluginsSerializer pluginsSerializer( *m_pluginsManager );
	pluginsSerializer.loadPluginsList();

	m_pluginsManager->loadPlugins();

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_pluginsManager->closePlugins();
	m_pluginsManager.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

extern "C" __declspec( dllexport )
IPluginInstance*
getPluginsManager()
{
	return new PluginInstance();
}

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
