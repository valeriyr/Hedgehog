
#ifndef __CN_IPLUGINS_MANAGER_INTERNAL_HPP__
#define __CN_IPLUGINS_MANAGER_INTERNAL_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugins_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

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

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGINS_MANAGER_INTERNAL_HPP__
