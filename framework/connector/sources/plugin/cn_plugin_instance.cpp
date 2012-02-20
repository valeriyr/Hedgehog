
/** Connector plugin instance implementation */

#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugin/cn_plugin_instance.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


PluginInstance::PluginInstance()
{
} // PluginInstance::PluginInstance


/*---------------------------------------------------------------------------*/


PluginInstance::~PluginInstance()
{
} // PluginInstance::~PluginInstance


/*---------------------------------------------------------------------------*/


void
PluginInstance::initialize( IBase* _connector )
{
	std::cout << "> Connector loaded" << std::cout;

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	std::cout << "> Connector closed" << std::cout;

} // PluginInstance::close


/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
