
#include "commands_manager/sources/ph/cm_ph.hpp"

#include "commands_manager/sources/plugin/cm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace CommandsManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

END_INTERFACE_MAP()


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
PluginInstance::initialize()
{
} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
} // PluginInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace CommandsManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
