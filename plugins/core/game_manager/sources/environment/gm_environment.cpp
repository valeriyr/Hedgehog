
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/environment/gm_environment.hpp"

#include "game_manager/sources/plugin/gm_plugin_instance.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

#include "network_manager/ih/nm_iconnection_manager.hpp"

#include "sound_manager/ih/sm_isound_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_manager.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "messenger/ms_imessenger.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

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


boost::intrusive_ptr< LandscapeModel::IEditableLandscape >
Environment::getCurrentLandscape() const
{
	return m_pluginInstance.getLandscapeManager()->getCurrentLandscape();

} // Environment::getCurrentLandscape


/*---------------------------------------------------------------------------*/


void
Environment::startThread( const QString& _threadName ) const
{
	m_pluginInstance.getMultithreadingManager()->startThread( _threadName );

} // Environment::startThread


/*---------------------------------------------------------------------------*/


void
Environment::stopThread( const QString& _threadName ) const
{
	m_pluginInstance.getMultithreadingManager()->stopThread( _threadName );

} // Environment::stopThread


/*---------------------------------------------------------------------------*/


Framework::Core::MultithreadingManager::TaskHandle
Environment::pushTask(
		const QString& _threadName
	,	Framework::Core::MultithreadingManager::RunnableFunction _function
	,	const qint64 _period ) const
{
	return m_pluginInstance.getMultithreadingManager()->pushTask( _threadName, _function, _period );

} // Environment::pushTask


/*---------------------------------------------------------------------------*/


void
Environment::playSound( const QString& _resourcePath ) const
{
	m_pluginInstance.getSoundManager()->play( _resourcePath );

} // Environment::playSound


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

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
