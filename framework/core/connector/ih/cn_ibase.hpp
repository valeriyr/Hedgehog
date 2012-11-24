
#ifndef __CN_IBASE_HPP__
#define __CN_IBASE_HPP__

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


inline
void intrusive_ptr_add_ref( Framework::Connector::IBase* _base )
{ 
    _base->addRef(); 
} 

inline
void intrusive_ptr_release( Framework::Connector::IBase* _base )
{ 
    _base->releaseRef(); 
} 


/*---------------------------------------------------------------------------*/

#endif // __CN_IBASE_HPP__
