
/** Connector plugins serializer implementation part */

#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugins_serializer/cn_plugins_serializer.hpp"

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
} // PluginsSerializer::loadPluginsData


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
