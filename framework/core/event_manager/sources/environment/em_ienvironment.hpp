
#ifndef __EM_IENVIRONMENT_HPP__
#define __EM_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

#include "messenger/ms_imessenger.hpp"

#include "time/t_time.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual MultithreadingManager::TaskHandle
		pushPeriodicalTask(
					const QString& _threadName
				,	const MultithreadingManager::RunnableFunction& _function
				,	const Tools::Core::Time::Milliseconds _timeLimit ) = 0;

	virtual void removeTask( const MultithreadingManager::TaskHandle& _taskHandle ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_IENVIRONMENT_HPP__
