
#ifndef __CN_IBASE_HPP__
#define __CN_IBASE_HPP__

/*---------------------------------------------------------------------------*/


struct IBase
{
	virtual void addRef() = 0;

	virtual void releaseRef() = 0;
};


/*---------------------------------------------------------------------------*/


inline
void intrusive_ptr_add_ref( IBase* _base )
{ 
    _base->addRef(); 
} 

inline
void intrusive_ptr_release( IBase* _base )
{ 
    _base->releaseRef(); 
} 


/*---------------------------------------------------------------------------*/

#endif // __CN_IBASE_HPP__
