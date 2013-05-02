
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/environment/gm_environment.hpp"

#include "game_manager/sources/plugin/gm_plugin_instance.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"


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


void
Environment::run(
		const QString& _threadName
	,	Framework::Core::MultithreadingManager::RunnableFunction _function ) const
{
	m_pluginInstance.getMultithreadingManager()->run( _threadName, _function, 1000 );

} // Environment::run


/*---------------------------------------------------------------------------*/


void
Environment::stop( const QString& _threadName ) const
{
	m_pluginInstance.getMultithreadingManager()->stop( _threadName );

} // Environment::stop


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
