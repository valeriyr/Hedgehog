
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/workers/mm_worker.hpp"

#include "mm_worker.moc"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


Worker::Worker( QObject* _parent )
	:	QObject( _parent )
	,	m_semaphore()
	,	m_stopped( false )
{
} // Worker::Worker


/*---------------------------------------------------------------------------*/


Worker::~Worker()
{
} // Worker::~Worker


/*---------------------------------------------------------------------------*/


QString
Worker::pushTask( RunnableFunction _function, const qint64 _period )
{
	const QString taskId( m_tasksQueue.pushTask( _function, _period ) );

	m_semaphore.release( 1 );

	return taskId;

} // Worker::pushTask


/*---------------------------------------------------------------------------*/


void
Worker::removeTask( const QString& _taskId )
{
	m_tasksQueue.removeTask( _taskId );

} // Worker::removeTask


/*---------------------------------------------------------------------------*/


void
Worker::refreshPeriodicalTasks()
{
	m_semaphore.release( m_tasksQueue.refreshPeriodicalTasks() );

} // Worker::refreshPeriodicalTasks


/*---------------------------------------------------------------------------*/


void
Worker::clear()
{
	m_tasksQueue.clear();

} // Worker::clear


/*---------------------------------------------------------------------------*/


void
Worker::stop()
{
	m_tasksQueue.clear();
	m_stopped = true;

	m_semaphore.release( 1 );

} // Worker::stop


/*---------------------------------------------------------------------------*/


void
Worker::doWork()
{
	while( !m_stopped )
	{
		m_semaphore.acquire();

		TaskData taskData( m_tasksQueue.getTaskForProcessing() );

		if ( !taskData.m_isInitialized )
			continue;

		taskData.m_function();
	}

} // Worker::doWork


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
