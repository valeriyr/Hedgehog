
#ifndef __LM_TRAIN_GOAL_HPP__
#define __LM_TRAIN_GOAL_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/ai/ai_goals/lm_igoal.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class TrainGoal
	:	public Tools::Core::BaseWrapper< IGoal >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	TrainGoal();

	~TrainGoal();

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

#endif // __LM_TRAIN_GOAL_HPP__
