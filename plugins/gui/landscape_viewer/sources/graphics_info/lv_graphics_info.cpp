
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/graphics_info/lv_graphics_info.hpp"

#include "landscape_viewer/sources/graphics_info/lv_surface_item_graphics_info.hpp"

#include "iterators/it_simple_iterator.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

const QString IGraphicsInfo::ms_anySkinIdentifier = "Any";

/*---------------------------------------------------------------------------*/

GraphicsInfo::GraphicsInfo()
	:	m_surfaceGraphicsInfoCollection()
	,	m_possiblePlayersColors()
{
} // GraphicsInfo::GraphicsInfo


/*---------------------------------------------------------------------------*/


GraphicsInfo::~GraphicsInfo()
{
} // GraphicsInfo::~GraphicsInfo


/*---------------------------------------------------------------------------*/


void
GraphicsInfo::regSurfaceItemGraphicsInfo(
		const QString& _skinId
	,	const Core::LandscapeModel::ISurfaceItem::Id& _id
	,	const QString& _atlasName
	,	const QRect _frameRect )
{
	SurfaceGraphicsInfoCollectionIterator graphicsInfoIterator = m_surfaceGraphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator == m_surfaceGraphicsInfoCollection.end() )
		graphicsInfoIterator = m_surfaceGraphicsInfoCollection.insert( std::make_pair( _skinId, SurfaceGraphicsInfo() ) ).first;

	assert(	graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.find( _id )
		==	graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.end() );

	graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.insert(
		std::make_pair(
				_id
			,	boost::intrusive_ptr< ISurfaceItemGraphicsInfo >( new SurfaceItemGraphicsInfo( _id, QString( "skins" ) + "/" + _skinId + "/" + _atlasName, _frameRect ) ) ) );

} // GraphicsInfo::regSurfaceItemGraphicsInfo


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
GraphicsInfo::getSurfaceItemGraphicsInfo(
		const QString& _skinId
	,	const Core::LandscapeModel::ISurfaceItem::Id& _id ) const
{
	SurfaceGraphicsInfoCollectionConstIterator graphicsInfoIterator = m_surfaceGraphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator != m_surfaceGraphicsInfoCollection.end() )
	{
		SurfaceGraphicsInfo::SurfaceItemGraphicsInfoCollectionIterator iterator
			= graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.find( _id );

		if ( iterator != graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.end() )
			return iterator->second;
	}

	if ( _skinId != IGraphicsInfo::ms_anySkinIdentifier )
		return getSurfaceItemGraphicsInfo( IGraphicsInfo::ms_anySkinIdentifier, _id );

	return boost::intrusive_ptr< ISurfaceItemGraphicsInfo >();

} // GraphicsInfo::getSurfaceItemGraphicsInfo


/*---------------------------------------------------------------------------*/


void
GraphicsInfo::fetchSurfaceItemGraphicsInfos(
		const QString& _skinId
	,	SurfaceItemGraphicsInfoCollection& _collection ) const
{
	_collection.clear();

	SurfaceGraphicsInfoCollectionConstIterator graphicsInfoIterator = m_surfaceGraphicsInfoCollection.find( _skinId );

	if ( graphicsInfoIterator == m_surfaceGraphicsInfoCollection.end() )
		return;

	SurfaceGraphicsInfo::SurfaceItemGraphicsInfoCollectionIterator
			begin = graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.begin()
		,	end = graphicsInfoIterator->second.m_surfaceItemGraphicsInfos.end();

	for ( ; begin != end; ++begin )
	{
		_collection.push_back( begin->second );
	}

} // GraphicsInfo::fetchSurfaceItemGraphicsInfos


/*---------------------------------------------------------------------------*/


void
GraphicsInfo::regPossiblePlayersColor( const QColor& _color )
{
	m_possiblePlayersColors.push_back( _color );

} // GraphicsInfo::regPossiblePlayersColor


/*---------------------------------------------------------------------------*/


IGraphicsInfo::PossiblePlayersColorIterator
GraphicsInfo::getPossiblePlayersColors() const
{
	return
		IGraphicsInfo::PossiblePlayersColorIterator(
			new Tools::Core::SimpleIterator< PossiblePlayersColorsCollection >( m_possiblePlayersColors ) );

} // GraphicsInfo::getPossiblePlayersColors


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
