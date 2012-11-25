
#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugins_serializer/cn_plugins_serializer.hpp"

#include "connector/sources/plugins_manager/cn_iplugins_manager_internal.hpp"
#include "connector/sources/plugins_manager/cn_plugin_data.hpp"

#include "xml_library/sources/rules/xl_tag_rule.hpp"
#include "xml_library/sources/rules/xl_attribute_rule.hpp"

#include "xml_library/sources/handle/xl_handle.hpp"

#include "xml_library/sources/visitors/xl_xml_parser.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Connector {

/*---------------------------------------------------------------------------*/


PluginsSerializer::PluginsSerializer( IPluginsManagerInternal& _pluginsManager )
	:	m_pluginsManager( _pluginsManager )
{
} // PluginsSerializer::PluginsSerializer


/*---------------------------------------------------------------------------*/


PluginsSerializer::~PluginsSerializer()
{
} // PluginsSerializer::~PluginsSerializer


/*---------------------------------------------------------------------------*/


void
PluginsSerializer::loadPluginsList()
{
} // PluginsSerializer::loadPluginsList


/*---------------------------------------------------------------------------*/


void
PluginsSerializer::onPluginElement(
		const unsigned int _pluginId
	,	const bool _loadAtStartup
	,	const std::string& _pluginName
	,	const std::string& _filePath
	)
{
	m_pluginsManager.registerPlugin(
		boost::shared_ptr< PluginData >( new PluginData( _pluginId, _loadAtStartup, _pluginName, _filePath ) ) );

} // PluginsSerializer::onPluginElement


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
