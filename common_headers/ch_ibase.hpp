/** Base interface for all classes witch use intrusive pointer */

#ifndef __COMMON_HEADERS_IBASE_HPP_
#define __COMMON_HEADERS_IBASE_HPP_

/*---------------------------------------------------------------------------*/

namespace Common {

/*---------------------------------------------------------------------------*/


struct IBase
{
	virtual void addRef() = 0;

	virtual void releaseRef() = 0;
};


/*---------------------------------------------------------------------------*/


void intrusive_ptr_add_ref( IBase* _base )
{ 
    _base->addRef(); 
} 


void intrusive_ptr_release( IBase* _base )
{ 
    _base->releaseRef(); 
} 


/*---------------------------------------------------------------------------*/

} // namespace Common

/*---------------------------------------------------------------------------*/

#endif // __COMMON_HEADERS_IBASE_HPP_
