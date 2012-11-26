
#ifndef __PM_BASE_PALUGIN_HPP__
#define __PM_BASE_PALUGIN_HPP__

#include "plugins_manager/ih/pm_iplugin.hpp"
#include "plugins_manager/ih/pm_iplugins_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

class BasePlugin
	:	public Tools::Core::BaseWrapper< IPlugin >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	BasePlugin()
		:	m_pluginsManager( NULL )
	{}

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initialize( IPluginsManager* _pluginsManager )
	{
		m_pluginsManager = _pluginsManager;
		initialize();
	}

/*---------------------------------------------------------------------------*/

	virtual void initialize() = 0;

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	template< typename _TInterfaceType >
	boost::intrusive_ptr< _TInterfaceType >
	getPluginInterface(
			const std::string& _pluginName
		,	const unsigned int _interfaceId ) const
	{
		return
			boost::intrusive_ptr< _TInterfaceType >(
				static_cast< _TInterfaceType* >(
					getPluginsManager()->getPluginInterface( _pluginName, _interfaceId ).get() ) );
	}

	IPluginsManager* getPluginsManager() const
	{
		return m_pluginsManager;
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IPluginsManager* m_pluginsManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_BASE_PALUGIN_HPP__
