
#ifndef __LM_POINT_HPP__
#define __LM_POINT_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct Point
{

/*---------------------------------------------------------------------------*/

	Point( unsigned int _x = 0, unsigned int _y = 0 )
		:	m_x( _x )
		,	m_y( _y )
	{}

	Point( const Point& _point )
	{
		*this = _point;
	}

/*---------------------------------------------------------------------------*/

	Point& operator = ( const Point& _point )
	{
		m_x = _point.m_x;
		m_y = _point.m_y;

		return *this;
	}

/*---------------------------------------------------------------------------*/

	bool operator == ( const Point& _point ) const
	{
		return m_x == _point.m_x && m_y == _point.m_y;
	}

	bool operator < ( const Point& _point ) const
	{
		return m_x < _point.m_x || m_y < _point.m_y;
	}

/*---------------------------------------------------------------------------*/

	unsigned int m_x;

	unsigned int m_y;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_POINT_HPP__