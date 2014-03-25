
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_health_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


HealthComponent::HealthComponent( Object& _object, const IHealthComponent::StaticData& _staticData )
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


const IHealthComponent::StaticData&
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
	if ( _health < 0 )
		m_health = 0;
	else if ( _health > m_staticData.m_maximumHealth )
		m_health = m_staticData.m_maximumHealth;
	else
		m_health = _health;

} // HealthComponent::setHealth


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
