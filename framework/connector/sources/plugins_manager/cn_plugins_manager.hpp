
/** Connector plugin manager declaration part */

#ifndef __CN_PLUGINS_MANAGER_HPP__
#define __CN_PLUGINS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "connector/ih/cn_iplugins_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/

struct PluignData;

/*---------------------------------------------------------------------------*/

class PluginsManager
	:	public BaseWrapper< IPluginsManager >
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

	void registerPlugin( boost::shared_ptr< PluignData > _pluginData );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void loadPlugin( boost::shared_ptr< PluignData > _pluginData );

/*---------------------------------------------------------------------------*/

	typedef
		std::hash_map< unsigned int, boost::shared_ptr< PluignData > >
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
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __CN_PLUGINS_MANAGER_HPP__
