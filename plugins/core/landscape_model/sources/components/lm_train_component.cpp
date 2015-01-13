
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_train_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


TrainComponent::TrainComponent(
		GameObject& _object
	,	const ITrainComponent::StaticData& _staticData
	)
	:	BaseComponent< ITrainComponent >( _object )
	,	m_staticData( _staticData )
	,	m_data()
{
} // TrainComponent::TrainComponent


/*---------------------------------------------------------------------------*/


TrainComponent::~TrainComponent()
{
} // TrainComponent::~TrainComponent


/*---------------------------------------------------------------------------*/


const ITrainComponent::StaticData&
TrainComponent::getStaticData() const
{
	return m_staticData;

} // TrainComponent::getStaticData


/*---------------------------------------------------------------------------*/


ITrainComponent::Data&
TrainComponent::getTrainData()
{
	return m_data;

} // TrainComponent::getTrainData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
