
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"

#include "landscape_model/ih/lm_iunit.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Landscape::Landscape( const ISurfaceItemsCache& _surfaceItemsCache )
	:	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_width( 0 )
	,	m_height( 0 )
	,	m_units()
	,	m_surfaceItems( NULL )
	,	m_terrainMap( NULL )
	,	m_selectedUnit()
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


boost::intrusive_ptr< ISurfaceItem >
Landscape::getSurfaceItem( const unsigned int _width, const unsigned int _height ) const
{
	assert( m_surfaceItems );
	assert( _width < m_width );
	assert( _height < m_height );

	return boost::intrusive_ptr< ISurfaceItem >( m_surfaceItems[ _width ][ _height ] );

} // Landscape::getSurfaceItem


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IUnit >
Landscape::getUnit( const unsigned int _width, const unsigned int _height ) const
{
	ILandscape::UnitsMapConstIterator iterator = m_units.find( std::make_pair( _width, _height ) );

	if ( iterator != m_units.end() )
		return iterator->second;

	return boost::intrusive_ptr< IUnit >();

} // Landscape::getUnit


/*---------------------------------------------------------------------------*/


std::pair< unsigned int, unsigned int >
Landscape::getUnitPosition( boost::intrusive_ptr< IUnit > _unit ) const
{
	ILandscape::UnitsMapConstIterator
			begin = m_units.begin()
		,	end = m_units.end();

	for ( ; begin != end; ++begin )
	{
		if ( begin->second == _unit )
			return begin->first;
	}

	return std::pair< unsigned int, unsigned int >();

} // Landscape::getUnitPosition


/*---------------------------------------------------------------------------*/


unsigned int
Landscape::getUnitsCount() const
{
	return m_units.size();

} // Landscape::getUnitsCount


/*---------------------------------------------------------------------------*/


ILandscape::UnitsIteratorPtr
Landscape::getUnitsIterator() const
{
	return ILandscape::UnitsIteratorPtr( new ILandscape::UnitsIterator( m_units ) );

} // Landscape::getUnitsIterator


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IUnit >
Landscape::getSelectedUnit() const
{
	return m_selectedUnit;

} // Landscape::getSelectedUnit


/*---------------------------------------------------------------------------*/


int
Landscape::getTerrainMapValue( const unsigned int _width, const unsigned int _height ) const
{
	assert( m_terrainMap );
	assert( _width < m_width );
	assert( _height < m_height );
	
	return m_terrainMap[ _width ][ _height ];

} // Landscape::getTerrainMapValue


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
			m_surfaceItems[ i ][ j ] = m_surfaceItemsCache.getDefaultSurfaceItem().get();
			m_terrainMap[ i ][ j ] = m_surfaceItemsCache.getDefaultSurfaceItem()->getTerrainMapValue();
		}
	}

} // Landscape::setWidth


/*---------------------------------------------------------------------------*/


void
Landscape::setSurfaceItem(
		const unsigned int _width
	,	const unsigned int _height
	,	boost::intrusive_ptr< ISurfaceItem > _surfaceItem )
{
	assert( m_surfaceItems );
	assert( m_terrainMap );
	assert( _width < m_width );
	assert( _height < m_height );

	m_surfaceItems[ _width ][ _height ] = _surfaceItem.get();
	m_terrainMap[ _width ][ _height ] = _surfaceItem->getTerrainMapValue();

} // Landscape::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
Landscape::setUnit(
		const unsigned int _width
	,	const unsigned int _height
	,	boost::intrusive_ptr< IUnit > _unit )
{
	ILandscape::UnitsMapIterator iterator = m_units.find( std::make_pair( _width, _height ) );

	if ( iterator == m_units.end() )
	{
		m_units.insert( std::make_pair( std::make_pair( _width, _height ), _unit ) );
	}
	else
	{
		iterator->second = _unit;
	}

} // Landscape::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
Landscape::setSelectedUnit( const unsigned int _width, const unsigned int _height )
{
	m_selectedUnit = getUnit( _width, _height );

} // Landscape::setSelectedUnit


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
