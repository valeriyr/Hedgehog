
#ifndef __XL_IELEMENT_HPP__
#define __XL_IELEMENT_HPP__

#include "allocators/al_block_allocator.hpp"


/*---------------------------------------------------------------------------*/

namespace Tools {
namespace XmlLibrary {

/*---------------------------------------------------------------------------*/

struct IVisitor;

/*---------------------------------------------------------------------------*/

struct IElement
	:	public BlockAllocator<>
{
	virtual void accept ( IVisitor& _visitor ) const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace XmlLibrary
} // namespace Tools

/*---------------------------------------------------------------------------*/

#endif // __XL_IELEMENT_HPP__
