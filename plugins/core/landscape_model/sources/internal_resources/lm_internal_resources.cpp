
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const QString ModuleName = "LANDSCAPE_MODEL";

/*---------------------------------------------------------------------------*/

	const QString LandscapeVersion = "1.0.0";

	const QString ReplayVersion = "1.0.0";

/*---------------------------------------------------------------------------*/

	const QString LandscapesDirectoryName = "maps";

	const QString ReplaysDirectoryName = "replays";

/*---------------------------------------------------------------------------*/

	const Tools::Core::Time::Milliseconds TimeLimit = 100;

	const QString TimeLimitWarning = "Time limit has been exceeded! Time: '%1' ( limit: '%2' )";

	const QString SimulationHasBeenStartedMessage = "Simulation has been started at: '%1' msec";

	const QString SimulationHasBeenStoppedMessage = "Simulation has been stopped at: '%1' msec";

	const QString SocketHasBeenOpenedMessage = "Socket has been opened at: '%1:%2'";

	const QString SocketHasBeenClosedMessage = "Socket has been closed at: '%1:%2'";

	const QString CommandReceivedMessage = "Command has been received from '%1:%2', type '%3', timestamp '%4', tick '%5'";

	const QString CommandsIsNotPresentedMessage = "Commands are not presented for player '%1'(%2) for tick '%3'";

	const QString CommandWilNotBeProcessedMessage = "Command '%1' will not be processed because model is not initialized or simulation has been blocked";

	const QString CommandCannotBeProcessedInReplayModeMessage = "Command '%1' can not be processed in replay mode";

	const QString SimulationStoppedMessage = "Simulation has been stopped at: '%1' msec, tick '%2'";

/*---------------------------------------------------------------------------*/

	const QString ConfigurationScriptsRootDirectory = "landscape_model";

	const QString ObjectsConfigurationScriptsDirectory = "objects";

	const QString AIConfigurationScriptsDirectory = "ai";

/*---------------------------------------------------------------------------*/

namespace Xml {

/*---------------------------------------------------------------------------*/

	const QString LandscapeDocTypeString = "<!DOCTYPE hmap>";
	const QString ReplayDocTypeString = "<!DOCTYPE hreplay>";

	const QString HMap = "hmap";
	const QString HReplay = "hreplay";

	const QString Version = "version";

	const QString Landscape = "landscape";
	const QString Width = "width";
	const QString Height = "height";

	const QString VictoryCondition = "victory";

	const QString StartPoints = "start_points";
	const QString StartPoint = "start_point";

	const QString Surface = "surface";

	const QString Objects = "objects";
	const QString Object = "object";

	const QString Count = "count";

	const QString Name = "name";

	const QString Location = "location";

	const QString X = "x";
	const QString Y = "y";

	const QString Id = "id";

	const QString Players = "players";
	const QString Player = "player";

	const QString Race = "race";
	const QString Type = "type";

	const QString Commands = "commands";
	const QString Command = "command";

	const QString Tick = "tick";
	const QString TimeStamp = "timestamp";

	const QString Arguments = "arguments";
	const QString Argument = "argument";

	const QString Value = "value";

/*---------------------------------------------------------------------------*/

} // namespace Xml

/*---------------------------------------------------------------------------*/

	const QString DefaultPlayerName = "none";

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
