
#ifndef __LM_IHEALTH_COMPONENT_HPP__
#define __LM_IHEALTH_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_health_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IHealthComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	virtual const HealthComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const int getHealth() const = 0;

	virtual void setHealth( const int _health ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IHEALTH_COMPONENT_HPP__
