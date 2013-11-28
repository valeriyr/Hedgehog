
#ifndef __EM_IENVIRONMENT_HPP__
#define __EM_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual MultithreadingManager::TaskHandle
		pushTask(	const QString& _threadName
				,	const MultithreadingManager::RunnableFunction& _function ) = 0;

	virtual void removeTask( const MultithreadingManager::TaskHandle& _taskHandle ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_IENVIRONMENT_HPP__
