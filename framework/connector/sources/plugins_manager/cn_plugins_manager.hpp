
/** Connector plugin manager declaration part */

#ifndef __CN_PLUGINS_MANAGER_HPP__
#define __CN_PLUGINS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugins_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct IPluginsSerializer;

/*---------------------------------------------------------------------------*/

class PluginsManager
	:	public BaseWrapper< IPluginsManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PluginsManager( boost::intrusive_ptr< IPluginsSerializer > _pluginsSerializer );

	virtual ~PluginsManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IBase >
		getPluginInterface( const int _pluginId, const int _interfaceId );

	/*virtual*/ bool isPluginLoaded( const int _pluginId ) const;

/*---------------------------------------------------------------------------*/

	void loadStartupPlugins();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void readPluginsDatabase();

/*---------------------------------------------------------------------------*/

	typedef
		std::hash_map< const int, boost::intrusive_ptr< IBase > >
		PluginsCollectionType;
	typedef
		PluginsCollectionType::const_iterator
		PluginsCollectionTypeIterator;

/*---------------------------------------------------------------------------*/

	PluginsCollectionType m_pluginsCollection;

	boost::intrusive_ptr< IPluginsSerializer > m_pluginsSerializer;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGINS_MANAGER_HPP__
