
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/plugin/wm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

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
PluginInstance::initialize( Framework::Core::PluginsManager::IPluginsManager& _pluginsManager )
{
	m_mainWindow.reset( new QMainWindow() );

	boost::intrusive_ptr< Core::PluginsManager::ISystemInformation > systemInformation
		= getPluginInterface< Core::PluginsManager::ISystemInformation >(
				_pluginsManager
			,	Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Core::PluginsManager::IID_SYSTEM_INFORMATION );

	m_mainWindow->setWindowTitle( systemInformation->getApplicationName().c_str() );

	m_mainWindow->setCentralWidget( new QTextEdit( "This is a most cool game!!!" ) );

	m_mainWindow->showMaximized();

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_mainWindow.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
