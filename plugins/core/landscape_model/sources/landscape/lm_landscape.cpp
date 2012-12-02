
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape/lm_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
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


LandscapeItems::Enum
Landscape::getLadscapeItem( const ILandscape::Point& _point ) const
{
	LandscapeItemsCollectionConstIterator iterator
		= m_LandscapeItems.find( _point );

	return
			( iterator != m_LandscapeItems.end() )
		?	iterator->second
		:	LandscapeItems::Grass;

} // Landscape::getLadscapeItem


/*---------------------------------------------------------------------------*/


void
Landscape::setLadscapeItem(
		const ILandscape::Point& _point
	,	const LandscapeItems::Enum _item )
{
	LandscapeItemsCollectionIterator iterator
		= m_LandscapeItems.find( _point );

	if ( iterator != m_LandscapeItems.end() )
		iterator->second = _item;
	else
		m_LandscapeItems.insert( std::make_pair( _point, _item ) );

} // Landscape::setLadscapeItem


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
