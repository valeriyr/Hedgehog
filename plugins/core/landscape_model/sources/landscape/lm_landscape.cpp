
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/sources/landscape_objects/lm_tree_object.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Landscape::Landscape()
	:	m_width( 0 )
	,	m_height( 0 )
	,	m_surfaceItems( NULL )
	,	m_terrainMap( NULL )
{
} // Landscape::Landscape


/*---------------------------------------------------------------------------*/


Landscape::~Landscape()
{
	clearCollection( m_surfaceItems );
	clearCollection( m_terrainMap );

} // Landscape::~Landscape


/*---------------------------------------------------------------------------*/


unsigned int
Landscape::getWidth() const
{
	return m_width;

} // Landscape::getWidth


/*---------------------------------------------------------------------------*/


unsigned int
Landscape::getHeight() const
{
	return m_height;

} // Landscape::getHeight


/*---------------------------------------------------------------------------*/


ILandscapeObject::Ptr
Landscape::getLadscapeObject( const unsigned int _width, const unsigned int _height ) const
{
	return ILandscapeObject::Ptr();

} // Landscape::getLadscapeObject


/*---------------------------------------------------------------------------*/


SurfaceItems::Enum
Landscape::getSurfaceItem( const unsigned int _width, const unsigned int _height ) const
{
	assert( m_surfaceItems );
	assert( _width < m_width );
	assert( _height < m_height );

	return m_surfaceItems[ _width ][ _height ];

} // Landscape::getSurfaceItem


/*---------------------------------------------------------------------------*/


TerrainMapItems::Enum
Landscape::getTerrainMapItem( const unsigned int _width, const unsigned int _height ) const
{
	assert( m_terrainMap );
	assert( _width < m_width );
	assert( _height < m_height );

	return m_terrainMap[ _width ][ _height ];

} // Landscape::getTerrainMapItem


/*---------------------------------------------------------------------------*/


void
Landscape::setSize( const unsigned int _width, const unsigned int _height )
{
	assert( _width > 0 );
	assert( _height > 0 );

	m_width = _width;
	m_height = _height;

	initCollection( m_surfaceItems );
	initCollection( m_terrainMap );

	for ( unsigned int i = 0; i < m_width; ++i )
	{
		for ( unsigned int j = 0; j < m_height; ++j )
		{
			SurfaceItems::Enum defaultSurfaceItem = SurfaceItems::Grass;

			m_surfaceItems[ i ][ j ] = defaultSurfaceItem;
			m_terrainMap[ i ][ j ]
				= TerrainMapItems::fromSurfaceItem( defaultSurfaceItem );
		}
	}

} // Landscape::setWidth


/*---------------------------------------------------------------------------*/


void
Landscape::setSurfaceItem(
		const unsigned int _width
	,	const unsigned int _height
	,	const SurfaceItems::Enum _surfaceItem )
{
	assert( m_surfaceItems );
	assert( m_terrainMap );
	assert( _width < m_width );
	assert( _height < m_height );

	m_surfaceItems[ _width ][ _height ] = _surfaceItem;
	m_terrainMap[ _width ][ _height ] = TerrainMapItems::fromSurfaceItem( _surfaceItem );

} // Landscape::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
Landscape::createTreeObject( const unsigned int _width, const unsigned int _height )
{
} // Landscape::createTreeObject


/*---------------------------------------------------------------------------*/


template< typename _TCollectionItem >
void
Landscape::initCollection( _TCollectionItem**& _collection )
{
	assert( !_collection );

	_collection = new _TCollectionItem*[ m_width ];
	for ( unsigned int i = 0; i < m_width; ++i )
		_collection[ i ] = new _TCollectionItem[ m_height ];

} // Landscape::initCollection


/*---------------------------------------------------------------------------*/


template< typename _TCollection >
void
Landscape::clearCollection( _TCollection& _collection )
{
	if ( _collection )
	{
		for ( unsigned int i = 0; i < m_width; ++i )
			delete _collection[ i ];
		delete [] _collection;

		_collection = NULL;
	}

} // Landscape::clearCollection


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
