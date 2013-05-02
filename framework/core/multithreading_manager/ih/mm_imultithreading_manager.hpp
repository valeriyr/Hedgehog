
#ifndef __MM_IMULTITHREADING_MANAGER_HPP__
#define __MM_IMULTITHREADING_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "multithreading_manager/h/mm_runnable_function.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_MULTITHREADING_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IMultithreadingManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void run( RunnableFunction _function ) = 0;

	virtual void run(
			const QString& _threadName
		,	RunnableFunction _function
		,	const unsigned int _period ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void stop( const QString& _threadName ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_IMULTITHREADING_MANAGER_HPP__