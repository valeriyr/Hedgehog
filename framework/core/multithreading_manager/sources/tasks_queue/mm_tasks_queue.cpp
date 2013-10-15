
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/tasks_queue/mm_tasks_queue.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


TasksQueue::TasksQueue()
	:	m_readyTasksCollection()
	,	m_periodicalTasksCollection()
	,	m_taskQueueLocker( QMutex::Recursive )
{
} // TasksQueue::TasksQueue


/*---------------------------------------------------------------------------*/


TasksQueue::~TasksQueue()
{
} // TasksQueue::~TasksQueue


/*---------------------------------------------------------------------------*/


QString
TasksQueue::pushTask( RunnableFunction _function, const qint64 _period )
{
	QMutexLocker locker( &m_taskQueueLocker );

	const QString taskId( QUuid::createUuid().toString() );

	TaskData taskData( _function, _period );

	if ( taskData.isPeriodical() )
	{
		taskData.m_lastStart = QDateTime::currentDateTime().toMSecsSinceEpoch();
		m_periodicalTasksCollection.insert( std::make_pair( taskId, taskData ) );
	}

	m_readyTasksCollection.insert( std::make_pair( taskId, taskData ) );

	return taskId;

} // TasksQueue::pushTask


/*---------------------------------------------------------------------------*/


void
TasksQueue::removeTask( const QString& _taskId )
{
	QMutexLocker locker( &m_taskQueueLocker );

	m_periodicalTasksCollection.erase( _taskId );
	m_readyTasksCollection.erase( _taskId );

} // TasksQueue::removeTask


/*---------------------------------------------------------------------------*/


void
TasksQueue::clear()
{
	QMutexLocker locker( &m_taskQueueLocker );

	m_periodicalTasksCollection.clear();
	m_readyTasksCollection.clear();

} // TasksQueue::clear


/*---------------------------------------------------------------------------*/


TaskData
TasksQueue::getTaskForProcessing()
{
	QMutexLocker locker( &m_taskQueueLocker );

	if ( m_readyTasksCollection.empty() )
		return TaskData();

	TaskData taskData( m_readyTasksCollection.begin()->second );
	m_readyTasksCollection.erase( m_readyTasksCollection.begin() );

	return taskData;

} // TasksQueue::getTaskForProcessing


/*---------------------------------------------------------------------------*/


unsigned int
TasksQueue::refreshPeriodicalTasks()
{
	QMutexLocker locker( &m_taskQueueLocker );

	TasksCollectionIterator
			begin = m_periodicalTasksCollection.begin()
		,	end = m_periodicalTasksCollection.end();

	unsigned int tasksCount = 0;

	for( ; begin != end ; ++begin )
	{
		const qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

		if ( currentTime - begin->second.m_lastStart >= begin->second.m_period )
		{
			if ( m_readyTasksCollection.find( begin->first ) != m_readyTasksCollection.end() )
				continue;

			begin->second.m_lastStart = currentTime;
			m_readyTasksCollection.insert( std::make_pair( begin->first, begin->second ) );
			++tasksCount;
		}
	}

	return tasksCount;

} // TasksQueue::refreshPeriodicalTasks


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
