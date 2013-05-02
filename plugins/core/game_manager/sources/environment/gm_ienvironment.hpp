
#ifndef __GM_IENVIRONMENT_HPP__
#define __GM_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "multithreading_manager/h/mm_runnable_function.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{
	virtual void run( Framework::Core::MultithreadingManager::RunnableFunction _function ) const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_IENVIRONMENT_HPP__
