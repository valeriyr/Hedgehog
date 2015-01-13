
#ifndef __LM_HEALTH_COMPONENT_HPP__
#define __LM_HEALTH_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_ihealth_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class HealthComponent
	:	public BaseComponent< IHealthComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	HealthComponent( GameObject& _object, const IHealthComponent::StaticData& _staticData );

	virtual ~HealthComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IHealthComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const int getHealth() const;

	/*virtual*/ void setHealth( const int _health );

	/*virtual*/ bool isHealthy() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IHealthComponent::StaticData& m_staticData;

	int m_health;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_HEALTH_COMPONENT_HPP__
