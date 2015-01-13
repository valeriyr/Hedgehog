
#ifndef __LM_ATTACK_COMPONENT_HPP__
#define __LM_ATTACK_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_iattack_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class AttackComponent
	:	public BaseComponent< IAttackComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AttackComponent( GameObject& _object, const IAttackComponent::StaticData& _staticData );

	virtual ~AttackComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IAttackComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::shared_ptr< GameObject > getTargetObject() const;

	/*virtual*/ void setTargetObject( boost::shared_ptr< GameObject > _object );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IAttackComponent::StaticData& m_staticData;

	boost::shared_ptr< GameObject > m_targetObject;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ATTACK_COMPONENT_HPP__
