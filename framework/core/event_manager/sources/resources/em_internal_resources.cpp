
#include "event_manager/sources/ph/em_ph.hpp"

#include "event_manager/sources/resources/em_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const QString ModuleName = "EVENT_MANAGER";

/*---------------------------------------------------------------------------*/

	const Tools::Core::Time::Milliseconds TimeLimit = 16;

	const QString TimeLimitWarning = "Time limit has been exceeded! Time: '%1' ( limit: '%2' )";

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
