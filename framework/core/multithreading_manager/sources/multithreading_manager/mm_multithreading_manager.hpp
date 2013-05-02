
#ifndef __MM_MULTITHREADING_MANAGER_HPP__
#define __MM_MULTITHREADING_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

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

};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_MULTITHREADING_MANAGER_HPP__
