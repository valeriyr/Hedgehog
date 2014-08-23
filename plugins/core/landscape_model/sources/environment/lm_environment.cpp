
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/environment/lm_environment.hpp"

#include "landscape_model/sources/plugin/lm_plugin_instance.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"
#include "landscape_model/sources/notification_center/lm_inotification_center.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "event_manager/ih/em_ievent_manager.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"
#include "network_manager/ih/nm_iconnection_manager.hpp"

#include "messenger/ms_imessenger.hpp"


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
	,	const qint64 _period ) const
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

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
