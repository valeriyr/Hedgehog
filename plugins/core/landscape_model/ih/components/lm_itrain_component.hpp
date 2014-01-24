
#ifndef __LM_ITRAIN_COMPONENT_HPP__
#define __LM_ITRAIN_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_train_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ITrainComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	struct TrainData
	{
		typedef
			std::list< QString >
			TrainObjectsQueue;
		typedef
			TrainObjectsQueue::const_iterator
			TrainObjectsQueueIterator;

		TrainData()
			:	m_trainProgress( 0 )
			,	m_trainQueue()
		{}

		int m_trainProgress;

		TrainObjectsQueue m_trainQueue;
	};

/*---------------------------------------------------------------------------*/

	virtual const TrainComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual TrainData& getTrainData() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ITRAIN_COMPONENT_HPP__
