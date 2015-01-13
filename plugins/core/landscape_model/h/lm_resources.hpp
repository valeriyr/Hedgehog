
#ifndef __LM_RESOURCES_HPP__
#define __LM_RESOURCES_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Resources {

/*---------------------------------------------------------------------------*/

	const QString ModelThreadName = "ModelThread";

	const QString LandscapeFileExtension = "hmap";

	const QString LandscapeFileFilter = "*.hmap";

	const QString ReplayFileFilter = "*.hreplay";

/*---------------------------------------------------------------------------*/

namespace Properties {

/*---------------------------------------------------------------------------*/

	const QString PlayerName = "PlayerName";

	const QString Port = "Port";

	const QString Ip = "Ip";

	const QString ConnectionTimeOut = "ConnectionTimeOut";

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
