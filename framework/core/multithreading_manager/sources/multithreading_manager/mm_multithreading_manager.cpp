
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/multithreading_manager/mm_multithreading_manager.hpp"

#include "multithreading_manager/sources/runnable/mm_runnable.hpp"
#include "multithreading_manager/sources/workers/mm_worker.hpp"
#include "multithreading_manager/sources/workers/mm_main_thread_worker.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


MultithreadingManager::MultithreadingManager()
	:	m_threadPool()
	,	m_threadsCollection()
	,	m_mainThreadWorker( new MainThreadWorker() )
{
	m_mainThreadWorker->start();
	m_mainThreadWorker->pushPeriodicalTask( boost::bind( &MultithreadingManager::refreshTasks, this ), MainThreadWorker::ms_period - 10 );

} // MultithreadingManager::MultithreadingManager


/*---------------------------------------------------------------------------*/


MultithreadingManager::~MultithreadingManager()
{
	m_mainThreadWorker->clear();
	assert( m_threadsCollection.empty() );

} // MultithreadingManager::~MultithreadingManager


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::startThread( const QString& _threadName )
{
	if (	_threadName != Resources::MainThreadName
		&&	m_threadsCollection.find( _threadName ) == m_threadsCollection.end() )
	{
		Worker* worker = new Worker();

		boost::shared_ptr< QThread > thread( new QThread() );

		QObject::connect( thread.get(), SIGNAL( started() ), worker, SLOT( doWork() ) );
		QObject::connect( thread.get(), SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
		worker->moveToThread( thread.get() );

		m_threadsCollection.insert( std::make_pair( _threadName, ThreadData( thread, worker ) ) );

		thread->start();
	}

} // MultithreadingManager::startThread


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::stopThread( const QString& _threadName )
{
	if ( _threadName == Resources::MainThreadName )
		return;

	ThreadsCollectionIterator iterator = m_threadsCollection.find( _threadName );

	if ( iterator != m_threadsCollection.end() )
	{
		iterator->second.m_worker->stop();

		iterator->second.m_thread->quit();
		iterator->second.m_thread->wait();

		m_threadsCollection.erase( _threadName );
	}

} // MultithreadingManager::stopThread


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::run( RunnableFunction _function )
{
	Runnable* runnable = new Runnable( _function );
	m_threadPool.start( runnable );

} // MultithreadingManager::run


/*---------------------------------------------------------------------------*/


TaskHandle
MultithreadingManager::pushTask( const QString& _threadName, RunnableFunction _function )
{
	if ( _threadName == Resources::MainThreadName )
	{
		return TaskHandle( _threadName, m_mainThreadWorker->pushTask( _function ) );
	}
	else
	{
		ThreadsCollectionIterator iterator = m_threadsCollection.find( _threadName );

		return		iterator != m_threadsCollection.end()
				?	TaskHandle( _threadName, iterator->second.m_worker->pushTask( _function ) )
				:	TaskHandle();
	}

} // MultithreadingManager::pushTask


/*---------------------------------------------------------------------------*/


TaskHandle
MultithreadingManager::pushPeriodicalTask(
		const QString& _threadName
	,	RunnableFunction _function
	,	const qint64 _period )
{
	if ( _threadName == Resources::MainThreadName )
	{
		return TaskHandle( _threadName, m_mainThreadWorker->pushPeriodicalTask( _function, _period ) );
	}
	else
	{
		ThreadsCollectionIterator iterator = m_threadsCollection.find( _threadName );

		return		iterator != m_threadsCollection.end()
				?	TaskHandle( _threadName, iterator->second.m_worker->pushPeriodicalTask( _function, _period ) )
				:	TaskHandle();
	}

} // MultithreadingManager::pushPeriodicalTask


/*---------------------------------------------------------------------------*/


TaskHandle
MultithreadingManager::pushDelayedTask(
		const QString& _threadName
	,	RunnableFunction _function
	,	const qint64 _delay )
{
	if ( _threadName == Resources::MainThreadName )
	{
		return TaskHandle( _threadName, m_mainThreadWorker->pushDelayedTask( _function, _delay ) );
	}
	else
	{
		ThreadsCollectionIterator iterator = m_threadsCollection.find( _threadName );

		return		iterator != m_threadsCollection.end()
				?	TaskHandle( _threadName, iterator->second.m_worker->pushDelayedTask( _function, _delay ) )
				:	TaskHandle();
	}

} // MultithreadingManager::pushDelayedTask


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::removeTask( const TaskHandle& _taskHandle )
{
	if ( _taskHandle.m_threadName == Resources::MainThreadName )
	{
		m_mainThreadWorker->removeTask( _taskHandle.m_taskId );
	}
	else
	{
		ThreadsCollectionIterator iterator = m_threadsCollection.find( _taskHandle.m_threadName );

		if ( iterator != m_threadsCollection.end() )
		{
			iterator->second.m_worker->removeTask( _taskHandle.m_taskId );
		}
	}

} // MultithreadingManager::removeTask


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::refreshTasks()
{
	ThreadsCollectionIterator
			begin = m_threadsCollection.begin()
		,	end = m_threadsCollection.end();

	for ( ; begin != end ; ++begin )
	{
		begin->second.m_worker->refreshTasks();
	}

} // MultithreadingManager::refreshTasks


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
