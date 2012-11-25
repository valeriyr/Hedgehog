
#ifndef __CN_PLUGINS_MANAGER_HPP__
#define __CN_PLUGINS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/sources/plugins_manager/cn_iplugins_manager_internal.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/

class PluginsManager
	:	public Tools::Core::BaseWrapper< IPluginsManagerInternal >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginsManager( const std::string& _pluginsDirectory );

	virtual ~PluginsManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IBase >
		getPluginInterface( const std::string& _pluginName, const unsigned int _interfaceId );

	/*virtual*/ bool isPluginLoaded( const std::string& _pluginName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void registerPlugin( boost::shared_ptr< PluginData > _pluginData );

	/*virtual*/ void loadPlugins();

	/*virtual*/ void closePlugins();

	/*virtual*/ const std::string& getPluginsDirectory() const;

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

	const std::string m_pluginsDirectory;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGINS_MANAGER_HPP__
