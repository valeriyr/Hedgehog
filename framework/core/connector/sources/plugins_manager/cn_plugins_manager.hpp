
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

	PluginsManager();

	virtual ~PluginsManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IBase >
		getPluginInterface( const unsigned int _pluginId, const unsigned int _interfaceId );

	/*virtual*/ bool isPluginLoaded( const unsigned int _pluginId ) const;

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
		std::hash_map< unsigned int, boost::shared_ptr< PluginData > >
		PluginsCollectionType;
	typedef
		PluginsCollectionType::const_iterator
		PluginsCollectionTypeIterator;

/*---------------------------------------------------------------------------*/

	PluginsCollectionType m_pluginsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGINS_MANAGER_HPP__
