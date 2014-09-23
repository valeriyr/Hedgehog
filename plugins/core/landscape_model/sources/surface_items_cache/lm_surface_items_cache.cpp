
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


void
SurfaceItemsCache::regSurfaceItem(
		const Tools::Core::Generators::IGenerator::IdType _id
	,	const TerrainMapItem::Enum _terrainMapItem )
{
	m_surfaceItemsCollection.insert(
		std::make_pair(
				_id
			,	boost::intrusive_ptr< ISurfaceItem >( new SurfaceItem( _id, _terrainMapItem ) ) ) );

} // SurfaceItemsCache::regSurfaceItem


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ISurfaceItem >
SurfaceItemsCache::getSurfaceItem( const Tools::Core::Generators::IGenerator::IdType _id ) const
{
	SurfaceItemsCollectionIterator iterator( m_surfaceItemsCollection.find( _id ) );

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
SurfaceItemsCache::setDefaultSurfaceItem( const Tools::Core::Generators::IGenerator::IdType _id )
{
	SurfaceItemsCollectionIterator iterator( m_surfaceItemsCollection.find( _id ) );

	if ( iterator != m_surfaceItemsCollection.end() )
		m_defaultSurfaceItem = iterator->second;

} // SurfaceItemsCache::setDefaultSurfaceItem


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
