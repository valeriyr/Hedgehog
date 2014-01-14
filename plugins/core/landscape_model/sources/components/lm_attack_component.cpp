
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_attack_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


AttackComponent::AttackComponent( Object& _object, const AttackComponentStaticData& _staticData )
	:	BaseComponent< IAttackComponent >( _object )
	,	m_staticData( _staticData )
{
} // AttackComponent::AttackComponent


/*---------------------------------------------------------------------------*/


AttackComponent::~AttackComponent()
{
} // AttackComponent::~AttackComponent


/*---------------------------------------------------------------------------*/


const AttackComponentStaticData&
AttackComponent::getStaticData() const
{
	return m_staticData;

} // AttackComponent::getStaticData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
