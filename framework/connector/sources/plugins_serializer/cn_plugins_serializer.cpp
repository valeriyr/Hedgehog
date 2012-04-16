
#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugins_serializer/cn_plugins_serializer.hpp"

#include "xml_library/sources/rules/xl_tag.hpp"
#include "xml_library/sources/rules/xl_attribute.hpp"
#include "xml_library/sources/rules/xl_and_attribute.hpp"


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
	Tools::XmlLibrary::IRule& rule
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

} // PluginsSerializer::loadPluginsData


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
