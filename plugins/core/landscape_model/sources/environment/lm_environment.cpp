
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/environment/lm_environment.hpp"

#include "landscape_model/sources/plugin/lm_plugin_instance.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

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
Environment::pushTask(
		const QString& _threadName
	,	Framework::Core::MultithreadingManager::RunnableFunction _function
	,	const qint64 _period ) const
{
	return m_pluginInstance.getMultithreadingManager()->pushTask( _threadName, _function, _period );

} // Environment::pushTask


/*---------------------------------------------------------------------------*/


void
Environment::printMessage( const QString& _message ) const
{
	m_pluginInstance.getSystemMessenger()->printMessage( _message );

} // Environment::printMessage


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
