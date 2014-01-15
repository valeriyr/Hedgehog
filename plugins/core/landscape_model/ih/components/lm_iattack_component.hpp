
#ifndef __LM_IATTACK_COMPONENT_HPP__
#define __LM_IATTACK_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_icomponent.hpp"
#include "landscape_model/h/components/lm_attack_component_static_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class Object;

/*---------------------------------------------------------------------------*/

struct IAttackComponent
	:	public IComponent
{

/*---------------------------------------------------------------------------*/

	virtual const AttackComponentStaticData& getStaticData() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::shared_ptr< Object > getTargetObject() const = 0;

	virtual void setTargetObject( boost::shared_ptr< Object > _object ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IATTACK_COMPONENT_HPP__
