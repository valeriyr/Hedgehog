
#ifndef __LM_GEOMETRY_HPP__
#define __LM_GEOMETRY_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Geometry {

/*---------------------------------------------------------------------------*/

	extern const int ZeroDistance;

	extern const int NeighborDistance;

	extern const int DiagonalDistance;

/*---------------------------------------------------------------------------*/

	int getDistance( const QPoint& _from, const QPoint& _to );

	QPoint getNearestPoint( const QPoint& _from, const QPoint& _to );

	QPoint getNearestPoint( const QPoint& _from, const QRect& _in );

	bool checkDistance( const QPoint& _from, const QRect& _to, const int _distance );

	bool checkDistance( const QPoint& _from, const QPoint& _to, const int _distance );

/*---------------------------------------------------------------------------*/

} // namespace Geometry
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_GEOMETRY_HPP__
