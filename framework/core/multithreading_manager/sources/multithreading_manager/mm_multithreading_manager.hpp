
#ifndef __MM_MULTITHREADING_MANAGER_HPP__
#define __MM_MULTITHREADING_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

class Worker;
class MainThreadWorker;

/*---------------------------------------------------------------------------*/

class MultithreadingManager
	:	public Tools::Core::BaseWrapper< IMultithreadingManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MultithreadingManager();

	virtual ~MultithreadingManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void startThread( const QString& _threadName );

	/*virtual*/ void stopThread( const QString& _threadName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void run( RunnableFunction _function );

/*---------------------------------------------------------------------------*/

	/*virtual*/ TaskHandle pushTask( const QString& _threadName, RunnableFunction _function );

	/*virtual*/ TaskHandle pushPeriodicalTask(
			const QString& _threadName
		,	RunnableFunction _function
		,	const Tools::Core::Time::Milliseconds _period );

	/*virtual*/ TaskHandle pushDelayedTask(
			const QString& _threadName
		,	RunnableFunction _function
		,	const Tools::Core::Time::Milliseconds _delay );

	/*virtual*/ void removeTask( const TaskHandle& _taskHandle );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void refreshTasks();

/*---------------------------------------------------------------------------*/

	struct ThreadData
	{
		ThreadData(
				boost::shared_ptr< QThread > _thread
			,	Worker* _worker
			)
			:	m_thread( _thread )
			,	m_worker( _worker )
		{
			assert( m_thread && m_worker && "Worker and Thread should not be NULL!" );
		}

		boost::shared_ptr< QThread > m_thread;
		Worker* m_worker;
	};

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, ThreadData >
		ThreadsCollection;
	typedef
		ThreadsCollection::iterator
		ThreadsCollectionIterator;

/*---------------------------------------------------------------------------*/

	QThreadPool m_threadPool;

	ThreadsCollection m_threadsCollection;

	boost::shared_ptr< MainThreadWorker > m_mainThreadWorker;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_MULTITHREADING_MANAGER_HPP__
