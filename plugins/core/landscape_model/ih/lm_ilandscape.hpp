
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/ih/lm_ilandscape_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscape
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		boost::intrusive_ptr< ILandscape >
		Ptr;

/*---------------------------------------------------------------------------*/

	struct Point
	{
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

		unsigned int m_widthIndex;
		unsigned int m_heightIndex;
	};

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

/*---------------------------------------------------------------------------*/

	virtual ILandscapeItem::Ptr getLadscapeItem( const Point& _point ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
