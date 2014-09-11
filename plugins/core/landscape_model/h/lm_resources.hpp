
#ifndef __LM_RESOURCES_HPP__
#define __LM_RESOURCES_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const char* const ModelThreadName = "ModelThread";

	const char* const LandscapeFileExtension = "hmap";

	const char* const LandscapeFileFilter = "*.hmap";

	const char* const ReplayFileFilter = "*.hreplay";

/*---------------------------------------------------------------------------*/

namespace Properties {

/*---------------------------------------------------------------------------*/

	const char* const PlayerName = "PlayerName";

	const char* const Port = "Port";

	const char* const Ip = "Ip";

	const char* const ConnectionTimeOut = "ConnectionTimeOut";

/*---------------------------------------------------------------------------*/

	const int DefaultPortValue = 1988;

/*---------------------------------------------------------------------------*/

} // namespace Properties

/*---------------------------------------------------------------------------*/

} // namespace Resources
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_RESOURCES_HPP__
