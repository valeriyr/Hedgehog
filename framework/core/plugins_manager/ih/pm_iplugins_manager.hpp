
#ifndef __PM_IPLUGINS_MANAGER_HPP__
#define __PM_IPLUGINS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct IPluginsManager
	:	public Tools::Core::IBase
{
	virtual boost::intrusive_ptr< Tools::Core::IBase >
		getPluginInterface( const QString& _pluginName, const quint32 _interfaceId ) = 0;

	virtual bool isPluginLoaded( const QString& _pluginName ) const = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_IPLUGINS_MANAGER_HPP__
