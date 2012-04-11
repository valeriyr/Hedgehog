
/** Connector plugin manager internal interface */

#ifndef __CN_IPLUGINS_MANAGER_INTERNAL_HPP__
#define __CN_IPLUGINS_MANAGER_INTERNAL_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugins_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsManagerInternal
	:	public IPluginsManager
{
	virtual void registerPlugin( boost::shared_ptr< PluginData > _pluginData ) = 0;

	virtual void loadStartupPlugins() = 0;

	virtual void closeAllPlugins() = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGINS_MANAGER_INTERNAL_HPP__
