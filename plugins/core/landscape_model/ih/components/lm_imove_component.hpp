
#ifndef __LM_IMOVE_COMPONENT_HPP__
#define __LM_IMOVE_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"

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
		StaticData( const int _movingSpeed )
			:	m_movingSpeed( _movingSpeed )
		{}

		const int m_movingSpeed;
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
			m_movingProgress = 0.0f;
			m_movingTo = QPoint( 0, 0 );
			m_movingToObject.reset();
		}

		IPathFinder::PointsCollection m_path;
		float m_movingProgress;
		QPoint m_movingTo;
		boost::shared_ptr< Object > m_movingToObject;
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
