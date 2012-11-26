
#ifndef __PM_IPLUGINS_MANAGER_INTERNAL_HPP__
#define __PM_IPLUGINS_MANAGER_INTERNAL_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/ih/pm_iplugins_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct PluginData;

/*---------------------------------------------------------------------------*/

struct IPluginsManagerInternal
	:	public IPluginsManager
{
	virtual void registerPlugin( boost::shared_ptr< PluginData > _pluginData ) = 0;

	virtual void loadPlugins() = 0;

	virtual void closePlugins() = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_IPLUGINS_MANAGER_INTERNAL_HPP__
