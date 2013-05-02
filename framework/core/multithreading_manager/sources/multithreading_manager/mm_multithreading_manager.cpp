
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/multithreading_manager/mm_multithreading_manager.hpp"

#include "multithreading_manager/sources/runnable/mm_runnable.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


MultithreadingManager::MultithreadingManager()
	:	m_threadPool()
{
} // MultithreadingManager::MultithreadingManager


/*---------------------------------------------------------------------------*/


MultithreadingManager::~MultithreadingManager()
{
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
MultithreadingManager::run( const QString& _threadName, RunnableFunction _function )
{
} // MultithreadingManager::run


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::run(
		const QString& _threadName
	,	RunnableFunction _function
	,	const unsigned int _period )
{
} // MultithreadingManager::run


/*---------------------------------------------------------------------------*/


void
MultithreadingManager::stop( const QString& _threadName )
{
} // MultithreadingManager::stop


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
