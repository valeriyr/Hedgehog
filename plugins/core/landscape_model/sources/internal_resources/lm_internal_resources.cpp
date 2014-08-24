
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

	const char* const LandscapeVersion = "1.0.0";

/*---------------------------------------------------------------------------*/

	const char* const LandscapesDirectoryName = "maps";

/*---------------------------------------------------------------------------*/

	const int TimeLimit = 100;

	const char* const TimeLimitWarning = "Time limit has been exceeded! Time: '%1' ( limit: '%2' )";

	const char* const SimulationHasBeenStartedMessage = "Simulation has been started at: '%1' msec";

	const char* const SimulationHasBeenStoppedMessage = "Simulation has been stopped at: '%1' msec";

	const char* const SocketHasBeenOpenedMessage = "Socket has been opened at: '%1:%2'";

	const char* const SocketHasBeenClosedMessage = "Socket has been closed at: '%1:%2'";

	const char* const CommandReceivedMessage = "Command has been received from '%1:%2', type '%3', data '%4'";

/*---------------------------------------------------------------------------*/

	const char* const ConfigurationScriptsDirectory = "landscape_model";

/*---------------------------------------------------------------------------*/

	const char* const DocTypeString = "<!DOCTYPE hmap>";

	const char* const HMapTagName = "hmap";

	const char* const VersionAttributeName = "version";

	const char* const WidthAttributeName = "width";
	const char* const HeightAttributeName = "height";

	const char* const StartPointsTagName = "start_points";
	const char* const StartPointTagName = "start_point";

	const char* const SurfaceTagName = "surface";

	const char* const ObjectsTagName = "objects";
	const char* const ObjectTagName = "object";

	const char* const CountAttributeName = "count";

	const char* const NameAttributeName = "name";

	const char* const LocationTagName = "location";

	const char* const XAttributeName = "x";
	const char* const YAttributeName = "y";

	const char* const IdAttributeName = "id";

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
