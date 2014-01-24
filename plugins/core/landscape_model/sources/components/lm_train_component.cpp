
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_train_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


TrainComponent::TrainComponent(
		Object& _object
	,	const TrainComponentStaticData& _staticData
	)
	:	BaseComponent< ITrainComponent >( _object )
	,	m_staticData( _staticData )
	,	m_trainData()
{
} // TrainComponent::TrainComponent


/*---------------------------------------------------------------------------*/


TrainComponent::~TrainComponent()
{
} // TrainComponent::~TrainComponent


/*---------------------------------------------------------------------------*/


const TrainComponentStaticData&
TrainComponent::getStaticData() const
{
	return m_staticData;

} // TrainComponent::getStaticData


/*---------------------------------------------------------------------------*/


ITrainComponent::TrainData&
TrainComponent::getTrainData()
{
	return m_trainData;

} // TrainComponent::getTrainData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
