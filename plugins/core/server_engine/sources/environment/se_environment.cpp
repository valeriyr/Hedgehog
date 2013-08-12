
#include "server_engine/sources/ph/se_ph.hpp"

#include "server_engine/sources/environment/se_environment.hpp"

#include "server_engine/sources/plugin/se_plugin_instance.hpp"

#include "messenger/ms_imessenger.hpp"

#include "network_manager/ih/nm_iconnection_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

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


void
Environment::printMessage( const QString& _message ) const
{
	m_pluginInstance.getSystemMessenger()->printMessage( _message );

} // Environment::printMessage


/*---------------------------------------------------------------------------*/


Framework::Core::NetworkManager::IUdpConnection&
Environment::getConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const
{
	return m_pluginInstance.getConnectionManager()->getUdpConnection( _connectionInfo );

} // Environment::getConnection


/*---------------------------------------------------------------------------*/


void
Environment::closeConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const
{
	m_pluginInstance.getConnectionManager()->closeUdpConnection( _connectionInfo );

} // Environment::closeConnection


/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
