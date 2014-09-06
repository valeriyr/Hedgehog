
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/victory_checker/lm_endless_checker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


EndlessChecker::EndlessChecker()
{
} // EndlessChecker::EndlessChecker


/*---------------------------------------------------------------------------*/


EndlessChecker::~EndlessChecker()
{
} // EndlessChecker::~EndlessChecker


/*---------------------------------------------------------------------------*/


bool
EndlessChecker::check() const
{
	return false;

} // EndlessChecker::check


/*---------------------------------------------------------------------------*/


const VictoryCondition::Enum
EndlessChecker::getType() const
{
	return VictoryCondition::Endless;

} // EndlessChecker::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
