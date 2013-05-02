
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/runnable/mm_runnable.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


Runnable::Runnable( RunnableFunction _function )
	:	m_function( _function )
{
} // Runnable::Runnable


/*---------------------------------------------------------------------------*/


Runnable::~Runnable()
{
} // Runnable::~Runnable


/*---------------------------------------------------------------------------*/


void
Runnable::run()
{
	m_function();

} // Runnable::run


/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
