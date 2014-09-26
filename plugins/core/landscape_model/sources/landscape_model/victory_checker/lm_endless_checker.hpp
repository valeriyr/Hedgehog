
#ifndef __LM_ENDLESS_CHECKER_HPP__
#define __LM_ENDLESS_CHECKER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/victory_checker/lm_ivictory_checker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModel;

/*---------------------------------------------------------------------------*/

class EndlessChecker
	:	public Tools::Core::BaseWrapper< IVictoryChecker >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	EndlessChecker( const ILandscapeModel& _landscapeModel );

	virtual ~EndlessChecker();

/*---------------------------------------------------------------------------*/

	/*virtual*/ bool check() const;

	/*virtual*/ const VictoryCondition::Enum getType() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeModel& m_landscapeModel;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ENDLESS_CHECKER_HPP__
