
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/surface_items_cache/lm_surface_items_cache.hpp"

#include "landscape_model/sources/surface_item/lm_surface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SurfaceItemsCache::SurfaceItemsCache()
	:	m_surfaceItemsCollection()
	,	m_defaultSurfaceItem()
{
} // SurfaceItemsCache::SurfaceItemsCache


/*---------------------------------------------------------------------------*/


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
	if ( m_defaultSurfaceItem )
	{
		return m_defaultSurfaceItem;
	}

	if ( !m_surfaceItemsCollection.empty() )
	{
		return m_surfaceItemsCollection.begin()->second;
	}

	return boost::intrusive_ptr< ISurfaceItem >();

} // SurfaceItemsCache::getDefaultSurfaceItem


/*---------------------------------------------------------------------------*/


void
SurfaceItemsCache::addSurfaceItem(
		const unsigned int _index
	,	const QString& _bundlePath
	,	const QRect& _rectInBundle
	)
{
	m_surfaceItemsCollection.insert(
		std::make_pair(
				_index
			,	boost::intrusive_ptr< ISurfaceItem >( new SurfaceItem( _index, _bundlePath, _rectInBundle ) ) ) );

} // SurfaceItemsCache::addSurfaceItem


/*---------------------------------------------------------------------------*/


void
SurfaceItemsCache::setDefaultSurfaceItem( boost::intrusive_ptr< ISurfaceItem > _item )
{
	m_defaultSurfaceItem = _item;

} // SurfaceItemsCache::setDefaultSurfaceItem


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
