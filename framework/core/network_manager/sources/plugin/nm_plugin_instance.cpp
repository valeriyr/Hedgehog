
#include "network_manager/sources/ph/nm_ph.hpp"

#include "network_manager/sources/plugin/nm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "network_manager/sources/connection_manager/nm_connection_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_CONNECTION_MANAGER, m_connectionManager )

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
	m_connectionManager.reset( new ConnectionManager() );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_connectionManager.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
