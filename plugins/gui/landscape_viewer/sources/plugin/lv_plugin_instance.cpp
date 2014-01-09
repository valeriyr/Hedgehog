
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"

#include "messenger/ms_imessenger.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_landscape_viewer.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"

#include "landscape_viewer/sources/commands/lv_commands.hpp"
#include "landscape_viewer/sources/commands_executor/lv_commands_executor.hpp"

#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/h/wm_plugin_id.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_istatic_data.hpp"
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
	fillObjectsCache();

	m_graphicsInfoCache.reset( new GraphicsInfoCache() );
	fillSurfaceItemsCache();

	getSettings()->regBool( Resources::Properties::TerrainMapVisibility, false );
	getSettings()->regString( Resources::Properties::SkinId, "winter" );

	m_environment.reset( new Environment( *this ) );

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

	getWindowManager()->addCommandToMenu( "File/New", Resources::Commands::NewLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Open", Resources::Commands::OpenLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Close", Resources::Commands::CloseLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Save", Resources::Commands::SaveLandscapeCommandName );
	getWindowManager()->addCommandToMenu( "File/Save As", Resources::Commands::SaveAsLandscapeCommandName );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
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

	m_commandsExecutor.reset();
	m_landscapeViewer.reset();
	m_environment.reset();

	getSettings()->unregProperty( Resources::Properties::SkinId );
	getSettings()->unregProperty( Resources::Properties::TerrainMapVisibility );

	m_graphicsInfoCache.reset();

	clearObjectsCache();

} // PluginInstance::close


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


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeModel >
PluginInstance::getLandscapeModel() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::ILandscapeModel >(
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

	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 1, "surface", QRect( 352, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 2, "surface", QRect( 128, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 3, "surface", QRect( 128, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 4, "surface", QRect( 256, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 5, "surface", QRect( 384, 384, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 6, "surface", QRect(  32, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 7, "surface", QRect( 256, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 8, "surface", QRect( 160, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 9, "surface", QRect( 352, 448, 32, 32 ) );

	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 1, "surface", QRect(  64, 544, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 2, "surface", QRect( 224, 512, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 3, "surface", QRect( 352, 544, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 4, "surface", QRect( 416, 512, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 5, "surface", QRect(  64, 512, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 6, "surface", QRect( 224, 544, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 7, "surface", QRect(   0, 576, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 8, "surface", QRect( 448, 544, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 9, "surface", QRect(  64, 576, 32, 32 ) );

	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 1, "surface", QRect( 192, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 2, "surface", QRect( 416, 384, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 3, "surface", QRect( 448, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 4, "surface", QRect(  96, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 5, "surface", QRect(  32, 352, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 6, "surface", QRect( 384, 416, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 7, "surface", QRect(  96, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 8, "surface", QRect(   0, 448, 32, 32 ) );
	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 9, "surface", QRect( 160, 448, 32, 32 ) );

	// Water tiles

	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "summer", 101, "surface", QRect( 256, 640, 32, 32 ) );

	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "winter", 101, "surface", QRect( 352, 640, 32, 32 ) );

	m_graphicsInfoCache->regSurfaceItemGraphicsInfo( "wasteland", 101, "surface", QRect( 0, 608, 32, 32 ) );

} // PluginInstance::fillSurfaceItemsCache


/*---------------------------------------------------------------------------*/


void
PluginInstance::fillObjectsCache()
{
	boost::intrusive_ptr< Framework::GUI::AnimationManager::IAnimationsCache >
		animationsCache = getAnimationsCache();

	// Grant graphic info

	{
		// Grant standing up animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Grunt"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Up ) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 0, 0, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/grunt", animationFrames ) );
	}

	{
		// Grant standing down animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Grunt"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Down) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 288, 0, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/grunt", animationFrames ) );
	}

	{
		// Grant standing left animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Grunt"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Left) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 144, 0, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/grunt", animationFrames ) );
	}

	{
		// Grant standing right animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Grunt"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Right) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 144, 0, 72, 72 ), true ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/grunt", animationFrames ) );
	}

	{
		// Grant moving up animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Grunt"
				,	Core::LandscapeModel::ObjectState::Moving
				,	Core::LandscapeModel::Direction::Up ) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0,  72, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0, 144, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0, 216, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0, 288, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/grunt", animationFrames ) );
	}

	{
		// Grant moving down animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Grunt"
				,	Core::LandscapeModel::ObjectState::Moving
				,	Core::LandscapeModel::Direction::Down) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288,  72, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288, 144, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288, 216, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288, 288, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/grunt", animationFrames ) );
	}

	{
		// Grant moving left animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Grunt"
				,	Core::LandscapeModel::ObjectState::Moving
				,	Core::LandscapeModel::Direction::Left) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144,  72, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 144, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 216, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 288, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/grunt", animationFrames ) );
	}

	{
		// Grant moving right animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Grunt"
				,	Core::LandscapeModel::ObjectState::Moving
				,	Core::LandscapeModel::Direction::Right) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144,  72, 72, 72 ), true ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 144, 72, 72 ), true ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 216, 72, 72 ), true ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 288, 72, 72 ), true ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/grunt", animationFrames ) );
	}

	// Elven Archer graphic info

	{
		// Elven Archer standing up animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Elven Archer"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Up ) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 0, 0, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/elven_archer", animationFrames ) );
	}

	{
		// Elven Archer standing down animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Elven Archer"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Down) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 288, 0, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/elven_archer", animationFrames ) );
	}

	{
		// Elven Archer standing left animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Elven Archer"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Left) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 144, 0, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/elven_archer", animationFrames ) );
	}

	{
		// Elven Archer standing right animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Elven Archer"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Right) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 144, 0, 72, 72 ), true ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/elven_archer", animationFrames ) );
	}

	{
		// Elven Archer moving up animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Elven Archer"
				,	Core::LandscapeModel::ObjectState::Moving
				,	Core::LandscapeModel::Direction::Up ) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0,   0, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0,  72, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0, 144, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0, 216, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 0, 288, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/elven_archer", animationFrames ) );
	}

	{
		// Elven Archer moving down animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Elven Archer"
				,	Core::LandscapeModel::ObjectState::Moving
				,	Core::LandscapeModel::Direction::Down) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288,   0, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288,  72, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288, 144, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288, 216, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 288, 288, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/elven_archer", animationFrames ) );
	}

	{
		// Elven Archer moving left animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Elven Archer"
				,	Core::LandscapeModel::ObjectState::Moving
				,	Core::LandscapeModel::Direction::Left) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144,   0, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144,  72, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 144, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 216, 72, 72 ) ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 288, 72, 72 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/elven_archer", animationFrames ) );
	}

	{
		// Elven Archer moving right animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Elven Archer"
				,	Core::LandscapeModel::ObjectState::Moving
				,	Core::LandscapeModel::Direction::Right) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144,   0, 72, 72 ), true ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144,  72, 72, 72 ), true ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 144, 72, 72 ), true ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 216, 72, 72 ), true ) );
		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100, QRect( 144, 288, 72, 72 ), true ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "units/elven_archer", animationFrames ) );
	}

	// Orc Barracks

	{
		// Orc Barracks standing down animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Orc Barracks"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Down) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 0, 0, 92, 92 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "buildings/orc/barracks", animationFrames ) );
	}

	{
		// Orc Barracks standing down animation ( winter skin )
		QString animationName(
			generateAnimationName(
					"winter"
				,	"Orc Barracks"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Down) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 0, 0, 92, 92 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "skins/winter/orc/barracks", animationFrames ) );
	}

	// Human Barracks

	{
		// Human Barracks standing down animation
		QString animationName(
			generateAnimationName(
					IGraphicsInfoCache::ms_anySkinIdentifier
				,	"Human Barracks"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Down) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 0, 0, 92, 92 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "buildings/human/barracks", animationFrames ) );
	}

	{
		// Human Barracks standing down animation ( winter skin )
		QString animationName(
			generateAnimationName(
					"winter"
				,	"Human Barracks"
				,	Core::LandscapeModel::ObjectState::Standing
				,	Core::LandscapeModel::Direction::Down) );

		Framework::GUI::AnimationManager::AnimationInfo::FramesCollection animationFrames;

		animationFrames.push_back( Framework::GUI::AnimationManager::FrameInfo( 100000, QRect( 0, 0, 92, 92 ) ) );

		animationsCache->regAnimation( Framework::GUI::AnimationManager::AnimationInfo( animationName, "skins/winter/human/barracks", animationFrames ) );
	}

} // PluginInstance::fillObjectsCache


/*---------------------------------------------------------------------------*/


void
PluginInstance::clearObjectsCache()
{
	boost::intrusive_ptr< Framework::GUI::AnimationManager::IAnimationsCache >
		animationsCache = getAnimationsCache();

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Grunt"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Up ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Grunt"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Down ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Grunt"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Left ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Grunt"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Right ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Grunt"
			,	Core::LandscapeModel::ObjectState::Moving
			,	Core::LandscapeModel::Direction::Up ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Grunt"
			,	Core::LandscapeModel::ObjectState::Moving
			,	Core::LandscapeModel::Direction::Down ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Grunt"
			,	Core::LandscapeModel::ObjectState::Moving
			,	Core::LandscapeModel::Direction::Left ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Grunt"
			,	Core::LandscapeModel::ObjectState::Moving
			,	Core::LandscapeModel::Direction::Right ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Elven Archer"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Up ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Elven Archer"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Down ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Elven Archer"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Left ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Elven Archer"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Right ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Elven Archer"
			,	Core::LandscapeModel::ObjectState::Moving
			,	Core::LandscapeModel::Direction::Up ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Elven Archer"
			,	Core::LandscapeModel::ObjectState::Moving
			,	Core::LandscapeModel::Direction::Down ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Elven Archer"
			,	Core::LandscapeModel::ObjectState::Moving
			,	Core::LandscapeModel::Direction::Left ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Elven Archer"
			,	Core::LandscapeModel::ObjectState::Moving
			,	Core::LandscapeModel::Direction::Right ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Orc Barracks"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Down ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				"winter"
			,	"Orc Barracks"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Down ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				IGraphicsInfoCache::ms_anySkinIdentifier
			,	"Human Barracks"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Down ) );

	animationsCache->unregAnimation(
		generateAnimationName(
				"winter"
			,	"Human Barracks"
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Down ) );

} // PluginInstance::clearObjectsCache


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
