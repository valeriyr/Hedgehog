
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/workers/mm_main_thread_worker.hpp"

#include "mm_main_thread_worker.moc"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


MainThreadWorker::MainThreadWorker( QObject* _parent )
	:	QObject( _parent )
	,	m_timer( new QTimer( this ) )
	,	m_tasksQueue()
{
	QObject::connect( m_timer, SIGNAL( timeout() ), this, SLOT( doWork() ) );

} // MainThreadWorker::MainThreadWorker


/*---------------------------------------------------------------------------*/


MainThreadWorker::~MainThreadWorker()
{
	QObject::disconnect( m_timer, SIGNAL( timeout() ), this, SLOT( doWork() ) );

} // MainThreadWorker::~MainThreadWorker


/*---------------------------------------------------------------------------*/


QString
MainThreadWorker::pushTask( RunnableFunction _function )
{
	return m_tasksQueue.pushTask( _function );

} // MainThreadWorker::pushTask


/*---------------------------------------------------------------------------*/


QString
MainThreadWorker::pushPeriodicalTask( RunnableFunction _function, const Tools::Core::Time::Milliseconds _period )
{
	return m_tasksQueue.pushPeriodicalTask( _function, _period );

} // MainThreadWorker::pushPeriodicalTask


/*---------------------------------------------------------------------------*/


QString
MainThreadWorker::pushDelayedTask( RunnableFunction _function, const Tools::Core::Time::Milliseconds _delay )
{
	return m_tasksQueue.pushDelayedTask( _function, _delay );

} // MainThreadWorker::pushDelayedTask


/*---------------------------------------------------------------------------*/


void
MainThreadWorker::removeTask( const QString& _taskId )
{
	m_tasksQueue.removeTask( _taskId );

} // MainThreadWorker::removeTask


/*---------------------------------------------------------------------------*/


void
MainThreadWorker::clear()
{
	m_tasksQueue.clear();

} // MainThreadWorker::clear


/*---------------------------------------------------------------------------*/


void
MainThreadWorker::start()
{
	m_timer->start( ms_period );

} // MainThreadWorker::start


/*---------------------------------------------------------------------------*/


void
MainThreadWorker::doWork()
{
	const Tools::Core::Time::Milliseconds startTime = Tools::Core::Time::currentTime();

	m_tasksQueue.refreshTasks();

	do
	{
		TaskData taskData( m_tasksQueue.getTaskForProcessing() );

		if ( !taskData.m_isInitialized )
			return;

		taskData.m_function();
	}
	while( Tools::Core::Time::currentTime() - startTime < ms_oneTickTimeLimit );

} // MainThreadWorker::doWork


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
