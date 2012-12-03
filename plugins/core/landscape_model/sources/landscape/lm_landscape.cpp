
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


ILandscapeItem::Ptr
Landscape::getLadscapeItem( const ILandscape::Point& _point ) const
{
	LandscapeItemsCollectionConstIterator iterator
		= m_LandscapeItems.find( _point );

	return iterator->second;

} // Landscape::getLadscapeItem


/*---------------------------------------------------------------------------*/


void
Landscape::greateGrassItem( const ILandscape::Point& _point )
{
	/*LandscapeItemsCollectionIterator iterator
		= m_LandscapeItems.find( _point );

	if ( iterator != m_LandscapeItems.end() )
		iterator->second = _item;
	else
		m_LandscapeItems.insert( std::make_pair( _point, _item ) );*/

} // Landscape::greateGrassItem


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
