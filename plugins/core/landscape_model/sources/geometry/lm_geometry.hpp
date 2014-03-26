
#ifndef __LM_GEOMETRY_HPP__
#define __LM_GEOMETRY_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Geometry {

/*---------------------------------------------------------------------------*/

	float getDistance( const QPoint& _from, const QPoint& _to );

	QPoint getNearestPoint( const QPoint& _from, const QPoint& _to );

	QPoint getNearestPoint( const QPoint& _from, const QRect& _in );

	bool checkDistance( const QPoint& _from, const QRect& _to, const float _distance );

	bool checkDistance( const QPoint& _from, const QPoint& _to, const float _distance );

/*---------------------------------------------------------------------------*/

} // namespace Geometry
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_GEOMETRY_HPP__
