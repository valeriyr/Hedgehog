
#ifndef __MM_TASKS_QUEUE_HPP__
#define __MM_TASKS_QUEUE_HPP__

/*---------------------------------------------------------------------------*/

#include "multithreading_manager/h/mm_runnable_function.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

	struct TaskData
	{

		TaskData()
			:	m_function()
			,	m_period()
			,	m_isInitialized( false )
		{}

		TaskData(
				RunnableFunction _function
			,	const qint64 _period
			)
			:	m_function( _function )
			,	m_period( _period )
			,	m_lastStart( 0 )
			,	m_isInitialized( true )
		{}

		TaskData( RunnableFunction _function )
			:	m_function( _function )
			,	m_period( 0 )
			,	m_lastStart( 0 )
			,	m_isInitialized( true )
		{}

		bool isPeriodical() { return m_period > 0; }

		RunnableFunction m_function;
		qint64 m_period;
		qint64 m_lastStart;

		const bool m_isInitialized;
	};

/*---------------------------------------------------------------------------*/

class TasksQueue
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	TasksQueue();

	virtual ~TasksQueue();

/*---------------------------------------------------------------------------*/

	QString pushTask( RunnableFunction _function, const qint64 _period );

	void removeTask( const QString& _taskId );

	void clear();

	TaskData getTaskForProcessing();

/*---------------------------------------------------------------------------*/

	unsigned int refreshPeriodicalTasks();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, TaskData >
		TasksCollection;
	typedef
		TasksCollection::iterator
		TasksCollectionIterator;

/*---------------------------------------------------------------------------*/

	TasksCollection m_readyTasksCollection;
	TasksCollection m_periodicalTasksCollection;

	QMutex m_taskQueueLocker;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_TASKS_QUEUE_HPP__
