
#ifndef __LM_IBUILD_COMPONENT_HPP__
#define __LM_IBUILD_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_build_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IBuildComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct BuildData
	{
		typedef
			std::list< std::pair< QString, QPoint > >
			BuildObjectsQueue;
		typedef
			BuildObjectsQueue::const_iterator
			BuildObjectsQueueIterator;

		BuildData()
			:	m_buildProgress( 0 )
			,	m_buildQueue()
		{}

		void clear()
		{
			 m_buildProgress = 0;
			 m_buildQueue.clear();
		}

		int m_buildProgress;

		BuildObjectsQueue m_buildQueue;
	};

/*---------------------------------------------------------------------------*/

	virtual const BuildComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual BuildData& getBuildData() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IBUILD_COMPONENT_HPP__
