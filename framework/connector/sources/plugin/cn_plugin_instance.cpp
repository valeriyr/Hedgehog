
/** Connector plugin instance implementation */

#include "connector/sources/ph/cn_ph.hpp"

#include "connector/sources/plugin/cn_plugin_instance.hpp"

#include "connector/h/cn_plugin_factory.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Connector {

/*---------------------------------------------------------------------------*/


PluginInstance::PluginInstance()
{
	std::cout << "> Connector plugin instance created" << std::endl;

} // PluginInstance::PluginInstance


/*---------------------------------------------------------------------------*/


PluginInstance::~PluginInstance()
{
	std::cout << "> Connector plugin instance deleted" << std::endl;

} // PluginInstance::~PluginInstance


/*---------------------------------------------------------------------------*/


void
PluginInstance::initialize( IBase* _connector )
{
	std::cout << "> Connector loaded" << std::endl;

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	std::cout << "> Connector closed" << std::endl;

} // PluginInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace Connector
} // namespace Framework

/*---------------------------------------------------------------------------*/
