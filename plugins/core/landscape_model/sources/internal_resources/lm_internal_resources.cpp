
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const char* const ModuleName = "LANDSCAPE_MODEL";

/*---------------------------------------------------------------------------*/

	const float LandscapeVersion = 1.0f;

/*---------------------------------------------------------------------------*/

	const int TimeLimit = 100;

	const char* const TimeLimitWarning = "Time limit has been exceeded! Time: '%1' ( limit: '%2' )";

/*---------------------------------------------------------------------------*/

	const char* const ConfigurationScriptsDirectory = "landscape_model";

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
