
#ifndef __LM_ATTACK_GOAL_HPP__
#define __LM_ATTACK_GOAL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/ai/ai_goals/lm_igoal.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class AttackGoal
	:	public Tools::Core::BaseWrapper< IGoal >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AttackGoal();

	~AttackGoal();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool process();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ATTACK_GOAL_HPP__
