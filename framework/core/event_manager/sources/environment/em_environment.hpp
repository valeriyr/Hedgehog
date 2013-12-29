
#ifndef __EM_ENVIRONMENT_HPP__
#define __EM_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "event_manager/sources/environment/em_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ MultithreadingManager::TaskHandle
		pushPeriodicalTask(
					const QString& _threadName
				,	const MultithreadingManager::RunnableFunction& _function );

	/*virtual*/ void removeTask( const MultithreadingManager::TaskHandle& _taskHandle );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_ENVIRONMENT_HPP__
