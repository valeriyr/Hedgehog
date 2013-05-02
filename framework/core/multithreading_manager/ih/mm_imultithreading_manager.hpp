
#ifndef __MM_IMULTITHREADING_MANAGER_HPP__
#define __MM_IMULTITHREADING_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

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
};

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __MM_IMULTITHREADING_MANAGER_HPP__
