
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/victory_checker/lm_stay_alone_checker.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


StayAloneChecker::StayAloneChecker()
{
} // StayAloneChecker::StayAloneChecker


/*---------------------------------------------------------------------------*/


StayAloneChecker::~StayAloneChecker()
{
} // StayAloneChecker::~StayAloneChecker


/*---------------------------------------------------------------------------*/


bool
StayAloneChecker::check() const
{
	return false;

} // StayAloneChecker::check


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
