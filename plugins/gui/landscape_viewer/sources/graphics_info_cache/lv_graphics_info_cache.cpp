
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "landscape_viewer/sources/surface_item_graphics_info/lv_surface_item_graphics_info.hpp"
#include "landscape_viewer/sources/object_graphics_info/lv_object_graphics_info.hpp"

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


void
GraphicsInfoCache::regObjectGraphicsInfo(
		const QString& _skinId
	,	const QString& _objectName
	,	const QString& _atlasName
	,	const QRect _frameRect )
{
	GraphicsInfoCollectionIterator graphicsInfoIterator = m_graphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator == m_graphicsInfoCollection.end() )
		graphicsInfoIterator = m_graphicsInfoCollection.insert( std::make_pair( _skinId, GraphicsInfo() ) ).first;

	assert(	graphicsInfoIterator->second.m_objectGraphicsInfo.find( _objectName )
		==	graphicsInfoIterator->second.m_objectGraphicsInfo.end() );

	graphicsInfoIterator->second.m_objectGraphicsInfo.insert(
		std::make_pair(
				_objectName
			,	boost::intrusive_ptr< IObjectGraphicsInfo >( new ObjectGraphicsInfo( _objectName, _atlasName, _frameRect ) ) ) );

} // GraphicsInfoCache::regObjectGraphicsInfo


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


boost::intrusive_ptr< IObjectGraphicsInfo >
GraphicsInfoCache::getObjectGraphicsInfo(
		const QString& _skinId
	,	const QString& _objectName ) const
{
	GraphicsInfoCollectionConstIterator graphicsInfoIterator = m_graphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator == m_graphicsInfoCollection.end() )
		return boost::intrusive_ptr< IObjectGraphicsInfo >();

	GraphicsInfo::ObjectGraphicsInfoCollectionIterator iterator
		= graphicsInfoIterator->second.m_objectGraphicsInfo.find( _objectName );

	if ( iterator != graphicsInfoIterator->second.m_objectGraphicsInfo.end() )
		return iterator->second;

	if ( _skinId != ms_anySkinIdentifier )
		return getObjectGraphicsInfo( ms_anySkinIdentifier, _objectName );

	return boost::intrusive_ptr< IObjectGraphicsInfo >();

} // GraphicsInfoCache::getObjectGraphicsInfo


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


void
GraphicsInfoCache::fetchObjectsGraphicsInfos(
		const QString& _skinId
	,	ObjectGraphicsInfoCollection& _collection ) const
{
	_collection.clear();

	GraphicsInfoCollectionConstIterator graphicsInfoIterator = m_graphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator == m_graphicsInfoCollection.end() )
		return;

	GraphicsInfo::ObjectGraphicsInfoCollectionIterator
			begin = graphicsInfoIterator->second.m_objectGraphicsInfo.begin()
		,	end = graphicsInfoIterator->second.m_objectGraphicsInfo.end();

	for ( ; begin != end; ++begin )
	{
		_collection.push_back( begin->second );
	}

} // GraphicsInfoCache::fetchObjectsGraphicsInfos


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
