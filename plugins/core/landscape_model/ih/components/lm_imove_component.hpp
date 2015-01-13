
#ifndef __LM_IMOVE_COMPONENT_HPP__
#define __LM_IMOVE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

#include "landscape_model/h/lm_constants.hpp"

#include "landscape_model/sources/path_finders/lm_ipath_finder.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IMoveComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct StaticData
	{
		StaticData( const TickType _movingSpeed )
			:	m_movingSpeed( _movingSpeed )
		{}

		const TickType m_movingSpeed;
	};

/*---------------------------------------------------------------------------*/

	struct MovingData
	{
		MovingData()
			:	m_path()
			,	m_movingProgress( 0.0 )
			,	m_movingTo( 0, 0 )
			,	m_movingToObject()
		{}

		void reset()
		{
			m_path.clear();
			m_movingProgress = 0;
			m_movingTo = QPoint( 0, 0 );
			m_movingToObject.reset();
		}

		void leaveOnlyFirstPoint()
		{
			if ( !m_path.empty() )
			{
				QPoint inProgressPoint( m_path.front() );
				m_path.clear();
				m_path.push_back( inProgressPoint );
			}
		}

		IPathFinder::PointsCollection m_path;
		TickType m_movingProgress;
		QPoint m_movingTo;
		boost::shared_ptr< GameObject > m_movingToObject;
	};

/*---------------------------------------------------------------------------*/

	virtual const StaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual MovingData& getMovingData() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IMOVE_COMPONENT_HPP__
