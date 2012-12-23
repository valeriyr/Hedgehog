
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
	,	m_surfaceData( NULL )
{
} // Landscape::Landscape


/*---------------------------------------------------------------------------*/


Landscape::~Landscape()
{
	if ( m_surfaceData )
	{
		for ( unsigned int i = 0; i < m_width; ++i )
			delete m_surfaceData[ i ];
		delete [] m_surfaceData;

		m_surfaceData = NULL;
	}

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
Landscape::getLadscapeObject( const Point& _point ) const
{
	return ILandscapeObject::Ptr();

} // Landscape::getLadscapeObject


/*---------------------------------------------------------------------------*/


SurfaceItems::Enum
Landscape::getSurfaceItem( const Point& _point ) const
{
	assert( m_surfaceData );
	assert( _point.m_widthIndex < m_width );
	assert( _point.m_heightIndex < m_height );

	return m_surfaceData[ _point.m_widthIndex][ _point.m_heightIndex ];

} // Landscape::getSurfaceItem


/*---------------------------------------------------------------------------*/


void
Landscape::setSize(
		const unsigned int _width
	,	const unsigned int _height )
{
	assert( _width > 0 );
	assert( _height > 0 );

	m_width = _width;
	m_height = _height;

	m_surfaceData = new SurfaceItems::Enum*[ m_width ];
	for ( unsigned int i = 0; i < m_width; ++i )
		m_surfaceData[ i ] = new SurfaceItems::Enum[ m_height ];

	for ( unsigned int i = 0; i < m_width; ++i )
		for ( unsigned int j = 0; j < m_height; ++j )
			m_surfaceData[ i ][ j ] = SurfaceItems::Grass;

} // Landscape::setWidth


/*---------------------------------------------------------------------------*/


void
Landscape::setSurfaceItem(
		const Point& _point
	,	const SurfaceItems::Enum _surfaceItem )
{
	assert( m_surfaceData );
	assert( _point.m_widthIndex < m_width );
	assert( _point.m_heightIndex < m_height );

	m_surfaceData[ _point.m_widthIndex][ _point.m_heightIndex ] = _surfaceItem;

} // Landscape::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
Landscape::createTreeObject( const Point& _point )
{
} // Landscape::createTreeObject


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
