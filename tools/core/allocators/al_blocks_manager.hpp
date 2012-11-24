
#ifndef __AL_BLOCKS_MANAGER_HPP__
#define __AL_BLOCKS_MANAGER_HPP__

#include <memory>


/*---------------------------------------------------------------------------*/

namespace Tools {

/*---------------------------------------------------------------------------*/

template< size_t _BlockSize >
class BlocksManager
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	static const size_t ms_blockSize = _BlockSize;

/*---------------------------------------------------------------------------*/

	static BlocksManager< _BlockSize >& instance();

/*---------------------------------------------------------------------------*/

	void* allocate( size_t _size );

	void free( void* _object, size_t _size );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	BlocksManager();

	BlocksManager( const BlocksManager& );

	BlocksManager& operator= ( const BlocksManager& );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/


template< size_t _BlockSize >
BlocksManager< _BlockSize >::BlocksManager()
{
} // BlocksManager< _BlockSize >::BlocksManager()


/*---------------------------------------------------------------------------*/


template< size_t _BlockSize >
BlocksManager< _BlockSize >&
BlocksManager< _BlockSize >::instance()
{
	static std::auto_ptr< BlocksManager< _BlockSize > > blocksManager;

	if ( !blocksManager.get() )
		blocksManager.reset( new BlocksManager< _BlockSize >() ); 

	return *blocksManager;

} // BlocksManager< _BlockSize >::instance()


/*---------------------------------------------------------------------------*/


template< size_t _BlockSize >
void*
BlocksManager< _BlockSize >::allocate( size_t _size )
{
	return NULL;

} // BlocksManager< _BlockSize >allocate()


/*---------------------------------------------------------------------------*/


template< size_t _BlockSize >
void
BlocksManager< _BlockSize >::free( void* _object, size_t _size )
{
} // BlocksManager< _BlockSize >::free


/*---------------------------------------------------------------------------*/

} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __AL_BLOCKS_MANAGER_HPP__
