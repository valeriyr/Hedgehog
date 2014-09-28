
#ifndef __LM_INTERNAL_RESOURCES_HPP__
#define __LM_INTERNAL_RESOURCES_HPP__

#include "time/t_time.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Resources {

/*---------------------------------------------------------------------------*/

	extern const char* const ModuleName;

/*---------------------------------------------------------------------------*/

	extern const char* const LandscapeVersion;

	extern const char* const ReplayVersion;

/*---------------------------------------------------------------------------*/

	extern const char* const LandscapesDirectoryName;

	extern const char* const ReplaysDirectoryName;

/*---------------------------------------------------------------------------*/

	extern const Tools::Core::Time::Milliseconds TimeLimit;

	extern const char* const TimeLimitWarning;

	extern const char* const SimulationHasBeenStartedMessage;

	extern const char* const SimulationHasBeenStoppedMessage;

	extern const char* const SocketHasBeenOpenedMessage;

	extern const char* const SocketHasBeenClosedMessage;

	extern const char* const CommandReceivedMessage;

	extern const char* const CommandsIsNotPresentedMessage;

	extern const char* const CommandWilNotBeProcessedMessage;

	extern const char* const CommandCannotBeProcessedInReplayModeMessage;

	extern const char* const SimulationStoppedMessage;

/*---------------------------------------------------------------------------*/

	extern const char* const ConfigurationScriptsRootDirectory;

	extern const char* const ObjectsConfigurationScriptsDirectory;

	extern const char* const AIConfigurationScriptsDirectory;

/*---------------------------------------------------------------------------*/

namespace Xml {

/*---------------------------------------------------------------------------*/

	extern const char* const LandscapeDocTypeString;
	extern const char* const ReplayDocTypeString;

	extern const char* const HMap;
	extern const char* const HReplay;

	extern const char* const Version;

	extern const char* const Landscape;
	extern const char* const Width;
	extern const char* const Height;

	extern const char* const VictoryCondition;

	extern const char* const StartPoints;
	extern const char* const StartPoint;

	extern const char* const Surface;

	extern const char* const Objects;
	extern const char* const Object;

	extern const char* const Count;

	extern const char* const Name;

	extern const char* const Location;

	extern const char* const X;
	extern const char* const Y;

	extern const char* const Id;

	extern const char* const Players;
	extern const char* const Player;

	extern const char* const Race;
	extern const char* const Type;

	extern const char* const Commands;
	extern const char* const Command;

	extern const char* const Tick;
	extern const char* const TimeStamp;

	extern const char* const Arguments;
	extern const char* const Argument;

	extern const char* const Value;

/*---------------------------------------------------------------------------*/

} // namespace Xml

/*---------------------------------------------------------------------------*/

	extern const char* const DefaultPlayerName;

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_INTERNAL_RESOURCES_HPP__
