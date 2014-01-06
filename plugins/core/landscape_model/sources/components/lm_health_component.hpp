
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

	HealthComponent( Object& _object, const HealthComponentStaticData& _staticData );

	virtual ~HealthComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const HealthComponentStaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const int getHealth() const;

	/*virtual*/ void setHealth( const int _health );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const HealthComponentStaticData& m_staticData;

	int m_health;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_HEALTH_COMPONENT_HPP__
