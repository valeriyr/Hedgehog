
#ifndef __LM_ISURFACE_ITEMS_CACHE_HPP__
#define __LM_ISURFACE_ITEMS_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItem;

/*---------------------------------------------------------------------------*/

struct ISurfaceItemsCache
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem >
		getSurfaceItem( const unsigned int _index ) const = 0;

	virtual boost::intrusive_ptr< ISurfaceItem > getDefaultSurfaceItem() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void addSurfaceItem(
			const unsigned int _index
		,	boost::intrusive_ptr< ISurfaceItem > _item ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISURFACE_ITEMS_CACHE_HPP__
