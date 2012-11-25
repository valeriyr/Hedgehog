
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
PluginsSerializer::loadPluginsData()
{
	QFile file( "e:/Hedgehog/x64/Debug/bin/config/plugins.xml" );
	assert( file.exists() );

	if ( !file.open( QIODevice::ReadOnly ) )
		return;

	Tools::XmlLibrary::Tag rule
		=
			Tools::XmlLibrary::Tag( "plugins" )
			[
				*Tools::XmlLibrary::Tag( "plugin" )
				[
						Tools::XmlLibrary::Attribute( "name", Tools::XmlLibrary::AttributeType::String )
					&&
						Tools::XmlLibrary::Attribute( "file", Tools::XmlLibrary::AttributeType::String )
					&&
						Tools::XmlLibrary::Attribute( "id", Tools::XmlLibrary::AttributeType::Integer )
					&&
						Tools::XmlLibrary::Attribute( "loadatstartup", Tools::XmlLibrary::AttributeType::Integer )
				]
				.postHandle(
						boost::bind( &PluginsSerializer::onPluginElement, this, _1, _2, _3, _4 )
					,	Tools::XmlLibrary::UIntAttributeExtructor( "id" )
					,	Tools::XmlLibrary::BoolAttributeExtructor( "loadatstartup" )
					,	Tools::XmlLibrary::StringAttributeExtructor( "name" )
					,	Tools::XmlLibrary::StringAttributeExtructor( "file" )
					)
			];

	Tools::XmlLibrary::Parser::parse( *rule.getElement(), file );

} // PluginsSerializer::loadPluginsData


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
} // namespace Framework

/*---------------------------------------------------------------------------*/
