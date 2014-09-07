
#include "event_manager/sources/ph/em_ph.hpp"

#include "event_manager/sources/environment/em_environment.hpp"

#include "event_manager/sources/plugin/em_plugin_instance.hpp"

#include "event_manager/sources/resources/em_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

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


MultithreadingManager::TaskHandle
Environment::pushPeriodicalTask(
		const QString& _threadName
	,	const MultithreadingManager::RunnableFunction& _function
	,	const Tools::Core::Time::Milliseconds _timeLimit )
{
	return m_pluginInstance.getMultithreadingManager()->pushPeriodicalTask( _threadName, _function, _timeLimit );

} // Environment::pushPeriodicalTask


/*---------------------------------------------------------------------------*/


void
Environment::removeTask( const MultithreadingManager::TaskHandle& _taskHandle )
{
	m_pluginInstance.getMultithreadingManager()->removeTask( _taskHandle );

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

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
