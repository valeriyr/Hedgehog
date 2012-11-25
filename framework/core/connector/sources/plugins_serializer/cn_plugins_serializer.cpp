
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
	QDir pluginsDirectory = QDir( m_pluginsManager.getPluginsDirectory().c_str() );
	assert( pluginsDirectory.exists() );

	QStringList filesFilter;
	filesFilter.push_back( "*.dll" );

	QFileInfoList filesList = pluginsDirectory.entryInfoList( filesFilter );

	for (int i = 0; i < filesList.size(); ++i)
	{
         QFileInfo fileInfo = filesList.at( i );
		 m_pluginsManager.registerPlugin( boost::shared_ptr< PluginData >( new PluginData( fileInfo.baseName().toLocal8Bit().data() ) ) );
	}

} // PluginsSerializer::loadPluginsList


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
