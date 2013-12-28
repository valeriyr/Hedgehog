
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
	,	m_delayedTasksCollection()
	,	m_taskQueueLocker( QMutex::Recursive )
{
} // TasksQueue::TasksQueue


/*---------------------------------------------------------------------------*/


TasksQueue::~TasksQueue()
{
} // TasksQueue::~TasksQueue


/*---------------------------------------------------------------------------*/


QString
TasksQueue::pushTask( RunnableFunction _function )
{
	QMutexLocker locker( &m_taskQueueLocker );

	const QString taskId( QUuid::createUuid().toString() );

	m_readyTasksCollection.insert( std::make_pair( taskId, TaskData( _function ) ) );

	return taskId;

} // TasksQueue::pushTask


/*---------------------------------------------------------------------------*/


QString
TasksQueue::pushPeriodicalTask( RunnableFunction _function, const qint64 _period )
{
	QMutexLocker locker( &m_taskQueueLocker );

	const QString taskId( QUuid::createUuid().toString() );

	TaskData taskData( _function, _period );
	taskData.m_lastStart = QDateTime::currentDateTime().toMSecsSinceEpoch();

	m_periodicalTasksCollection.insert( std::make_pair( taskId, taskData ) );

	m_readyTasksCollection.insert( std::make_pair( taskId, taskData ) );

	return taskId;

} // TasksQueue::pushPeriodicalTask


/*---------------------------------------------------------------------------*/


QString
TasksQueue::pushDelayedTask( RunnableFunction _function, const qint64 _delay )
{
	QMutexLocker locker( &m_taskQueueLocker );

	const QString taskId( QUuid::createUuid().toString() );

	TaskData taskData( _function, _delay );

	taskData.m_lastStart = QDateTime::currentDateTime().toMSecsSinceEpoch();

	m_delayedTasksCollection.insert( std::make_pair( taskId, taskData ) );

	return taskId;

} // TasksQueue::pushDelayedTask


/*---------------------------------------------------------------------------*/


void
TasksQueue::removeTask( const QString& _taskId )
{
	QMutexLocker locker( &m_taskQueueLocker );

	m_delayedTasksCollection.erase( _taskId );
	m_periodicalTasksCollection.erase( _taskId );
	m_readyTasksCollection.erase( _taskId );

} // TasksQueue::removeTask


/*---------------------------------------------------------------------------*/


void
TasksQueue::clear()
{
	QMutexLocker locker( &m_taskQueueLocker );

	m_delayedTasksCollection.clear();
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
TasksQueue::refreshTasks()
{
	QMutexLocker locker( &m_taskQueueLocker );

	unsigned int tasksCount = 0;

	TasksCollectionIterator
			beginPeriodical = m_periodicalTasksCollection.begin()
		,	endPeriodical = m_periodicalTasksCollection.end();

	for( ; beginPeriodical != endPeriodical ; ++beginPeriodical )
	{
		const qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

		if ( currentTime - beginPeriodical->second.m_lastStart >= beginPeriodical->second.m_time )
		{
			if ( m_readyTasksCollection.find( beginPeriodical->first ) != m_readyTasksCollection.end() )
				continue;

			beginPeriodical->second.m_lastStart = currentTime;
			m_readyTasksCollection.insert( std::make_pair( beginPeriodical->first, beginPeriodical->second ) );
			++tasksCount;
		}
	}

	std::vector< QString > delayedTasksToRemove;

	for(	TasksCollectionIterator beginDeleyed = m_delayedTasksCollection.begin()
		;	beginDeleyed != m_delayedTasksCollection.end()
		;	++beginDeleyed )
	{
		const qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

		if ( currentTime - beginDeleyed->second.m_lastStart >= beginDeleyed->second.m_time )
		{
			assert( m_readyTasksCollection.find( beginDeleyed->first ) == m_readyTasksCollection.end() );

			m_readyTasksCollection.insert( std::make_pair( beginDeleyed->first, beginDeleyed->second ) );
			++tasksCount;

			delayedTasksToRemove.push_back( beginDeleyed->first );
		}
	}

	std::vector< QString >::const_iterator
			begin = delayedTasksToRemove.begin()
		,	end = delayedTasksToRemove.end();

	for( ; begin != end ; ++begin )
	{
		m_delayedTasksCollection.erase( *begin );
	}

	return tasksCount;

} // TasksQueue::refreshTasks


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
