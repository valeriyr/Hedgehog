
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/plugin/le_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "commands_manager/h/cm_plugin_id.hpp"

#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/h/lm_plugin_id.hpp"

#include "landscape_editor/sources/environment/le_environment.hpp"

#include "landscape_editor/sources/views/le_editor_view.hpp"
#include "landscape_editor/sources/views/le_objects_view.hpp"
#include "landscape_editor/sources/views/le_description_view.hpp"

#include "landscape_editor/sources/commands/le_new_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_open_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_close_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_save_landscape_command.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_editor/sources/landscape_editor_controller/le_landscape_editor_controller.hpp"


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
	m_environment.reset( new Environment( *this ) );

	using namespace Framework::Core::CommandsManager;
	boost::intrusive_ptr< ICommandsRegistry > commandsRegistry = getCommandsManager();

	commandsRegistry->registerCommand(
			Resources::Commands::NewLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new NewLandscapeCommand( *m_environment ) ) );
	commandsRegistry->registerCommand(
			Resources::Commands::OpenLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new OpenLandscapeCommand( *m_environment ) ) );
	commandsRegistry->registerCommand(
			Resources::Commands::CloseLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new CloseLandscapeCommand( *m_environment ) ) );
	commandsRegistry->registerCommand(
			Resources::Commands::SaveLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new SaveLandscapeCommand( *m_environment ) ) );

	m_objectsView.reset( new ObjectsView( *m_environment ) );
	m_editorView.reset( new EditorView( *m_environment ) );
	m_descriptionView.reset( new DescriptionView( *m_environment ) );

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

	m_landscapeEditorController.reset( new LandscapeEditorController( *m_environment ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_landscapeEditorController.reset();

	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		windowManager = getWindowManager();

	windowManager->removeCommandFromMenu( "File/Save" );
	windowManager->removeCommandFromMenu( "File/Close" );
	windowManager->removeCommandFromMenu( "File/Open" );
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


boost::intrusive_ptr< Framework::GUI::WindowManager::IDialogsManager >
PluginInstance::getDialogsManager() const
{
	return
		getPluginInterface< Framework::GUI::WindowManager::IDialogsManager >(
				Framework::GUI::WindowManager::PID_WINDOW_MANAGER
			,	Framework::GUI::WindowManager::IID_DIALOGS_MANAGER );

} // PluginInstance::getDialogsManager


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


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeEditor >
PluginInstance::getLandscapeEditor() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::ILandscapeEditor >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_LANDSCAPE_EDITOR );

} // PluginInstance::getLandscapeEditor


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorView >
PluginInstance::getObjectsView() const
{
	return m_objectsView;

} // PluginInstance::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorView >
PluginInstance::getEditorView() const
{
	return m_editorView;

} // PluginInstance::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorView >
PluginInstance::getDescriptionView() const
{
	return m_descriptionView;

} // PluginInstance::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorController >
PluginInstance::getLandscapeEditorController() const
{
	return m_landscapeEditorController;

} // PluginInstance::getLandscapeEditorController


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
