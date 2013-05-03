
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/multithreading_manager/mm_multithreading_manager.hpp"

#include "multithreading_manager/sources/runnable/mm_runnable.hpp"
#include "multithreading_manager/sources/worker/mm_worker.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


MultithreadingManager::MultithreadingManager()
	:	m_threadPool()
	,	m_threadsCollection()
{
} // MultithreadingManager::MultithreadingManager


/*---------------------------------------------------------------------------*/


MultithreadingManager::~MultithreadingManager()
{
	assert( m_threadsCollection.empty() );

} // MultithreadingManager::~MultithreadingManager


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::run( RunnableFunction _function )
{
	Runnable* runnable = new Runnable( _function );
	m_threadPool.start( runnable );

} // MultithreadingManager::run


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::run(
		const QString& _threadName
	,	RunnableFunction _function
	,	const unsigned int _period )
{
	assert( m_threadsCollection.find( _threadName ) == m_threadsCollection.end() );

	Worker* worker = new Worker( _function, _period );

	boost::shared_ptr< QThread > thread( new QThread() );

	QObject::connect( thread.get(), SIGNAL( started() ), worker, SLOT( startTimer() ) );
	QObject::connect( thread.get(), SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
	worker->moveToThread( thread.get() );

	m_threadsCollection.insert( std::make_pair( _threadName, thread ) );

	thread->start();

} // MultithreadingManager::run


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::stop( const QString& _threadName )
{
	ThreadsCollectionIterator iterator = m_threadsCollection.find( _threadName );

	if ( iterator != m_threadsCollection.end() )
	{
		iterator->second->quit();
		iterator->second->wait();

		m_threadsCollection.erase( iterator );
	}

} // MultithreadingManager::stop


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
