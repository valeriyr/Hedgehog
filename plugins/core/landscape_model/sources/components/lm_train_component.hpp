
#ifndef __LM_TRAIN_COMPONENT_HPP__
#define __LM_TRAIN_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_itrain_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class TrainComponent
	:	public BaseComponent< ITrainComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	TrainComponent( Object& _object, const TrainComponentStaticData& _staticData );

	virtual ~TrainComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const TrainComponentStaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ ITrainComponent::TrainData& getTrainData();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const TrainComponentStaticData& m_staticData;

	ITrainComponent::TrainData m_trainData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_TRAIN_COMPONENT_HPP__
