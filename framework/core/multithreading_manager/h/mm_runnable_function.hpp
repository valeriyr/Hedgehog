
#ifndef __MM_RUNNABLE_FUNCTION_HPP__
#define __MM_RUNNABLE_FUNCTION_HPP__


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/

	typedef
		boost::function< void () >
		RunnableFunction;

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_RUNNABLE_FUNCTION_HPP__
