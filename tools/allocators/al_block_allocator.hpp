
#ifndef __AL_BLOCK_ALLOCATOR_HPP__
#define __AL_BLOCK_ALLOCATOR_HPP__

#include "allocators/al_blocks_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {

/*---------------------------------------------------------------------------*/

struct EmptyClass
{
};

/*---------------------------------------------------------------------------*/

template<
		typename _TBaseClass = EmptyClass
	,	size_t _BlockSize = 65536
	>
struct BlockAllocator
	:	public _TBaseClass
{

/*---------------------------------------------------------------------------*/

	virtual ~BlockAllocator() {}

/*---------------------------------------------------------------------------*/

	static void* operator new ( size_t _size );

	static void	operator delete ( void* _object, size_t _size );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/


template< typename _TBaseClass, size_t _BlockSize >
void*
BlockAllocator< _TBaseClass, _BlockSize >::operator new ( size_t _size )
{
	// if ( _size > _BlockSize )
		return ::operator new( _size );

	// return BlocksManager< _BlockSize >::instance().allocate( _size );

} // BlockAllocator< _TBaseClass, _BlockSize >::operator new


/*---------------------------------------------------------------------------*/


template< typename _TBaseClass, size_t _BlockSize >
void
BlockAllocator< _TBaseClass, _BlockSize >::operator delete ( void* _object, size_t _size )
{
	//if ( _size > _BlockSize )
		::operator delete( _object );
	/*else
		BlocksManager< _BlockSize >::instance().free( _object, _size );*/

} // BlockAllocator< _TBaseClass, _BlockSize >::operator new


/*---------------------------------------------------------------------------*/

} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __AL_BLOCK_ALLOCATOR_HPP__
