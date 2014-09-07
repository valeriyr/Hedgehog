
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/environment/lm_environment.hpp"

#include "landscape_model/sources/plugin/lm_plugin_instance.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"
#include "landscape_model/sources/notification_center/lm_inotification_center.hpp"
#include "landscape_model/sources/model_locker/lm_model_locker.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "event_manager/ih/em_ievent_manager.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"
#include "network_manager/ih/nm_iconnection_manager.hpp"
#include "network_manager/ih/nm_iudp_connection.hpp"

#include "messenger/ms_imessenger.hpp"

#include "settings/ih/st_isettings.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

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
Environment::pushPeriodicalTask(
		const QString& _threadName
	,	Framework::Core::MultithreadingManager::RunnableFunction _function
	,	const Tools::Core::Time::Milliseconds _period ) const
{
	return m_pluginInstance.getMultithreadingManager()->pushPeriodicalTask( _threadName, _function, _period );

} // Environment::pushPeriodicalTask


/*---------------------------------------------------------------------------*/


Framework::Core::MultithreadingManager::TaskHandle
Environment::pushTask(
		const QString& _threadName
	,	Framework::Core::MultithreadingManager::RunnableFunction _function ) const
{
	return m_pluginInstance.getMultithreadingManager()->pushTask( _threadName, _function );

} // Environment::pushTask


/*---------------------------------------------------------------------------*/


void
Environment::removeTask( const Framework::Core::MultithreadingManager::TaskHandle& _handle ) const
{
	return m_pluginInstance.getMultithreadingManager()->removeTask( _handle );

} // Environment::removeTask


/*---------------------------------------------------------------------------*/


void
Environment::printMessage(
		const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
	,	const QString& _message ) const
{
	m_pluginInstance.getSystemMessenger()->printMessage( Resources::ModuleName, _messageLevel, _message );

} // Environment::printMessage


/*---------------------------------------------------------------------------*/


void
Environment::riseEvent( const Framework::Core::EventManager::Event& _event ) const
{
	m_pluginInstance.getEventManager()->raise( _event );

} // Environment::riseEvent


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< INotificationCenter >
Environment::getNotificationCenter() const
{
	return m_pluginInstance.getNotificationCenter();

} // Environment::getNotificationCenter


/*---------------------------------------------------------------------------*/


QString
Environment::getApplicationDirectory() const
{
	return m_pluginInstance.getSystemInformation()->getApplicationDirectory();

} // Environment::getApplicationDirectory


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::NetworkManager::IUdpConnection >
Environment::getConnection(
		const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo
	,	const unsigned int _connectionTimeOut ) const
{
	return m_pluginInstance.getConnectionManager()->getUdpConnection( _connectionInfo, _connectionTimeOut );

} // Environment::getConnection


/*---------------------------------------------------------------------------*/


void
Environment::closeConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const
{
	m_pluginInstance.getConnectionManager()->closeUdpConnection( _connectionInfo );

} // Environment::closeConnection


/*---------------------------------------------------------------------------*/


QString
Environment::getString( const QString& _key ) const
{
	return m_pluginInstance.getSettings()->getString( _key );

} // Environment::getString


/*---------------------------------------------------------------------------*/


unsigned int
Environment::getUInt( const QString& _key ) const
{
	return m_pluginInstance.getSettings()->getUInt( _key );

} // Environment::getUInt


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IModelLocker >
Environment::lockModel() const
{
	return m_pluginInstance.getLandscapeModelLocker();

} // Environment::lockModel


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
