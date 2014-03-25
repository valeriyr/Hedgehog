
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_move_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


MoveComponent::MoveComponent(
		Object& _object
	,	const IMoveComponent::StaticData& _staticData
	)
	:	BaseComponent< IMoveComponent >( _object )
	,	m_staticData( _staticData )
	,	m_movingData()
{
} // MoveComponent::MoveComponent


/*---------------------------------------------------------------------------*/


MoveComponent::~MoveComponent()
{
} // MoveComponent::~MoveComponent


/*---------------------------------------------------------------------------*/


const IMoveComponent::StaticData&
MoveComponent::getStaticData() const
{
	return m_staticData;

} // MoveComponent::getStaticData


/*---------------------------------------------------------------------------*/


IMoveComponent::MovingData&
MoveComponent::getMovingData()
{
	return m_movingData;

} // MoveComponent::getMovingData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
