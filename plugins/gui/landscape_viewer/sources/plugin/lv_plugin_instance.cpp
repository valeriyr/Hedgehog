
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"

#include "messenger/ms_imessenger.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_landscape_viewer.hpp"
#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"
#include "landscape_viewer/sources/commands/lv_commands.hpp"
#include "landscape_viewer/sources/commands_executor/lv_commands_executor.hpp"
#include "landscape_viewer/sources/graphics_info/lv_graphics_info.hpp"
#include "landscape_viewer/sources/map_preview_generator/lv_map_preview_generator.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_istatic_data.hpp"
#include "landscape_model/ih/lm_imodel_information.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/h/lm_plugin_id.hpp"

#include "commands_manager/ih/cm_icommands_registry.hpp"
#include "commands_manager/h/cm_plugin_id.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"
#include "images_manager/h/im_plugin_id.hpp"

#include "animation_manager/ih/am_ianimation_manager.hpp"
#include "animation_manager/ih/am_ianimations_cache.hpp"
#include "animation_manager/h/am_plugin_id.hpp"
#include "animation_manager/h/am_animation_info.hpp"

#include "settings/ih/st_isettings.hpp"
#include "settings/h/st_plugin_id.hpp"

#include "event_manager/ih/em_ievent_manager.hpp"
#include "event_manager/h/em_plugin_id.hpp"

#include "multithreading_manager/h/mm_plugin_id.hpp"
#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"

#include "sound_manager/ih/sm_isound_manager.hpp"
#include "sound_manager/h/sm_plugin_id.hpp"

#include "script_engine/ih/se_iexporter.hpp"
#include "script_engine/ih/se_iscripts_executor.hpp"
#include "script_engine/h/se_plugin_id.hpp"
#include "script_engine/h/se_resources.hpp"

#include "network_manager/h/nm_resources.hpp"

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
	// Force loading of the sound manager. Needs to use it's properties.
	getSoundManager();

	m_graphicsInfo.reset( new GraphicsInfo() );

	exportScriptAPI();
	executeConfigurationScripts();

	getSettings()->regBool( Resources::Properties::TerrainMapVisibility, false );
	getSettings()->regString( Resources::Properties::SkinId, "winter" );
	getSettings()->regBool( Resources::Properties::UpdateMinimap, true );
	getSettings()->regUInt( Resources::Properties::Port, 1988 );
	getSettings()->regString( Resources::Properties::Ip, Framework::Core::NetworkManager::Resources::LocalHost );

	m_environment.reset( new Environment( *this ) );
	m_mapPreviewGenerator.reset( new MapPreviewGenerator( *m_environment ) );
	m_landscapeViewer.reset( new LandscapeViewer( *m_environment ) );
	m_commandsExecutor.reset( new CommandsExecutor( *m_environment, *m_landscapeViewer ) );

	using namespace Framework::Core::CommandsManager;

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

	getCommandsManager()->registerCommand(
			Resources::Commands::StartMultiplayerGameCommandName
		,	boost::intrusive_ptr< ICommand >( new StartMultiplayerGameCommand( *m_commandsExecutor ) ) );

	getWindowManager()->addCommandToMenu( "File/New", Resources::Commands::NewLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Open", Resources::Commands::OpenLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Close", Resources::Commands::CloseLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Save", Resources::Commands::SaveLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Save As", Resources::Commands::SaveAsLandscapeCommandName );

	getWindowManager()->addCommandToMenu( "Multiplayer/Start", Resources::Commands::StartMultiplayerGameCommandName );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	getWindowManager()->removeCommandFromMenu( "Multiplayer/Start" );

	getWindowManager()->removeCommandFromMenu( "File/Save As" );
	getWindowManager()->removeCommandFromMenu( "File/Save" );
	getWindowManager()->removeCommandFromMenu( "File/Close" );
	getWindowManager()->removeCommandFromMenu( "File/Open" );
	getWindowManager()->removeCommandFromMenu( "File/New" );

	getCommandsManager()->unregisterCommand( Resources::Commands::StartMultiplayerGameCommandName );

	getCommandsManager()->unregisterCommand( Resources::Commands::SaveAsLandscapeCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::SaveLandscapeCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::CloseLandscapeCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::OpenLandscapeCommandName );
	getCommandsManager()->unregisterCommand( Resources::Commands::NewLandscapeCommandName );

	m_commandsExecutor.reset();
	m_landscapeViewer.reset();
	m_mapPreviewGenerator.reset();
	m_environment.reset();

	getSettings()->unregProperty( Resources::Properties::SkinId );
	getSettings()->unregProperty( Resources::Properties::TerrainMapVisibility );
	getSettings()->unregProperty( Resources::Properties::UpdateMinimap );
	getSettings()->unregProperty( Resources::Properties::Port );
	getSettings()->unregProperty( Resources::Properties::Ip );

	m_graphicsInfo.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::PluginsManager::ISystemInformation >
PluginInstance::getSystemInformation() const
{
	return
		getPluginInterface< Framework::Core::PluginsManager::ISystemInformation >(
				Framework::Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Framework::Core::PluginsManager::IID_SYSTEM_INFORMATION );

} // PluginInstance::getSystemInformation


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Tools::Core::IMessenger >
PluginInstance::getSystemMessenger() const
{
	return
		getPluginInterface< Tools::Core::IMessenger >(
				Framework::Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Tools::Core::IID_MESSENGER );

} // PluginInstance::getSystemMessenger


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


boost::intrusive_ptr< Framework::GUI::AnimationManager::IAnimationManager >
PluginInstance::getAnimationManager() const
{
	return
		getPluginInterface< Framework::GUI::AnimationManager::IAnimationManager >(
				Framework::GUI::AnimationManager::PID_ANIMATION_MANAGER
			,	Framework::GUI::AnimationManager::IID_ANIMATION_MANAGER );

} // PluginInstance::getAnimationManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::GUI::AnimationManager::IAnimationsCache >
PluginInstance::getAnimationsCache() const
{
	return
		getPluginInterface< Framework::GUI::AnimationManager::IAnimationsCache >(
				Framework::GUI::AnimationManager::PID_ANIMATION_MANAGER
			,	Framework::GUI::AnimationManager::IID_ANIMATIONS_CACHE );

} // PluginInstance::getAnimationsCache


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


boost::intrusive_ptr< Framework::Core::EventManager::IEventManager >
PluginInstance::getEventManager() const
{
	return
		getPluginInterface< Framework::Core::EventManager::IEventManager >(
				Framework::Core::EventManager::PID_EVENT_MANAGER
			,	Framework::Core::EventManager::IID_EVENT_MANAGER );

} // PluginInstance::getEventManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Plugins::Core::LandscapeModel::IModelLocker >
PluginInstance::getModelLocker() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::IModelLocker >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_LANDSCAPE_MODEL );

} // PluginInstance::getLandscapeModel


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::MultithreadingManager::IMultithreadingManager >
PluginInstance::getMultithreadingManager() const
{
	return
		getPluginInterface< Framework::Core::MultithreadingManager::IMultithreadingManager >(
				Framework::Core::MultithreadingManager::PID_MULTITHREADING_MANAGER
			,	Framework::Core::MultithreadingManager::IID_MULTITHREADING_MANAGER );

} // PluginInstance::getMultithreadingManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::SoundManager::ISoundManager >
PluginInstance::getSoundManager() const
{
	return
		getPluginInterface< Framework::Core::SoundManager::ISoundManager >(
				Framework::Core::SoundManager::PID_SOUND_MANAGER
			,	Framework::Core::SoundManager::IID_SOUND_MANAGER );

} // PluginInstance::getSoundManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::ScriptEngine::IExporter >
PluginInstance::getScriptExporter() const
{
	return
		getPluginInterface< Framework::Core::ScriptEngine::IExporter >(
				Framework::Core::ScriptEngine::PID_SCRIPT_ENGINE
			,	Framework::Core::ScriptEngine::IID_EXPORTER );

} // PluginInstance::getScriptExporter


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Framework::Core::ScriptEngine::IScriptsExecutor >
PluginInstance::getScriptsExecutor() const
{
	return
		getPluginInterface< Framework::Core::ScriptEngine::IScriptsExecutor >(
				Framework::Core::ScriptEngine::PID_SCRIPT_ENGINE
			,	Framework::Core::ScriptEngine::IID_SCRIPTS_EXECUTOR );

} // PluginInstance::getScriptsExecutor


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


boost::intrusive_ptr< Plugins::Core::LandscapeModel::IStaticData >
PluginInstance::getStaticData() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::IStaticData >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_STATIC_DATA );

} // PluginInstance::getStaticData


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Plugins::Core::LandscapeModel::IModelInformation >
PluginInstance::getModelInformation() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::IModelInformation >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_MODEL_INFORMATION );

} // PluginInstance::getModelInformation


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IGraphicsInfo >
PluginInstance::getGraphicsInfo() const
{
	return m_graphicsInfo;

} // PluginInstance::getGraphicsInfo


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IMapPreviewGenerator >
PluginInstance::getMapPreviewGenerator() const
{
	return m_mapPreviewGenerator;

} // PluginInstance::getMapPreviewGenerator


/*---------------------------------------------------------------------------*/


void
PluginInstance::exportScriptAPI()
{
	Framework::Core::ScriptEngine::DataExporter exporter = getScriptExporter()->getDataExporter();

	// Graphics info cache

	exporter.exportClass< QColor >( "QColor" )
		->withConstructor< int, int, int >();

	// Graphics info cache

	exporter.exportClass< IGraphicsInfo >( "IGraphicsInfo" )
		->withMethod( "regSurfaceItemGraphicsInfo", &IGraphicsInfo::regSurfaceItemGraphicsInfo )
		.withMethod( "regPossiblePlayersColor", &IGraphicsInfo::regPossiblePlayersColor );

	exporter.exportVariable( "GraphicsInfo", m_graphicsInfo.get() );

	// Helpers

	exporter.exportFunction( "generateAnimationName", &generateAnimationName );

	exporter.exportVariable( "AnySkinIdentifier", &IGraphicsInfo::ms_anySkinIdentifier );

} // PluginInstance::exportScriptAPI


/*---------------------------------------------------------------------------*/


void
PluginInstance::executeConfigurationScripts()
{
	QDir scriptsDirectory = QDir( getSystemInformation()->getConfigDirectory() + "/" + Resources::ConfigurationScriptsDirectory );

	if ( !scriptsDirectory.exists() )
		return;

	QStringList filesFilter;
	filesFilter.push_back( QString( "*" ) + Framework::Core::ScriptEngine::Resources::ScriptFileExtension );

	QFileInfoList filesList = scriptsDirectory.entryInfoList( filesFilter );

	for ( int i = 0; i < filesList.size(); ++i )
	{
		 getScriptsExecutor()->executeFile( filesList.at( i ).filePath() );
	}

} // PluginInstance::executeConfigurationScripts


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
