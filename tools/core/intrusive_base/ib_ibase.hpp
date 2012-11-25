
#ifndef __IB_IBASE_HPP__
#define __IB_IBASE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_base.hpp"

/*---------------------------------------------------------------------------*/

namespace Tools {
namespace Core {

/*---------------------------------------------------------------------------*/

struct IBase
{
	virtual void addRef() = 0;

	virtual void releaseRef() = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Core
} // namespace Tools

/*---------------------------------------------------------------------------*/

inline
void intrusive_ptr_add_ref( Tools::Core::IBase* _base )
{ 
    _base->addRef(); 
} 

inline
void intrusive_ptr_release( Tools::Core::IBase* _base )
{ 
    _base->releaseRef(); 
} 

/*---------------------------------------------------------------------------*/

#endif // __IB_IBASE_HPP__
