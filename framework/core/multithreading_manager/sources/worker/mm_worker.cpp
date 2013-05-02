
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/worker/mm_worker.hpp"

#include "mm_worker.moc"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


Worker::Worker(
		RunnableFunction _function
	,	const unsigned int _period
	,	QObject* _parent
	)
	:	QObject( _parent )
	,	m_function( _function )
	,	m_period( _period )
	,	m_timer( new QTimer( this ) )
{
	QObject::connect( m_timer, SIGNAL( timeout() ), this, SLOT( doWork() ) );

} // Worker::Worker


/*---------------------------------------------------------------------------*/


Worker::~Worker()
{
	QObject::disconnect( m_timer, SIGNAL( timeout() ), this, SLOT( doWork() ) );

} // Worker::~Worker


/*---------------------------------------------------------------------------*/


void
Worker::startTimer()
{
	m_timer->start( m_period );

} // Worker::startTimer


/*---------------------------------------------------------------------------*/


void
Worker::doWork()
{
	m_function();

} // Worker::doWork


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
