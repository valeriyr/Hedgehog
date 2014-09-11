
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

	extern const char* const SimulationStoppedMessage;

/*---------------------------------------------------------------------------*/

	extern const char* const ConfigurationScriptsDirectory;

/*---------------------------------------------------------------------------*/

	extern const char* const DocTypeString;

	extern const char* const HMapTagName;

	extern const char* const VersionAttributeName;

	extern const char* const WidthAttributeName;
	extern const char* const HeightAttributeName;

	extern const char* const StartPointsTagName;
	extern const char* const StartPointTagName;

	extern const char* const SurfaceTagName;

	extern const char* const ObjectsTagName;
	extern const char* const ObjectTagName;

	extern const char* const CountAttributeName;

	extern const char* const NameAttributeName;

	extern const char* const LocationTagName;

	extern const char* const XAttributeName;
	extern const char* const YAttributeName;

	extern const char* const IdAttributeName;

/*---------------------------------------------------------------------------*/

	extern const char* const DefaultPlayerName;

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_INTERNAL_RESOURCES_HPP__
