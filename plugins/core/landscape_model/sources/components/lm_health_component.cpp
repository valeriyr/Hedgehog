
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_health_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


HealthComponent::HealthComponent( Object& _object, const HealthComponentStaticData& _staticData )
	:	BaseComponent< IHealthComponent >( _object )
	,	m_staticData( _staticData )
	,	m_health( _staticData.m_maximumHealth )
{
} // HealthComponent::HealthComponent


/*---------------------------------------------------------------------------*/


HealthComponent::~HealthComponent()
{
} // HealthComponent::~HealthComponent


/*---------------------------------------------------------------------------*/


const HealthComponentStaticData&
HealthComponent::getStaticData() const
{
	return m_staticData;

} // HealthComponent::getStaticData


/*---------------------------------------------------------------------------*/


const int
HealthComponent::getHealth() const
{
	return m_health;

} // HealthComponent::getHealth


/*---------------------------------------------------------------------------*/


void
HealthComponent::setHealth( const int _health )
{
	m_health = _health < 0 ? 0 : _health;

} // HealthComponent::setHealth


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
