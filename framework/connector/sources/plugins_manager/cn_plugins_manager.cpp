
/** Connector plugin manager implementation part */

#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugins_serializer/cn_iplugins_serializer.hpp"

#include "connector/sources/plugins_manager/cn_plugins_manager.hpp"
#include "connector/sources/plugins_serializer/cn_plugins_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


PluginsManager::PluginsManager( boost::intrusive_ptr< IPluginsSerializer > _pluginsSerializer )
	:	m_pluginsCollection()
	,	m_pluginsSerializer( _pluginsSerializer )
{
} // PluginsManager::PluginsManager


/*---------------------------------------------------------------------------*/


PluginsManager::~PluginsManager()
{
} // PluginsManager::~PluginsManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBase >
PluginsManager::getPluginInterface( const int _pluginId, const int _interfaceId )
{
	return boost::intrusive_ptr< IBase >();

} // PluginsManager::getPluginInterface


/*---------------------------------------------------------------------------*/


bool
PluginsManager::isPluginLoaded( const int _pluginId ) const
{
	return false;

} // PluginsManager::isPluginLoaded


/*---------------------------------------------------------------------------*/


void
PluginsManager::loadStartupPlugins()
{
	readPluginsDatabase();

} // PluginsManager::loadStartupPlugins


/*---------------------------------------------------------------------------*/


void
PluginsManager::readPluginsDatabase()
{
} // PluginsManager::readPluginsDatabase


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
