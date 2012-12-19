
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/plugin/le_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "commands_manager/h/cm_plugin_id.hpp"

#include "landscape_editor/sources/editor_view/le_editor_view.hpp"
#include "landscape_editor/sources/objects_view/le_objects_view.hpp"
#include "landscape_editor/sources/description_view/le_description_view.hpp"

#include "landscape_editor/sources/commands/le_new_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_open_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_close_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_save_landscape_command.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

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
	using namespace Framework::Core::CommandsManager;

	boost::intrusive_ptr< ICommandsRegistry > commandsRegistry = getCommandsManager();

	commandsRegistry->registerCommand(
			Resources::Commands::NewLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new NewLandscapeCommand() ) );
	commandsRegistry->registerCommand(
			Resources::Commands::OpenLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new OpenLandscapeCommand() ) );
	commandsRegistry->registerCommand(
			Resources::Commands::CloseLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new CloseLandscapeCommand() ) );
	commandsRegistry->registerCommand(
			Resources::Commands::SaveLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new SaveLandscapeCommand() ) );

	m_objectsView.reset( new ObjectsView() );
	m_editorView.reset( new EditorView() );
	m_descriptionView.reset( new DescriptionView() );

	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		windowManager = getWindowManager();

	windowManager->addView(
			m_objectsView
		,	Framework::GUI::WindowManager::ViewPosition::Left );
	windowManager->addView(
			m_editorView
		,	Framework::GUI::WindowManager::ViewPosition::Center );
	windowManager->addView(
			m_descriptionView
		,	Framework::GUI::WindowManager::ViewPosition::Right );

	windowManager->addCommandToMenu( "File/New", Resources::Commands::NewLandscapeCommandName );
	windowManager->addCommandToMenu( "File/Open", Resources::Commands::OpenLandscapeCommandName );
	windowManager->addCommandToMenu( "File/Close", Resources::Commands::CloseLandscapeCommandName );
	windowManager->addCommandToMenu( "File/Save", Resources::Commands::SaveLandscapeCommandName );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		windowManager = getWindowManager();

	windowManager->removeCommandFromMenu( "File/New" );

	windowManager->removeView( m_descriptionView );
	windowManager->removeView( m_editorView );
	windowManager->removeView( m_objectsView );

	m_descriptionView.reset();
	m_editorView.reset();
	m_objectsView.reset();

	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
		commandsRegistry = getCommandsManager();

	commandsRegistry->unregisterCommand( Resources::Commands::NewLandscapeCommandName );
	commandsRegistry->unregisterCommand( Resources::Commands::OpenLandscapeCommandName );
	commandsRegistry->unregisterCommand( Resources::Commands::CloseLandscapeCommandName );
	commandsRegistry->unregisterCommand( Resources::Commands::SaveLandscapeCommandName );

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


boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
PluginInstance::getCommandsManager() const
{
	return
		getPluginInterface< Framework::Core::CommandsManager::ICommandsRegistry >(
				Framework::Core::CommandsManager::PID_COMMANDS_MANAGER
			,	Framework::Core::CommandsManager::IID_COMMANDS_REGISTRY );

} // PluginInstance::getCommandsManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
