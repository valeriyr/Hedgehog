
#ifndef __LM_INTERNAL_RESOURCES_HPP__
#define __LM_INTERNAL_RESOURCES_HPP__

#include "time/t_time.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Resources {

/*---------------------------------------------------------------------------*/

	extern const QString ModuleName;

/*---------------------------------------------------------------------------*/

	extern const QString LandscapeVersion;

	extern const QString ReplayVersion;

/*---------------------------------------------------------------------------*/

	extern const QString LandscapesDirectoryName;

	extern const QString ReplaysDirectoryName;

/*---------------------------------------------------------------------------*/

	extern const Tools::Core::Time::Milliseconds TimeLimit;

	extern const QString TimeLimitWarning;

	extern const QString SimulationHasBeenStartedMessage;

	extern const QString SimulationHasBeenStoppedMessage;

	extern const QString SocketHasBeenOpenedMessage;

	extern const QString SocketHasBeenClosedMessage;

	extern const QString CommandReceivedMessage;

	extern const QString CommandsIsNotPresentedMessage;

	extern const QString CommandWilNotBeProcessedMessage;

	extern const QString CommandCannotBeProcessedInReplayModeMessage;

	extern const QString SimulationStoppedMessage;

/*---------------------------------------------------------------------------*/

	extern const QString ConfigurationScriptsRootDirectory;

	extern const QString ObjectsConfigurationScriptsDirectory;

	extern const QString AIConfigurationScriptsDirectory;

/*---------------------------------------------------------------------------*/

namespace Xml {

/*---------------------------------------------------------------------------*/

	extern const QString LandscapeDocTypeString;
	extern const QString ReplayDocTypeString;

	extern const QString HMap;
	extern const QString HReplay;

	extern const QString Version;

	extern const QString Landscape;
	extern const QString Width;
	extern const QString Height;

	extern const QString VictoryCondition;

	extern const QString StartPoints;
	extern const QString StartPoint;

	extern const QString Surface;

	extern const QString Objects;
	extern const QString GameObject;

	extern const QString Count;

	extern const QString Name;

	extern const QString Location;

	extern const QString X;
	extern const QString Y;

	extern const QString Id;

	extern const QString Players;
	extern const QString Player;

	extern const QString Race;
	extern const QString Type;

	extern const QString Commands;
	extern const QString Command;

	extern const QString Tick;
	extern const QString TimeStamp;

	extern const QString Arguments;
	extern const QString Argument;

	extern const QString Value;

/*---------------------------------------------------------------------------*/

} // namespace Xml

/*---------------------------------------------------------------------------*/

	extern const QString DefaultPlayerName;

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_INTERNAL_RESOURCES_HPP__
