
#ifndef __LM_DIRECTIONS_HPP__
#define __LM_DIRECTIONS_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct Direction
{
	enum Enum
	{
			North		= 0
		,	NorthEast
		,	East
		,	SouthEast
		,	South
		,	SouthWest
		,	West
		,	NorthWest
	};
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_DIRECTIONS_HPP__
