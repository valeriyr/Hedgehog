
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

	AttackComponent( Object& _object, const AttackComponentStaticData& _staticData );

	virtual ~AttackComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const AttackComponentStaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const AttackComponentStaticData& m_staticData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ATTACK_COMPONENT_HPP__
