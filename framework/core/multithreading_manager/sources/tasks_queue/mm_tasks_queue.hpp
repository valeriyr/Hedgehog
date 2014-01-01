
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
			,	m_time( 0 )
			,	m_isInitialized( false )
		{}

		TaskData(
				RunnableFunction _function
			,	const qint64 _time
			)
			:	m_function( _function )
			,	m_time( _time )
			,	m_lastStart( 0 )
			,	m_isInitialized( true )
		{}

		TaskData( RunnableFunction _function )
			:	m_function( _function )
			,	m_time( 0 )
			,	m_lastStart( 0 )
			,	m_isInitialized( true )
		{}

		RunnableFunction m_function;
		qint64 m_time;
		qint64 m_lastStart;

		bool m_isInitialized;
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

	QString pushTask( RunnableFunction _function );

	QString pushPeriodicalTask( RunnableFunction _function, const qint64 _period );

	QString pushDelayedTask( RunnableFunction _function, const qint64 _dalay );

/*---------------------------------------------------------------------------*/

	void removeTask( const QString& _taskId );

	void clear();

	TaskData getTaskForProcessing();

/*---------------------------------------------------------------------------*/

	unsigned int refreshTasks();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, TaskData >
		TasksCollection;
	typedef
		TasksCollection::iterator
		TasksCollectionIterator;

	typedef
		std::vector< std::pair< QString, TaskData > >
		ReadyTasksCollection;
	typedef
		ReadyTasksCollection::iterator
		ReadyTasksCollectionIterator;

/*---------------------------------------------------------------------------*/

	ReadyTasksCollection m_readyTasksCollection;

	TasksCollection m_periodicalTasksCollection;
	TasksCollection m_delayedTasksCollection;

	QMutex m_taskQueueLocker;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_TASKS_QUEUE_HPP__
