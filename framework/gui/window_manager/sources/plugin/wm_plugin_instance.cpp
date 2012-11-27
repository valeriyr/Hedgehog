
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
PluginInstance::initialize()
{
	m_mainWindow.reset( new QMainWindow() );

	m_mainWindow->setWindowTitle( getSystemInformation()->getApplicationName().c_str() );

	m_mainWindow->setCentralWidget( new QTextEdit( "This is a most cool game!!!" ) );

	QDockWidget* bottomDocWidget( new QDockWidget() );
	bottomDocWidget->setWidget( new QTextEdit( "Console should be here." ) );

	m_mainWindow->addDockWidget( Qt::BottomDockWidgetArea, bottomDocWidget );

	m_mainWindow->showMaximized();

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_mainWindow.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::PluginsManager::ISystemInformation >
PluginInstance::getSystemInformation() const
{
	return
		getPluginInterface< Core::PluginsManager::ISystemInformation >(
				Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Core::PluginsManager::IID_SYSTEM_INFORMATION );

} // PluginInstance::getSystemInformation


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
