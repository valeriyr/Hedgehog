
#ifndef __PM_IPLUGIN_HPP__
#define __PM_IPLUGIN_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "plugins_manager/ih/pm_iplugins_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/


struct IPlugin
	:	public Tools::Core::IBase
{
	virtual void initialize( IPluginsManager& _pluginsManager ) = 0;

	virtual void close() = 0;

	virtual Tools::Core::IBase* getInterface( const unsigned int _interfaceId ) = 0;
};

/*---------------------------------------------------------------------------*/


class BasePlugin
	:	public Tools::Core::BaseWrapper< IPlugin >
{

public:

	template< typename _TInterfaceType >
	boost::intrusive_ptr< _TInterfaceType >
	getPluginInterface(
			IPluginsManager& _pluginsManager
		,	const std::string& _pluginName
		,	const unsigned int _interfaceId ) const
	{
		return
			boost::intrusive_ptr< _TInterfaceType >(
				static_cast< _TInterfaceType* >(
					_pluginsManager.getPluginInterface( _pluginName, _interfaceId ).get() ) );
	}
};


/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_IPLUGIN_HPP__
