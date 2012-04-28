
#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugins_serializer/cn_plugins_serializer.hpp"

#include "xml_library/sources/rules/xl_tag_rule.hpp"
#include "xml_library/sources/rules/xl_attribute_rule.hpp"

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
	QFile file( "./config/plugins.xml" );
	assert( file.exists() );

	if ( !file.open( QIODevice::ReadOnly ) )
		return;

	Tools::XmlLibrary::Rule& rule
		=
			Tools::XmlLibrary::Tag( "plugins" )
			[
				*Tools::XmlLibrary::Tag( "plugin" )
				[
						Tools::XmlLibrary::Attribute( "id" )
					&&
						Tools::XmlLibrary::Attribute( "name" )
				]
			];

	Tools::XmlLibrary::Parser::parse( *rule.getElement(), file );

} // PluginsSerializer::loadPluginsData


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
