
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/utils/lm_math.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Math {

/*---------------------------------------------------------------------------*/

int calculatePart( const int _maxValue, const int _part, const int _maxPart )
{
	return ( ( ( _maxValue  * _maxPart ) * _part ) / _maxPart ) / _maxPart;
}

/*---------------------------------------------------------------------------*/

int calculatePercent( const int _value, const int _maxValue )
{
	return _value * 100 / _maxValue;
}

/*---------------------------------------------------------------------------*/

} // namespace Geometry
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
