
#ifndef __PM_PLUGIN_FACTORY_HPP__
#define __PM_PLUGIN_FACTORY_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/ih/pm_iplugin.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

typedef
	Framework::Core::PluginsManager::IPlugin*
	(*PluginFactoryPtr) ();

/*---------------------------------------------------------------------------*/

const char* const PluginFactoryName = "getPlugin";

/*---------------------------------------------------------------------------*/

#define PLUGIN_FACTORY_DECLARATION( PLUGIN_INSTANCE )						\
																			\
extern "C" __declspec( dllexport )											\
Framework::Core::PluginsManager::IPlugin*									\
getPlugin()																	\
{																			\
	return new PLUGIN_INSTANCE();											\
}																			\

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_PLUGIN_FACTORY_HPP__
