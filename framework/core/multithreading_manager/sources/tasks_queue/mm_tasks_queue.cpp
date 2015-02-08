
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
	,	m_mutex( QMutex::Recursive )
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
	QMutexLocker locker( &m_mutex );

	const QString taskId( QUuid::createUuid().toString() );

	m_readyTasksCollection.push_back( std::make_pair( taskId, TaskData( _function ) ) );

	return taskId;

} // TasksQueue::pushTask


/*---------------------------------------------------------------------------*/


QString
TasksQueue::pushPeriodicalTask( RunnableFunction _function, const Tools::Core::Time::Milliseconds _period )
{
	QMutexLocker locker( &m_mutex );

	const QString taskId( QUuid::createUuid().toString() );

	TaskData taskData( _function, _period );
	taskData.m_lastStart = Tools::Core::Time::currentTime();

	m_periodicalTasksCollection.insert( std::make_pair( taskId, taskData ) );

	m_readyTasksCollection.push_back( std::make_pair( taskId, taskData ) );

	return taskId;

} // TasksQueue::pushPeriodicalTask


/*---------------------------------------------------------------------------*/


QString
TasksQueue::pushDelayedTask( RunnableFunction _function, const Tools::Core::Time::Milliseconds _delay )
{
	QMutexLocker locker( &m_mutex );

	const QString taskId( QUuid::createUuid().toString() );

	TaskData taskData( _function, _delay );

	taskData.m_lastStart = Tools::Core::Time::currentTime();

	m_delayedTasksCollection.insert( std::make_pair( taskId, taskData ) );

	return taskId;

} // TasksQueue::pushDelayedTask


/*---------------------------------------------------------------------------*/


void
TasksQueue::removeTask( const QString& _taskId )
{
	QMutexLocker locker( &m_mutex );

	m_delayedTasksCollection.erase( _taskId );
	m_periodicalTasksCollection.erase( _taskId );

	ReadyTasksCollectionIterator
			begin = m_readyTasksCollection.begin()
		,	end = m_readyTasksCollection.end();

	for ( ; begin != end; ++begin )
	{
		if ( begin->first == _taskId )
		{
			m_readyTasksCollection.erase( begin );
			break;
		}
	}

} // TasksQueue::removeTask


/*---------------------------------------------------------------------------*/


void
TasksQueue::clear()
{
	QMutexLocker locker( &m_mutex );

	m_delayedTasksCollection.clear();
	m_periodicalTasksCollection.clear();
	m_readyTasksCollection.clear();

} // TasksQueue::clear


/*---------------------------------------------------------------------------*/


TaskData
TasksQueue::getTaskForProcessing()
{
	QMutexLocker locker( &m_mutex );

	if ( m_readyTasksCollection.empty() )
		return TaskData();

	TaskData taskData( m_readyTasksCollection.begin()->second );
	m_readyTasksCollection.erase( m_readyTasksCollection.begin() );

	return taskData;

} // TasksQueue::getTaskForProcessing


/*---------------------------------------------------------------------------*/


quint32
TasksQueue::refreshTasks()
{
	QMutexLocker locker( &m_mutex );

	quint32 tasksCount = 0;

	TasksCollectionIterator
			beginPeriodical = m_periodicalTasksCollection.begin()
		,	endPeriodical = m_periodicalTasksCollection.end();

	for( ; beginPeriodical != endPeriodical ; ++beginPeriodical )
	{
		const Tools::Core::Time::Milliseconds currentTime = Tools::Core::Time::currentTime();

		if ( currentTime - beginPeriodical->second.m_lastStart >= beginPeriodical->second.m_time )
		{
			ReadyTasksCollectionIterator
					beginReady = m_readyTasksCollection.begin()
				,	endReady = m_readyTasksCollection.end();

			for ( ; beginReady != endReady; ++beginReady )
			{
				if ( beginReady->first == beginPeriodical->first )
				{
					continue;
				}
			}

			beginPeriodical->second.m_lastStart = currentTime;
			m_readyTasksCollection.push_back( *beginPeriodical );
			++tasksCount;
		}
	}

	std::vector< QString > delayedTasksToRemove;

	for(	TasksCollectionIterator beginDeleyed = m_delayedTasksCollection.begin()
		;	beginDeleyed != m_delayedTasksCollection.end()
		;	++beginDeleyed )
	{
		const Tools::Core::Time::Milliseconds currentTime = Tools::Core::Time::currentTime();

		if ( currentTime - beginDeleyed->second.m_lastStart >= beginDeleyed->second.m_time )
		{
			ReadyTasksCollectionIterator
					beginReady = m_readyTasksCollection.begin()
				,	endReady = m_readyTasksCollection.end();

			for ( ; beginReady != endReady; ++beginReady )
			{
				if ( beginReady->first == beginDeleyed->first )
				{
					assert( !"Task should not be presented in the ready collection!" );
					continue;
				}
			}

			m_readyTasksCollection.push_back( *beginDeleyed );
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
