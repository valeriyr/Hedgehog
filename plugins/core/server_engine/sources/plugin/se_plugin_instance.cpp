
#include "server_engine/sources/ph/se_ph.hpp"

#include "server_engine/sources/plugin/se_plugin_instance.hpp"

#include "server_engine/sources/environment/se_environment.hpp"
#include "server_engine/sources/server_engine/se_server_engine.hpp"
#include "server_engine/sources/internal_resources/se_internal_resources.hpp"

#include "messenger/ms_imessenger.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"

#include "network_manager/h/nm_plugin_id.hpp"
#include "network_manager/ih/nm_iconnection_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

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
	m_environment->printMessage( Resources::Messanges::IntroMessage );

	m_serverEngine.reset( new ServerEngine( *m_environment ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_serverEngine.reset();
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


boost::intrusive_ptr< Framework::Core::NetworkManager::IConnectionManager >
PluginInstance::getConnectionManager() const
{
	return
		getPluginInterface< Framework::Core::NetworkManager::IConnectionManager >(
				Framework::Core::NetworkManager::PID_NETWORK_MANAGER
			,	Framework::Core::NetworkManager::IID_CONNECTION_MANAGER );

} // PluginInstance::getConnectionManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
