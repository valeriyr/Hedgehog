
#include "logger/sources/ph/lg_ph.hpp"

#include "logger/sources/plugin/lg_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "logger/sources/console_logger/lg_console_logger.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Logger {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( Tools::Core::IID_MESSENGER, m_consoleLogger )

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
	m_consoleLogger.reset( new ConsoleLogger() );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_consoleLogger.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace Logger
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
