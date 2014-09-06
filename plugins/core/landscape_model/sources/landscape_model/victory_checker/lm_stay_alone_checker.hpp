
#ifndef __LM_STAY_ALONE_CHECKER_HPP__
#define __LM_STAY_ALONE_CHECKER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/victory_checker/lm_ivictory_checker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class StayAloneChecker
	:	public Tools::Core::BaseWrapper< IVictoryChecker >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	StayAloneChecker( const IEnvironment& _environment );

	virtual ~StayAloneChecker();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool check() const;

	/*virtual*/ const VictoryCondition::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_STAY_ALONE_CHECKER_HPP__
