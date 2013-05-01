
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"
#include "landscape_viewer/sources/game_initializer/lv_game_initializer.hpp"
#include "landscape_viewer/sources/landscape_view/lv_landscape_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/commands/lv_run_game_command.hpp"
#include "landscape_viewer/sources/commands/lv_stop_game_command.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "landscape_model/ih/lm_ilandscape_manager.hpp"
#include "landscape_model/h/lm_plugin_id.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "commands_manager/h/cm_plugin_id.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"
#include "images_manager/h/im_plugin_id.hpp"

#include "game_manager/ih/gm_igame_manager.hpp"
#include "game_manager/h/gm_plugin_id.hpp"


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

	m_landscapeView.reset( new LandscapeView( *m_environment ) );

	getWindowManager()->addView(
			m_landscapeView
		,	Framework::GUI::WindowManager::ViewPosition::Center );

	using namespace Framework::Core::CommandsManager;
	getCommandsManager()->registerCommand(
			Resources::Commands::RunGameCommandName
		,	boost::intrusive_ptr< ICommand >( new RunGameCommand( *m_environment ) ) );
	getCommandsManager()->registerCommand(
			Resources::Commands::StopGameCommandName
		,	boost::intrusive_ptr< ICommand >( new StopGameCommand( *m_environment ) ) );

	getWindowManager()->addCommandToMenu( "Game/Run", Resources::Commands::RunGameCommandName );
	getWindowManager()->addCommandToMenu( "Game/Stop", Resources::Commands::StopGameCommandName );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	getWindowManager()->removeCommandFromMenu( "Game/Stop" );
	getWindowManager()->removeCommandFromMenu( "Game/Run" );

	getCommandsManager()->unregisterCommand( Resources::Commands::StopGameCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::RunGameCommandName );

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


boost::intrusive_ptr< LandscapeView >
PluginInstance::getLandscapeView() const
{
	return m_landscapeView;

} // PluginInstance::getLandscapeView


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


boost::intrusive_ptr< Framework::GUI::ImagesManager::IImagesManager >
PluginInstance::getImagesManager() const
{
	return
		getPluginInterface< Framework::GUI::ImagesManager::IImagesManager >(
				Framework::GUI::ImagesManager::PID_IMAGES_MANAGER
			,	Framework::GUI::ImagesManager::IID_IMAGES_MANAGER );

} // PluginInstance::getImageManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
PluginInstance::getCommandsManager() const
{
	return
		getPluginInterface< Framework::Core::CommandsManager::ICommandsRegistry >(
				Framework::Core::CommandsManager::PID_COMMANDS_MANAGER
			,	Framework::Core::CommandsManager::IID_COMMANDS_REGISTRY );

} // PluginInstance::getCommandsManager


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


boost::intrusive_ptr< Plugins::Core::GameManager::IGameManager >
PluginInstance::getGameManager() const
{
	return
		getPluginInterface< Plugins::Core::GameManager::IGameManager >(
				Plugins::Core::GameManager::PID_GAME_MANAGER
			,	Plugins::Core::GameManager::IID_GAME_MANAGER );

} // PluginInstance::getGameManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
