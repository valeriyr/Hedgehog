
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_landscape_viewer.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/commands/lv_commands.hpp"
#include "landscape_viewer/sources/commands_executor/lv_commands_executor.hpp"

#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/h/lm_plugin_id.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "commands_manager/h/cm_plugin_id.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"
#include "images_manager/h/im_plugin_id.hpp"

#include "settings/ih/st_isettings.hpp"
#include "settings/h/st_plugin_id.hpp"


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
	m_graphicsInfoCache.reset( new GraphicsInfoCache() );

	fillSurfaceItemsCache();
	fillUnitsCache();

	getSettings()->regBool( Resources::Properties::TerrainMapVisibility, false );

	m_environment.reset( new Environment( *this ) );
	m_landscapeViewer.reset( new LandscapeViewer( *m_environment ) );

	m_commandsExecutor.reset( new CommandsExecutor( *m_environment, *m_landscapeViewer ) );

	using namespace Framework::Core::CommandsManager;
	getCommandsManager()->registerCommand(
			Resources::Commands::RunGameCommandName
		,	boost::intrusive_ptr< ICommand >( new RunGameCommand( *m_commandsExecutor ) ) );
	getCommandsManager()->registerCommand(
			Resources::Commands::StopGameCommandName
		,	boost::intrusive_ptr< ICommand >( new StopGameCommand( *m_commandsExecutor ) ) );
	getCommandsManager()->registerCommand(
			Resources::Commands::NewLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new NewLandscapeCommand( *m_commandsExecutor ) ) );
	getCommandsManager()->registerCommand(
			Resources::Commands::OpenLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new OpenLandscapeCommand( *m_commandsExecutor ) ) );
	getCommandsManager()->registerCommand(
			Resources::Commands::CloseLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new CloseLandscapeCommand( *m_commandsExecutor ) ) );
	getCommandsManager()->registerCommand(
			Resources::Commands::SaveLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new SaveLandscapeCommand( *m_commandsExecutor ) ) );
	getCommandsManager()->registerCommand(
			Resources::Commands::SaveAsLandscapeCommandName
		,	boost::intrusive_ptr< ICommand >( new SaveAsLandscapeCommand( *m_commandsExecutor ) ) );

	getWindowManager()->addCommandToMenu( "File/New", Resources::Commands::NewLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Open", Resources::Commands::OpenLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Close", Resources::Commands::CloseLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Save", Resources::Commands::SaveLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Save As", Resources::Commands::SaveAsLandscapeCommandName );

	getWindowManager()->addCommandToMenu( "Game/Run", Resources::Commands::RunGameCommandName );
	getWindowManager()->addCommandToMenu( "Game/Stop", Resources::Commands::StopGameCommandName );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	getWindowManager()->removeCommandFromMenu( "Game/Stop" );
	getWindowManager()->removeCommandFromMenu( "Game/Run" );

	getWindowManager()->removeCommandFromMenu( "File/Save As" );
	getWindowManager()->removeCommandFromMenu( "File/Save" );
	getWindowManager()->removeCommandFromMenu( "File/Close" );
	getWindowManager()->removeCommandFromMenu( "File/Open" );
	getWindowManager()->removeCommandFromMenu( "File/New" );

	getCommandsManager()->unregisterCommand( Resources::Commands::SaveAsLandscapeCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::SaveLandscapeCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::CloseLandscapeCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::OpenLandscapeCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::NewLandscapeCommandName );

	getCommandsManager()->unregisterCommand( Resources::Commands::StopGameCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::RunGameCommandName );

	m_commandsExecutor.reset();
	m_landscapeViewer.reset();
	m_environment.reset();

	getSettings()->unregProperty( Resources::Properties::TerrainMapVisibility );

	m_graphicsInfoCache.reset();

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


boost::intrusive_ptr< Framework::Core::CommandsManager::ICommandsRegistry >
PluginInstance::getCommandsManager() const
{
	return
		getPluginInterface< Framework::Core::CommandsManager::ICommandsRegistry >(
				Framework::Core::CommandsManager::PID_COMMANDS_MANAGER
			,	Framework::Core::CommandsManager::IID_COMMANDS_REGISTRY );

} // PluginInstance::getCommandsManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::Settings::ISettings >
PluginInstance::getSettings() const
{
	return
		getPluginInterface< Framework::Core::Settings::ISettings >(
				Framework::Core::Settings::PID_SETTINGS
			,	Framework::Core::Settings::IID_SETTINGS );

} // PluginInstance::getSettings


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeModel >
PluginInstance::getLandscapeModel() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::ILandscapeModel >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_LANDSCAPE_MODEL );

} // PluginInstance::getLandscapeModel


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


boost::intrusive_ptr< IGraphicsInfoCache >
PluginInstance::getGraphicsInfoCache() const
{
	return m_graphicsInfoCache;

} // PluginInstance::getGraphicsInfoCache


/*---------------------------------------------------------------------------*/


void
PluginInstance::fillSurfaceItemsCache()
{
	// Ground tiles with water borders

	// 1 --- 2 --- 3
	// |     |     |
	// 4 --- 5 --- 6
	// |     |     |
	// 7 --- 8 --- 9

	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 1, "surface/summer", QRect( 352, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 2, "surface/summer", QRect( 128, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 3, "surface/summer", QRect( 128, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 4, "surface/summer", QRect( 256, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 5, "surface/summer", QRect( 384, 384, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 6, "surface/summer", QRect( 32, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 7, "surface/summer", QRect( 256, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 8, "surface/summer", QRect( 160, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 9, "surface/summer", QRect( 352, 448, 32, 32 ) );

	// Water tiles

	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 101, "surface/summer", QRect( 256, 640, 32, 32 ) );

} // PluginInstance::fillSurfaceItemsCache


/*---------------------------------------------------------------------------*/


void
PluginInstance::fillUnitsCache()
{
	m_graphicsInfoCache->regObjectGraphicsInfo(
			GraphicsInfoCache::ms_anySkinIdentifier
		,	"Grunt"
		,	"units/grunt"
		,	QRect( 288, 0, 72, 72 ) );

	m_graphicsInfoCache->regObjectGraphicsInfo(
			GraphicsInfoCache::ms_anySkinIdentifier
		,	"Elven Archer"
		,	"units/elven_archer"
		,	QRect( 648, 0, 72, 72 ) );

} // PluginInstance::fillUnitsCache


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
