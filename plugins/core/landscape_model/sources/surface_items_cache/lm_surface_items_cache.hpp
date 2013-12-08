
#ifndef __LM_SURFACE_ITEMS_CACHE_HPP__
#define __LM_SURFACE_ITEMS_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_isurface_items_cache.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct SurfaceItemsCache
	:	public Tools::Core::BaseWrapper< ISurfaceItemsCache >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SurfaceItemsCache();

	virtual ~SurfaceItemsCache();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regSurfaceItem(
			const ISurfaceItem::IdType _id
		,	const TerrainMapItem::Enum _terrainMapItem );

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem >
		getSurfaceItem( const ISurfaceItem::IdType _id ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< ISurfaceItem > getDefaultSurfaceItem() const;

	/*virtual*/ void setDefaultSurfaceItem( const ISurfaceItem::IdType _id );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< ISurfaceItem::IdType, boost::intrusive_ptr< ISurfaceItem > >
		SurfaceItemsCollection;
	typedef
		SurfaceItemsCollection::const_iterator
		SurfaceItemsCollectionIterator;

/*---------------------------------------------------------------------------*/

	SurfaceItemsCollection m_surfaceItemsCollection;

	boost::intrusive_ptr< ISurfaceItem > m_defaultSurfaceItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SURFACE_ITEMS_CACHE_HPP__
