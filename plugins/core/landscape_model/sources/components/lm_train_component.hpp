
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

	TrainComponent( GameObject& _object, const ITrainComponent::StaticData& _staticData );

	virtual ~TrainComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const ITrainComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ ITrainComponent::Data& getTrainData();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ITrainComponent::StaticData& m_staticData;

	ITrainComponent::Data m_data;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_TRAIN_COMPONENT_HPP__
