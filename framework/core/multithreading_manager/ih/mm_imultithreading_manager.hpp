
#ifndef __MM_IMULTITHREADING_MANAGER_HPP__
#define __MM_IMULTITHREADING_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "multithreading_manager/h/mm_runnable_function.hpp"
#include "multithreading_manager/h/mm_task_handle.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_MULTITHREADING_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IMultithreadingManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void startThread( const QString& _threadName ) = 0;

	virtual void stopThread( const QString& _threadName ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void run( RunnableFunction _function ) = 0;

/*---------------------------------------------------------------------------*/

	virtual TaskHandle pushTask( const QString& _threadName, RunnableFunction _function ) = 0;

	virtual TaskHandle pushPeriodicalTask( const QString& _threadName, RunnableFunction _function, const qint64 _period ) = 0;

	virtual TaskHandle pushDelayedTask( const QString& _threadName, RunnableFunction _function, const qint64 _delay ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void removeTask( const TaskHandle& _taskHandle ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_IMULTITHREADING_MANAGER_HPP__
