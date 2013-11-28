
#include "event_manager/sources/ph/em_ph.hpp"

#include "event_manager/sources/environment/em_environment.hpp"

#include "event_manager/sources/plugin/em_plugin_instance.hpp"


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
Environment::pushTask(	const QString& _threadName
					,	const MultithreadingManager::RunnableFunction& _function )
{
	return m_pluginInstance.getMultithreadingManager()->pushTask( _threadName, _function, 500 );

} // Environment::pushTask


/*---------------------------------------------------------------------------*/


void
Environment::removeTask( const MultithreadingManager::TaskHandle& _taskHandle )
{
	m_pluginInstance.getMultithreadingManager()->removeTask( _taskHandle );

} // Environment::removeTask


/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
