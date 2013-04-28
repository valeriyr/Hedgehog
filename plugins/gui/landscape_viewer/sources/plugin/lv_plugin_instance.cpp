
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"
#include "landscape_viewer/sources/game_initializer/lv_game_initializer.hpp"
#include "landscape_viewer/sources/landscape_view/lv_landscape_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "landscape_model/ih/lm_ilandscape_manager.hpp"
#include "landscape_model/h/lm_plugin_id.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

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
	m_environment.reset( new Environment( *this ) );

	m_gameInitializer.reset( new GameInitializer( *m_environment ) );

	m_landscapeView.reset( new LandscapeView() );

	getWindowManager()->addView(
			m_landscapeView
		,	Framework::GUI::WindowManager::ViewPosition::Center );

	getWindowManager()->addCommandToMenu( "Game/Run", Resources::Commands::RunGameCommandName );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	getWindowManager()->removeCommandFromMenu( "Game/Run" );

	getWindowManager()->removeView( m_landscapeView );

	m_landscapeView.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IGameInitializer >
PluginInstance::getGameInitializer() const
{
	return m_gameInitializer;

} // PluginInstance::getGameInitializer


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


boost::intrusive_ptr< Framework::GUI::WindowManager::IDialogsManager >
PluginInstance::getDialogsManager() const
{
	return
		getPluginInterface< Framework::GUI::WindowManager::IDialogsManager >(
				Framework::GUI::WindowManager::PID_WINDOW_MANAGER
			,	Framework::GUI::WindowManager::IID_DIALOGS_MANAGER );

} // PluginInstance::getDialogsManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeManager >
PluginInstance::getLandscapeManager() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::ILandscapeManager >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_LANDSCAPE_MANAGER );

} // PluginInstance::getLandscapeManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
