
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
Landscape::getLadscapeItem(
		const unsigned int _widht
	,	const unsigned int _height ) const
{
	return LandscapeItems::Grass;

} // Landscape::getLadscapeItem


/*---------------------------------------------------------------------------*/


void
Landscape::setLadscapeItem(
		const unsigned int _widht
	,	const unsigned int _height
	,	const LandscapeItems::Enum _Item )
{
} // Landscape::setLadscapeItem


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
