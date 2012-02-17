
/** Base interface for all classes witch use intrusive pointer */

#ifndef __CN_IBASE_HPP_
#define __CN_IBASE_HPP_

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


struct IBase
{
	virtual void addRef() = 0;

	virtual void releaseRef() = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/


void intrusive_ptr_add_ref( Common::IBase* _base )
{ 
    _base->addRef(); 
} 


void intrusive_ptr_release( Common::IBase* _base )
{ 
    _base->releaseRef(); 
} 

/*---------------------------------------------------------------------------*/

#endif // __CN_IBASE_HPP_
