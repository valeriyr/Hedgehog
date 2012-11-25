
#ifndef __CN_IPLUGINS_MANAGER_HPP__
#define __CN_IPLUGINS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsManager
	:	public Tools::Core::IBase
{
	virtual boost::intrusive_ptr< Tools::Core::IBase >
		getPluginInterface( const std::string& _pluginName, const unsigned int _interfaceId ) = 0;

	virtual bool isPluginLoaded( const std::string& _pluginName ) const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_IPLUGIN_MANAGER_HPP__
