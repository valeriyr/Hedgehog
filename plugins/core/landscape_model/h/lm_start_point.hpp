
#ifndef __LM_START_POINT_HPP__
#define __LM_START_POINT_HPP__

/*---------------------------------------------------------------------------*/

#include "generators/gn_igenerator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct StartPoint
{
	StartPoint( const Tools::Core::Generators::IGenerator::IdType _id, const QPoint _point )
		:	m_id( _id )
		,	m_point( _point )
	{}

	const Tools::Core::Generators::IGenerator::IdType m_id;

	const QPoint m_point;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_START_POINT_HPP__
