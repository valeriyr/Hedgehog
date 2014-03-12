
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
				,	const MultithreadingManager::RunnableFunction& _function
				,	const qint64 _timeLimit );

	/*virtual*/ void removeTask( const MultithreadingManager::TaskHandle& _taskHandle );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessage(
				const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
			,	const QString& _message ) const;

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
