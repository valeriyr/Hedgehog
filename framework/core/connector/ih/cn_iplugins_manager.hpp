
#ifndef __CN_IPLUGINS_MANAGER_HPP__
#define __CN_IPLUGINS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

	const unsigned int PM_INTERFACE_ID = 1;

/*---------------------------------------------------------------------------*/

struct IPluginsManager
	:	public IBase
{
	virtual boost::intrusive_ptr< IBase >
		getPluginInterface( const unsigned int _pluginId, const unsigned int _interfaceId ) = 0;

	virtual bool isPluginLoaded( const unsigned int _pluginId ) const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGIN_MANAGER_HPP__
