
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


Landscape::Landscape( const unsigned int _width, const unsigned int _height )
	:	m_width( _width )
	,	m_height( _height )
	,	m_LandscapeItems()
{
} // Landscape::Landscape


/*---------------------------------------------------------------------------*/


Landscape::~Landscape()
{
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
	LandscapeItemsCollectionConstIterator iterator
		= m_LandscapeItems.find( _point );

	return iterator->second;

} // Landscape::getLadscapeObject


/*---------------------------------------------------------------------------*/


SurfaceItems::Enum
Landscape::getSurfaceItem( const Point& _point ) const
{
	return SurfaceItems::Grass;

} // Landscape::getSurfaceItem


/*---------------------------------------------------------------------------*/


void
Landscape::setSurfaceItem(
		const Point& _point
	,	const SurfaceItems::Enum& _surfaceItem )
{
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
