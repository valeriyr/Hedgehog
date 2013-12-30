
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "landscape_viewer/sources/surface_item_graphics_info/lv_surface_item_graphics_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

const QString GraphicsInfoCache::ms_anySkinIdentifier = "Any";

/*---------------------------------------------------------------------------*/

GraphicsInfoCache::GraphicsInfoCache()
	:	m_graphicsInfoCollection()
{
} // GraphicsInfoCache::GraphicsInfoCache


/*---------------------------------------------------------------------------*/


GraphicsInfoCache::~GraphicsInfoCache()
{
} // GraphicsInfoCache::~GraphicsInfoCache


/*---------------------------------------------------------------------------*/


void
GraphicsInfoCache::regSurfaceItemGraphicsInfo(
		const QString& _skinId
	,	const Core::LandscapeModel::ISurfaceItem::IdType& _id
	,	const QString& _atlasName
	,	const QRect _frameRect )
{
	GraphicsInfoCollectionIterator graphicsInfoIterator = m_graphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator == m_graphicsInfoCollection.end() )
		graphicsInfoIterator = m_graphicsInfoCollection.insert( std::make_pair( _skinId, GraphicsInfo() ) ).first;

	assert(	graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.find( _id )
		==	graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.end() );

	graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.insert(
		std::make_pair(
				_id
			,	boost::intrusive_ptr< ISurfaceItemGraphicsInfo >( new SurfaceItemGraphicsInfo( _id, _atlasName, _frameRect ) ) ) );

} // GraphicsInfoCache::regSurfaceItemGraphicsInfo


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
GraphicsInfoCache::getSurfaceItemGraphicsInfo(
		const QString& _skinId
	,	const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const
{
	GraphicsInfoCollectionConstIterator graphicsInfoIterator = m_graphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator == m_graphicsInfoCollection.end() )
		return boost::intrusive_ptr< ISurfaceItemGraphicsInfo >();

	GraphicsInfo::SurfaceItemGraphicsInfoCollectionIterator iterator
		= graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.find( _id );

	if ( iterator != graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.end() )
		return iterator->second;

	if ( _skinId != ms_anySkinIdentifier )
		return getSurfaceItemGraphicsInfo( ms_anySkinIdentifier, _id );

	return boost::intrusive_ptr< ISurfaceItemGraphicsInfo >();

} // GraphicsInfoCache::getSurfaceItemGraphicsInfo


/*---------------------------------------------------------------------------*/


void
GraphicsInfoCache::fetchSurfaceItemGraphicsInfos(
		const QString& _skinId
	,	SurfaceItemGraphicsInfoCollection& _collection ) const
{
	_collection.clear();

	GraphicsInfoCollectionConstIterator graphicsInfoIterator = m_graphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator == m_graphicsInfoCollection.end() )
		return;

	GraphicsInfo::SurfaceItemGraphicsInfoCollectionIterator
			begin = graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.begin()
		,	end = graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.end();

	for ( ; begin != end; ++begin )
	{
		_collection.push_back( begin->second );
	}

} // GraphicsInfoCache::fetchSurfaceItemGraphicsInfos


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
