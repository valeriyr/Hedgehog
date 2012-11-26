
#ifndef __PM_PLUGINS_MANAGER_HPP__
#define __PM_PLUGINS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "plugins_manager/sources/plugins_manager/pm_iplugins_manager_internal.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace PluginsManager {

/*---------------------------------------------------------------------------*/

struct ISystemInformation;

/*---------------------------------------------------------------------------*/

class PluginsManager
	:	public Tools::Core::BaseWrapper< IPluginsManagerInternal >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginsManager( boost::intrusive_ptr< ISystemInformation > _systemInformation );

	virtual ~PluginsManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IBase >
		getPluginInterface( const std::string& _pluginName, const unsigned int _interfaceId );

	/*virtual*/ bool isPluginLoaded( const std::string& _pluginName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void registerPlugin( boost::shared_ptr< PluginData > _pluginData );

	/*virtual*/ void loadPlugins();

	/*virtual*/ void closePlugins();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void loadPluginIfNeeded( PluginData& _pluginData );

/*---------------------------------------------------------------------------*/

	typedef
		std::hash_map< std::string, boost::shared_ptr< PluginData > >
		PluginsCollectionType;
	typedef
		PluginsCollectionType::const_iterator
		PluginsCollectionTypeIterator;

/*---------------------------------------------------------------------------*/

	PluginsCollectionType m_pluginsCollection;

	boost::intrusive_ptr< ISystemInformation > m_systemInformation;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace PluginsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __PM_PLUGINS_MANAGER_HPP__
