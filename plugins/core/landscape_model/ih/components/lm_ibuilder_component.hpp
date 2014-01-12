
#ifndef __LM_IBUILDER_COMPONENT_HPP__
#define __LM_IBUILDER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_builder_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IBuilderComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct BuildData
	{
		typedef
			std::list< QString >
			BuildObjectsQueue;
		typedef
			BuildObjectsQueue::const_iterator
			BuildObjectsQueueIterator;

		BuildData()
			:	m_buildProgress( 0 )
			,	m_buildQueue()
		{}

		int m_buildProgress;

		BuildObjectsQueue m_buildQueue;
	};

/*---------------------------------------------------------------------------*/

	virtual const BuilderComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual BuildData& getBuildData() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IBUILDER_COMPONENT_HPP__
