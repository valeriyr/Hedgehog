
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_attack_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


AttackComponent::AttackComponent( GameObject& _object, const IAttackComponent::StaticData& _staticData )
	:	BaseComponent< IAttackComponent >( _object )
	,	m_staticData( _staticData )
	,	m_targetObject()
{
} // AttackComponent::AttackComponent


/*---------------------------------------------------------------------------*/


AttackComponent::~AttackComponent()
{
} // AttackComponent::~AttackComponent


/*---------------------------------------------------------------------------*/


const IAttackComponent::StaticData&
AttackComponent::getStaticData() const
{
	return m_staticData;

} // AttackComponent::getStaticData


/*---------------------------------------------------------------------------*/


boost::shared_ptr< GameObject >
AttackComponent::getTargetObject() const
{
	return m_targetObject;

} // AttackComponent::getTargetObject


/*---------------------------------------------------------------------------*/


void
AttackComponent::setTargetObject( boost::shared_ptr< GameObject > _object )
{
	m_targetObject = _object;

} // AttackComponent::setTargetObject


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
