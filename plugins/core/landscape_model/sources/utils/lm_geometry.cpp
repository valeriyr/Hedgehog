
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Geometry {

/*---------------------------------------------------------------------------*/

const int ZeroDistance = 0;

const int NeighborDistance = 10;

const int DiagonalDistance = 15;

/*---------------------------------------------------------------------------*/

int getDistance( const QPoint& _from, const QPoint& _to )
{
	QPoint point = _from - _to;
	return sqrt( static_cast< float >( point.x() * point.x() + point.y() * point.y() ) ) * NeighborDistance;
}

/*---------------------------------------------------------------------------*/

QPoint getNearestPoint( const QPoint& _from, const QPoint& _to )
{
	return getNearestPoint( _from, QRect( _to, QSize( 1, 1 ) ) );
}

/*---------------------------------------------------------------------------*/

QPoint getNearestPoint( const QPoint& _from, const QRect& _in )
{
	QPoint result( _in.x(), _in.y() );
	int distance = INT_MAX;

	for ( int x = _in.x(); x < _in.x() + _in.width(); ++x )
	{
		for ( int y = _in.y(); y < _in.y() + _in.height(); ++y )
		{
			int temp = getDistance( _from, QPoint( x, y ) );

			if ( temp < distance )
			{
				distance = temp;
				result = QPoint( x, y );
			}
		}
	}

	return result;
}

/*---------------------------------------------------------------------------*/

bool checkDistance( const QPoint& _from, const QRect& _to, const int _distance )
{
	return getDistance( _from, getNearestPoint( _from, _to ) ) <= _distance;
}

/*---------------------------------------------------------------------------*/

bool checkDistance( const QPoint& _from, const QPoint& _to, const int _distance )
{
	return getDistance( _from, getNearestPoint( _from, _to ) ) <= _distance;
}

/*---------------------------------------------------------------------------*/

} // namespace Geometry
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
