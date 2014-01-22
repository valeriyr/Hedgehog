
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

	static Enum getDirection( const QPoint& _location, const QPoint& _target )
	{
		if ( _target.y() > _location.y() && _target.x() > _location.x() )
			return SouthEast;
		else if ( _target.y() < _location.y() && _target.x() > _location.x() )
			return NorthEast;
		else if ( _target.y() > _location.y() && _target.x() < _location.x() )
			return SouthWest;
		else if ( _target.y() < _location.y() && _target.x() < _location.x() )
			return NorthWest;
		else if ( _target.y() > _location.y() )
			return South;
		else if ( _target.y() < _location.y() )
			return North;
		else if ( _target.x() > _location.x() )
			return East;
		else if ( _target.x() < _location.x() )
			return West;

		return South;
	}
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_DIRECTIONS_HPP__
