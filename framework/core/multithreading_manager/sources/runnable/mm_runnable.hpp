
#ifndef __MM_RUNNABLE_HPP__
#define __MM_RUNNABLE_HPP__

/*---------------------------------------------------------------------------*/

#include "multithreading_manager/h/mm_runnable_function.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

class Runnable
	:	public QRunnable
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Runnable( RunnableFunction _function );

	virtual ~Runnable();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void run();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	RunnableFunction m_function;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_RUNNABLE_HPP__
