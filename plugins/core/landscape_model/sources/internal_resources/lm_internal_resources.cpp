
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

	const char* const ReplayVersion = "1.0.0";

/*---------------------------------------------------------------------------*/

	const char* const LandscapesDirectoryName = "maps";

	const char* const ReplaysDirectoryName = "replays";

/*---------------------------------------------------------------------------*/

	const Tools::Core::Time::Milliseconds TimeLimit = 100;

	const char* const TimeLimitWarning = "Time limit has been exceeded! Time: '%1' ( limit: '%2' )";

	const char* const SimulationHasBeenStartedMessage = "Simulation has been started at: '%1' msec";

	const char* const SimulationHasBeenStoppedMessage = "Simulation has been stopped at: '%1' msec";

	const char* const SocketHasBeenOpenedMessage = "Socket has been opened at: '%1:%2'";

	const char* const SocketHasBeenClosedMessage = "Socket has been closed at: '%1:%2'";

	const char* const CommandReceivedMessage = "Command has been received from '%1:%2', type '%3', timestamp '%4', tick '%5'";

	const char* const CommandsIsNotPresentedMessage = "Commands are not presented for player '%1'(%2) for tick '%3'";

	const char* const CommandWilNotBeProcessedMessage = "Command '%1' will not be processed because model is not initialized or simulation has been blocked";

	const char* const CommandCannotBeProcessedInReplayModeMessage = "Command '%1' can not be processed in replay mode";

	const char* const SimulationStoppedMessage = "Simulation has been stopped at: '%1' msec, tick '%2'";

/*---------------------------------------------------------------------------*/

	const char* const ConfigurationScriptsDirectory = "landscape_model";

/*---------------------------------------------------------------------------*/

namespace Xml {

/*---------------------------------------------------------------------------*/

	const char* const LandscapeDocTypeString = "<!DOCTYPE hmap>";
	const char* const ReplayDocTypeString = "<!DOCTYPE hreplay>";

	const char* const HMap = "hmap";
	const char* const HReplay = "hreplay";

	const char* const Version = "version";

	const char* const Landscape = "landscape";
	const char* const Width = "width";
	const char* const Height = "height";

	const char* const StartPoints = "start_points";
	const char* const StartPoint = "start_point";

	const char* const Surface = "surface";

	const char* const Objects = "objects";
	const char* const Object = "object";

	const char* const Count = "count";

	const char* const Name = "name";

	const char* const Location = "location";

	const char* const X = "x";
	const char* const Y = "y";

	const char* const Id = "id";

	const char* const Players = "players";
	const char* const Player = "player";

	const char* const Race = "race";
	const char* const Type = "type";

	const char* const Commands = "commands";
	const char* const Command = "command";

	const char* const Tick = "tick";
	const char* const TimeStamp = "timestamp";

	const char* const Arguments = "arguments";
	const char* const Argument = "argument";

	const char* const Value = "value";

/*---------------------------------------------------------------------------*/

} // namespace Xml

/*---------------------------------------------------------------------------*/

	const char* const DefaultPlayerName = "none";

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
