
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Landscape::Landscape( const ISurfaceItemsCache& _surfaceItemsCache )
	:	m_surfaceItemsCache( _surfaceItemsCache )
	,	m_width( 0 )
	,	m_height( 0 )
	,	m_surfaceItems( NULL )
{
} // Landscape::Landscape


/*---------------------------------------------------------------------------*/


Landscape::~Landscape()
{
	clearCollection( m_surfaceItems );

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


void
Landscape::setSize( const unsigned int _width, const unsigned int _height )
{
	assert( _width > 0 );
	assert( _height > 0 );

	m_width = _width;
	m_height = _height;

	initCollection( m_surfaceItems );

	for ( unsigned int i = 0; i < m_width; ++i )
	{
		for ( unsigned int j = 0; j < m_height; ++j )
		{
			m_surfaceItems[ i ][ j ] = m_surfaceItemsCache.getDefaultSurfaceItem().get();
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
	assert( _width < m_width );
	assert( _height < m_height );

	m_surfaceItems[ _width ][ _height ] = _surfaceItem.get();

} // Landscape::setSurfaceItem


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
