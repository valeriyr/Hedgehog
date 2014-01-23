
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/geometry/lm_geometry.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Geometry {

/*---------------------------------------------------------------------------*/

float getDistance( const QPoint& _from, const QPoint& _to )
{
	QPoint point = _from - _to;
	return sqrt( pow( static_cast< double >( point.x() ), 2 ) + pow( static_cast< double >( point.y() ), 2 ) );
}

/*---------------------------------------------------------------------------*/

QPoint getNearestPoint( const QPoint& _from, const QRect& _in )
{
	QPoint result( _in.x(), _in.y() );
	float distance = getDistance( _from, result );

	for ( int x = _in.x(); x < _in.x() + _in.width(); ++x )
	{
		for ( int y = _in.y(); y < _in.y() + _in.height(); ++y )
		{
			int temp = getDistance( _from, QPoint( x, y ) );

			if ( distance < temp )
			{
				distance = temp;
				result = QPoint( x, y );
			}
		}
	}

	return result;
}

/*---------------------------------------------------------------------------*/

bool checkDistance( const QPoint& _from, const QRect& _to, const float _distance )
{
	return getDistance( _from, getNearestPoint( _from, _to ) ) <= _distance;
}

/*---------------------------------------------------------------------------*/

} // namespace Geometry
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
