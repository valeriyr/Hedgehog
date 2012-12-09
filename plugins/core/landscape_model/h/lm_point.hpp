
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

	Point(
			const unsigned int _widthIndex
		,	const unsigned int _heightIndex
		)
		:	m_widthIndex( _widthIndex )
		,	m_heightIndex( _heightIndex )
	{}

	Point( const Point& _point )
	{
		*this = _point;
	}

/*---------------------------------------------------------------------------*/

	Point& operator = ( const Point& _point )
	{
		m_widthIndex = _point.m_widthIndex;
		m_heightIndex = _point.m_heightIndex;

		return *this;
	}

	bool operator < ( const Point& _point ) const
	{
		return
				m_widthIndex < _point.m_widthIndex
			&&	m_heightIndex < _point.m_heightIndex;
	}

/*---------------------------------------------------------------------------*/

	unsigned int m_widthIndex;
	unsigned int m_heightIndex;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_POINT_HPP__
