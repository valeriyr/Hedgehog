
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/plugin/le_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"
#include "images_manager/h/im_plugin_id.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "commands_manager/h/cm_plugin_id.hpp"

#include "minimap_viewer/ih/mv_iminimap_viewer.hpp"
#include "minimap_viewer/h/mv_plugin_id.hpp"

#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/h/lm_plugin_id.hpp"

#include "landscape_editor/sources/environment/le_environment.hpp"

#include "landscape_editor/sources/views/le_editor_view.hpp"
#include "landscape_editor/sources/views/le_objects_view.hpp"
#include "landscape_editor/sources/views/le_description_view.hpp"

#include "landscape_editor/sources/commands/le_new_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_open_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_close_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_save_landscape_command.hpp"
#include "landscape_editor/sources/commands/le_save_as_landscape_command.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_editor/sources/landscape_editor/le_landscape_editor.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_LANDSCAPE_EDITOR, m_landscapeEditor.get() )

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
	fillSurfaceItemsCache();

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
	commandsRegistry->registerCommand(
			Resources::Commands::SaveAsLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new SaveAsLandscapeCommand( *m_environment ) ) );

	m_landscapeEditor.reset( new LandscapeEditor( *m_environment ) );

	m_objectsView.reset( new ObjectsView( *m_environment ) );
	m_editorView.reset( new EditorView( *m_environment ) );
	m_descriptionView.reset( new DescriptionView( *m_landscapeEditor ) );

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
	windowManager->addCommandToMenu( "File/Save As", Resources::Commands::SaveAsLandscapeCommandName );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	boost::intrusive_ptr< Framework::GUI::WindowManager::IWindowManager >
		windowManager = getWindowManager();

	windowManager->removeCommandFromMenu( "File/Save As" );
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

	m_landscapeEditor.reset();

	boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
		commandsRegistry = getCommandsManager();

	commandsRegistry->unregisterCommand( Resources::Commands::SaveAsLandscapeCommandName );
	commandsRegistry->unregisterCommand( Resources::Commands::SaveLandscapeCommandName );
	commandsRegistry->unregisterCommand( Resources::Commands::CloseLandscapeCommandName );
	commandsRegistry->unregisterCommand( Resources::Commands::OpenLandscapeCommandName );
	commandsRegistry->unregisterCommand( Resources::Commands::NewLandscapeCommandName );

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


boost::intrusive_ptr< Framework::GUI::ImagesManager::IImagesManager >
PluginInstance::getImagesManager() const
{
	return
		getPluginInterface< Framework::GUI::ImagesManager::IImagesManager >(
				Framework::GUI::ImagesManager::PID_IMAGES_MANAGER
			,	Framework::GUI::ImagesManager::IID_IMAGES_MANAGER );

} // PluginInstance::getImageManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< MinimapViewer::IMinimapViewer >
PluginInstance::getMinimapViewer() const
{
	return
		getPluginInterface< MinimapViewer::IMinimapViewer >(
				MinimapViewer::PID_MINIMAP_VIEWER
			,	MinimapViewer::IID_MINIMAP_VIEWER );

} // PluginInstance::getMinimapViewer


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


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItemsCache >
PluginInstance::getSurfaceItemsCache() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::ISurfaceItemsCache >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_SURFACE_ITEMS_CACHE );

} // PluginInstance::getSurfaceItemsCache


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBaseView >
PluginInstance::getObjectsView() const
{
	return m_objectsView;

} // PluginInstance::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IEditorView >
PluginInstance::getEditorView() const
{
	return m_editorView;

} // PluginInstance::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IBaseView >
PluginInstance::getDescriptionView() const
{
	return m_descriptionView;

} // PluginInstance::getObjectsView


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeEditorInternal >
PluginInstance::getGUILandscapeEditor() const
{
	return m_landscapeEditor;

} // PluginInstance::getGUILandscapeEditor


/*---------------------------------------------------------------------------*/


void
PluginInstance::fillSurfaceItemsCache()
{
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItemsCache >
		surfaceItemsCache = getSurfaceItemsCache();

	unsigned int counter = 0;

	for ( int i = 0; i < 24; ++i )
	{
		for ( int j = 0; j < 16; ++j )
		{
			surfaceItemsCache->addSurfaceItem(
					counter++
				,	"surface/summer"
				,	QRect(
						j * Resources::Landscape::CellSize
					,	i * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize ) );
		}
	}

	for ( int i = 0; i < 24; ++i )
	{
		for ( int j = 0; j < 16; ++j )
		{
			surfaceItemsCache->addSurfaceItem(
					counter++
				,	"surface/winter"
				,	QRect(
						j * Resources::Landscape::CellSize
					,	i * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize ) );
		}
	}

	for ( int i = 0; i < 24; ++i )
	{
		for ( int j = 0; j < 16; ++j )
		{
			surfaceItemsCache->addSurfaceItem(
					counter++
				,	"surface/wasteland"
				,	QRect(
						j * Resources::Landscape::CellSize
					,	i * Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize
					,	Resources::Landscape::CellSize ) );
		}
	}

	surfaceItemsCache->setDefaultSurfaceItem( surfaceItemsCache->getSurfaceItem( 269 ) );

} // PluginInstance::fillSurfaceItemsCache


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
