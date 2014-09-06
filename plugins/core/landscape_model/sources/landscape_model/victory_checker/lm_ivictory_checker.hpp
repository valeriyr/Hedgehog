
#ifndef __LM_IVICTORY_CHECKER_HPP__
#define __LM_IVICTORY_CHECKER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/h/lm_victory_condition.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IVictoryChecker
	: public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual bool check() const = 0;

	virtual const VictoryCondition::Enum getType() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IVICTORY_CHECKER_HPP__
