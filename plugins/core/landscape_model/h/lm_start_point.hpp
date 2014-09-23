
#ifndef __LM_START_POINT_HPP__
#define __LM_START_POINT_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct StartPoint
{
	typedef qint32 Id;

	StartPoint( const Id _id, const QPoint _point )
		:	m_id( _id )
		,	m_point( _point )
	{}

	const Id m_id;

	const QPoint m_point;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_START_POINT_HPP__
