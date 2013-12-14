
#include "console/sources/ph/con_ph.hpp"

#include "console/sources/plugin/con_plugin_instance.hpp"

#include "console/sources/main_view/con_main_view.hpp"
#include "console/sources/console_messenger/con_console_messenger.hpp"
#include "console/sources/environment/con_environment.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "script_engine/ih/se_iscripts_executor.hpp"
#include "script_engine/h/se_plugin_id.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( Tools::Core::IID_MESSENGER, m_consoleMessenger.get() )

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
	m_environment.reset( new Environment( *this ) );

	m_consoleView.reset( new MainView( *m_environment ) );

	getWindowManager()->addView(
			m_consoleView
		,	Framework::GUI::WindowManager::ViewPosition::Bottom );

	m_consoleMessenger.reset( new ConsoleMessenger( *m_consoleView ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_consoleMessenger.reset();

	getWindowManager()->removeView( m_consoleView );
	m_consoleView.reset();

	m_environment.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
PluginInstance::getWindowManager() const
{
	return
		getPluginInterface< Framework::GUI::WindowManager::IWindowManager >(
				Framework::GUI::WindowManager::PID_WINDOW_MANAGER
			,	Framework::GUI::WindowManager::IID_WINDOW_MANAGER );

} // PluginInstance::getWindowManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::ScriptEngine::IScriptsExecutor >
PluginInstance::getScriptsExecutor() const
{
	return
		getPluginInterface< Framework::Core::ScriptEngine::IScriptsExecutor >(
				Framework::Core::ScriptEngine::PID_SCRIPT_ENGINE
			,	Framework::Core::ScriptEngine::IID_SCRIPTS_EXECUTOR );

} // PluginInstance::getCommandExecutor


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
