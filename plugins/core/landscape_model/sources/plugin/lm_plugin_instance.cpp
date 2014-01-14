
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/plugin/lm_plugin_instance.hpp"

#include "messenger/ms_imessenger.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "multithreading_manager/h/mm_plugin_id.hpp"

#include "event_manager/ih/em_ievent_manager.hpp"
#include "event_manager/h/em_plugin_id.hpp"

#include "script_engine/ih/se_iexporter.hpp"
#include "script_engine/ih/se_iscripts_executor.hpp"
#include "script_engine/h/se_plugin_id.hpp"
#include "script_engine/h/se_resources.hpp"

#include "landscape_model/sources/environment/lm_environment.hpp"
#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"
#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"
#include "landscape_model/sources/surface_items_cache/lm_surface_items_cache.hpp"
#include "landscape_model/sources/static_data/lm_static_data.hpp"

#include "landscape_model/sources/surface_item/lm_surface_item.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/sources/notification_center/lm_notification_center.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_LANDSCAPE_MODEL, m_landscapeModel.get() )
	INTERFACE_DECLARATION( IID_SURFACE_ITEMS_CACHE, m_surfaceItemsCache.get() )
	INTERFACE_DECLARATION( IID_STATIC_DATA, m_staticData.get() )

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
	m_notificationCenter.reset( new NotificationCenter() );
	m_staticData.reset( new StaticData() );
	m_surfaceItemsCache.reset( new SurfaceItemsCache() );
	m_landscapeSerializer.reset( new LandscapeSerializer() );
	m_landscapeModel.reset( new LandscapeModel( *m_environment, *m_landscapeSerializer, *m_surfaceItemsCache, *m_staticData ) );

	exportScriptAPI();
	executeConfigurationScripts();

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_landscapeModel.reset();
	m_landscapeSerializer.reset();
	m_surfaceItemsCache.reset();
	m_staticData.reset();
	m_notificationCenter.reset();
	m_environment.reset();

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


boost::intrusive_ptr< Framework::Core::MultithreadingManager::IMultithreadingManager >
PluginInstance::getMultithreadingManager() const
{
	return
		getPluginInterface< Framework::Core::MultithreadingManager::IMultithreadingManager >(
				Framework::Core::MultithreadingManager::PID_MULTITHREADING_MANAGER
			,	Framework::Core::MultithreadingManager::IID_MULTITHREADING_MANAGER );

} // PluginInstance::getMultithreadingManager


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


boost::intrusive_ptr< INotificationCenter >
PluginInstance::getNotificationCenter() const
{
	return m_notificationCenter;

} // PluginInstance::getNotificationCenter


/*---------------------------------------------------------------------------*/


void
PluginInstance::exportScriptAPI()
{
	Framework::Core::ScriptEngine::DataExporter exporter = getScriptExporter()->getDataExporter();

	// Enums export

	exporter.exportClass< TerrainMapItem >( "TerrainMapItem" )
		->withEnum< TerrainMapItem::Enum >( "Enum" )
			.withItem( "NotAvailable", TerrainMapItem::NotAvailable )
			.withItem( "Ground", TerrainMapItem::Ground )
			.withItem( "Water", TerrainMapItem::Water );

	exporter.exportClass< Actions >( "Actions" )
		->withEnum< Actions::Enum >( "Enum" )
			.withItem( "Move", Actions::Move )
			.withItem( "Build", Actions::Build )
			.withItem( "GenerateResources", Actions::GenerateResources )
			.withItem( "Attack", Actions::Attack );

	exporter.exportClass< ObjectState >( "ObjectState" )
		->withEnum< ObjectState::Enum >( "Enum" )
			.withItem( "Standing", ObjectState::Standing )
			.withItem( "Moving", ObjectState::Moving )
			.withItem( "Attacking", ObjectState::Attacking )
			.withItem( "Building", ObjectState::Building );

	exporter.exportClass< Direction >( "Direction" )
		->withEnum< Direction::Enum >( "Enum" )
			.withItem( "Up", Direction::Up )
			.withItem( "Down", Direction::Down )
			.withItem( "Left", Direction::Left )
			.withItem( "Right", Direction::Right );

	// Surface items cache export

	exporter.exportClass< ISurfaceItemsCache >( "ISurfaceItemsCache" )
		->withMethod( "regSurfaceItem", &ISurfaceItemsCache::regSurfaceItem )
		.withMethod( "setDefaultSurfaceItem", &ISurfaceItemsCache::setDefaultSurfaceItem );

	exporter.exportVariable( "SurfaceItemsCache", m_surfaceItemsCache.get() );

	// Static data export

	exporter.exportClassWithShared< ResourcesData >( "ResourcesData" )
		->withConstructor()
		.withMethod( "pushResource", &ResourcesData::pushResource );

	exporter.exportClassWithShared< BuildObjectData >( "BuildObjectData" )
		->withConstructor< const int, const ResourcesData& >();

	exporter.exportClassWithShared< BuilderComponentStaticData >( "BuilderComponentStaticData" )
		->withConstructor()
		.withMethod( "pushBuildObjectData", &BuilderComponentStaticData::pushBuildObjectData );

	exporter.exportClassWithShared< HealthComponentStaticData >( "HealthComponentStaticData" )
		->withConstructor< const int >();

	exporter.exportClassWithShared< LocateComponentStaticData >( "LocateComponentStaticData" )
		->withConstructor< const QSize&, const TerrainMapItem::MaskType >();

	exporter.exportClassWithShared< SelectionComponentStaticData >( "SelectionComponentStaticData" )
		->withConstructor< const bool >();

	exporter.exportClassWithShared< ActionsComponentStaticData >( "ActionsComponentStaticData" )
		->withConstructor()
		.withMethod( "can", &ActionsComponentStaticData::can );

	exporter.exportClassWithShared< MoveComponentStaticData >( "MoveComponentStaticData" )
		->withConstructor< const unsigned int >();

	exporter.exportClassWithShared< AttackComponentStaticData >( "AttackComponentStaticData" )
		->withConstructor< const unsigned int, const unsigned int, const unsigned int >();

	exporter.exportClassWithShared< GenerateResourcesComponentStaticData >( "GenerateResourcesComponentStaticData" )
		->withConstructor()
		.withMethod( "canGenerate", &GenerateResourcesComponentStaticData::canGenerate );

	exporter.exportClass< IStaticData::ObjectStaticData >( "ObjectStaticData" )
		->withConstructor()
		.withRWProperty( "m_actionsData", &IStaticData::ObjectStaticData::m_actionsData )
		.withRWProperty( "m_builderData", &IStaticData::ObjectStaticData::m_builderData )
		.withRWProperty( "m_healthData", &IStaticData::ObjectStaticData::m_healthData )
		.withRWProperty( "m_locateData", &IStaticData::ObjectStaticData::m_locateData )
		.withRWProperty( "m_moveData", &IStaticData::ObjectStaticData::m_moveData )
		.withRWProperty( "m_selectionData", &IStaticData::ObjectStaticData::m_selectionData )
		.withRWProperty( "m_generateResourcesData", &IStaticData::ObjectStaticData::m_generateResourcesData )
		.withRWProperty( "m_attackData", &IStaticData::ObjectStaticData::m_attackData );

	exporter.exportClass< IStaticData >( "IStaticData" )
		->withMethod( "regObjectStaticData", &IStaticData::regObjectStaticData )
		.withMethod( "regResource", &IStaticData::regResource );

	exporter.exportVariable( "StaticData", m_staticData.get() );

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

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
