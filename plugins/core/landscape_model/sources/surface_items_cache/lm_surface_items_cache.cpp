
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/surface_items_cache/lm_surface_items_cache.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SurfaceItemsCache::SurfaceItemsCache()
	:	m_surfaceItemsCollection()
{
} // SurfaceItemsCache::SurfaceItemsCache


SurfaceItemsCache::~SurfaceItemsCache()
{
} // SurfaceItemsCache::~SurfaceItemsCache


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ISurfaceItem >
SurfaceItemsCache::getSurfaceItem( const unsigned int _index ) const
{
	SurfaceItemsCollectionIterator iterator( m_surfaceItemsCollection.find( _index ) );

	if ( iterator != m_surfaceItemsCollection.end() )
		return iterator->second;

	return boost::intrusive_ptr< ISurfaceItem >();

} // SurfaceItemsCache::getSurfaceItem


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ISurfaceItem >
SurfaceItemsCache::getDefaultSurfaceItem() const
{
	return getSurfaceItem( 44 );

} // SurfaceItemsCache::getDefaultSurfaceItem


/*---------------------------------------------------------------------------*/


void
SurfaceItemsCache::addSurfaceItem( const unsigned int _index, boost::intrusive_ptr< ISurfaceItem > _item )
{
	m_surfaceItemsCollection.insert( std::make_pair( _index, _item ) );

} // SurfaceItemsCache::addSurfaceItem


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
