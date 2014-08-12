
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
#include "landscape_model/sources/model_locker/lm_model_locker.hpp"
#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"
#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"
#include "landscape_model/sources/surface_items_cache/lm_surface_items_cache.hpp"
#include "landscape_model/sources/static_data/lm_static_data.hpp"
#include "landscape_model/sources/model_information/lm_model_information.hpp"

#include "landscape_model/sources/surface_item/lm_surface_item.hpp"

#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "landscape_model/sources/notification_center/lm_notification_center.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_LANDSCAPE_MODEL, getLandscapeModelLocker() )
	INTERFACE_DECLARATION( IID_SURFACE_ITEMS_CACHE, m_surfaceItemsCache )
	INTERFACE_DECLARATION( IID_STATIC_DATA, m_staticData )
	INTERFACE_DECLARATION( IID_MODEL_INFORMATION, m_modelInformation )

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
	m_modelInformation.reset( new ModelInformation( *m_environment ) );
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
	m_modelInformation.reset();
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

	exporter.exportVariable( "AnyTerrain", TerrainMapItem::ms_any );

	exporter.exportClass< TerrainMapItem >( "TerrainMapItem" )
		->withEnum< TerrainMapItem::Enum >( "Enum" )
			.withItem( "NotAvailable", TerrainMapItem::NotAvailable )
			.withItem( "Ground", TerrainMapItem::Ground )
			.withItem( "Water", TerrainMapItem::Water );

	exporter.exportClass< Emplacement >( "Emplacement" )
		->withEnum< Emplacement::Enum >( "Enum" )
			.withItem( "Ground", Emplacement::Ground )
			.withItem( "Air", Emplacement::Air);

	exporter.exportClass< ObjectState >( "ObjectState" )
		->withEnum< ObjectState::Enum >( "Enum" )
			.withItem( "Standing", ObjectState::Standing )
			.withItem( "Moving", ObjectState::Moving )
			.withItem( "Attacking", ObjectState::Attacking )
			.withItem( "Training", ObjectState::Training )
			.withItem( "Building", ObjectState::Building )
			.withItem( "Repairing", ObjectState::Repairing )
			.withItem( "Collecting", ObjectState::Collecting )
			.withItem( "Dying", ObjectState::Dying )
			.withItem( "UnderConstruction", ObjectState::UnderConstruction )
			.withItem( "UnderCollecting", ObjectState::UnderCollecting );

	exporter.exportClass< Direction >( "Direction" )
		->withEnum< Direction::Enum >( "Enum" )
			.withItem( "North", Direction::North )
			.withItem( "NorthEast", Direction::NorthEast )
			.withItem( "East", Direction::East )
			.withItem( "SouthEast", Direction::SouthEast )
			.withItem( "South", Direction::South )
			.withItem( "SouthWest", Direction::SouthWest )
			.withItem( "West", Direction::West )
			.withItem( "NorthWest", Direction::NorthWest );

	// Surface items cache export

	exporter.exportClass< ISurfaceItemsCache >( "ISurfaceItemsCache" )
		->withMethod( "regSurfaceItem", &ISurfaceItemsCache::regSurfaceItem )
		.withMethod( "setDefaultSurfaceItem", &ISurfaceItemsCache::setDefaultSurfaceItem );

	exporter.exportVariable( "SurfaceItemsCache", m_surfaceItemsCache.get() );

	// ResourcesData

	exporter.exportClassWithShared< ResourcesData >( "ResourcesData" )
		->withConstructor()
		.withMethod( "pushResource", &ResourcesData::pushResource );

	// TrainComponent

	exporter.exportClassWithShared< ITrainComponent::StaticData::TrainData >( "TrainData" )
		->withConstructor< const TickType, const ResourcesData& >();

	exporter.exportClassWithShared< ITrainComponent::StaticData >( "TrainComponentStaticData" )
		->withConstructor()
		.withMethod( "pushTrainData", &ITrainComponent::StaticData::pushTrainData );

	// BuildComponent

	exporter.exportClassWithShared< IBuildComponent::StaticData::BuildData >( "BuildData" )
		->withConstructor< const TickType, const ResourcesData& >();

	exporter.exportClassWithShared< IBuildComponent::StaticData >( "BuildComponentStaticData" )
		->withConstructor()
		.withMethod( "pushBuildData", &IBuildComponent::StaticData::pushBuildData );

	// RepairComponent

	exporter.exportClassWithShared< IRepairComponent::StaticData >( "RepairComponentStaticData" )
		->withConstructor< const TickType, const int >();

	// HealthComponent

	exporter.exportClassWithShared< IHealthComponent::StaticData >( "HealthComponentStaticData" )
		->withConstructor< const int, const bool >();

	// LocateComponent

	exporter.exportClassWithShared< ILocateComponent::StaticData >( "LocateComponentStaticData" )
		->withConstructor< const QSize&, const TerrainMapItem::MaskType, const Emplacement::Enum >();

	// SelectionComponent

	exporter.exportClassWithShared< ISelectionComponent::StaticData >( "SelectionComponentStaticData" )
		->withConstructor();

	// MoveComponent

	exporter.exportClassWithShared< IMoveComponent::StaticData >( "MoveComponentStaticData" )
		->withConstructor< const TickType >();

	// AttackComponent

	exporter.exportClassWithShared< IAttackComponent::StaticData >( "AttackComponentStaticData" )
		->withConstructor< const int, const int, const int, const TickType, const TickType >();

	// PlayerComponent

	exporter.exportClassWithShared< IPlayerComponent::StaticData >( "PlayerComponentStaticData" )
		->withConstructor();

	// GenerateResourcesComponent

	exporter.exportClassWithShared< IGenerateResourcesComponent::StaticData >( "GenerateResourcesComponentStaticData" )
		->withConstructor()
		.withMethod( "canGenerate", &IGenerateResourcesComponent::StaticData::canGenerate );

	// ResourceHolderComponent

	exporter.exportClassWithShared< IResourceHolderComponent::StaticData >( "ResourceHolderComponentStaticData" )
		->withConstructor()
		.withMethod( "hold", &IResourceHolderComponent::StaticData::hold );

	// ResourceSourceComponent

	exporter.exportClassWithShared< IResourceSourceComponent::StaticData >( "ResourceSourceComponentStaticData" )
		->withConstructor< const QString& >();

	// ResourceStorageComponent

	exporter.exportClassWithShared< IResourceStorageComponent::StaticData >( "ResourceStorageComponentStaticData" )
		->withConstructor()
		.withMethod( "canStore", &IResourceStorageComponent::StaticData::canStore );

	// StaticData

	exporter.exportClass< IStaticData::ObjectStaticData >( "ObjectStaticData" )
		->withConstructor()
		.withRWProperty( "m_trainData", &IStaticData::ObjectStaticData::m_trainData )
		.withRWProperty( "m_healthData", &IStaticData::ObjectStaticData::m_healthData )
		.withRWProperty( "m_locateData", &IStaticData::ObjectStaticData::m_locateData )
		.withRWProperty( "m_moveData", &IStaticData::ObjectStaticData::m_moveData )
		.withRWProperty( "m_selectionData", &IStaticData::ObjectStaticData::m_selectionData )
		.withRWProperty( "m_generateResourcesData", &IStaticData::ObjectStaticData::m_generateResourcesData )
		.withRWProperty( "m_attackData", &IStaticData::ObjectStaticData::m_attackData )
		.withRWProperty( "m_buildData", &IStaticData::ObjectStaticData::m_buildData )
		.withRWProperty( "m_repairData", &IStaticData::ObjectStaticData::m_repairData )
		.withRWProperty( "m_resourceHolderData", &IStaticData::ObjectStaticData::m_resourceHolderData )
		.withRWProperty( "m_resourceSourceData", &IStaticData::ObjectStaticData::m_resourceSourceData )
		.withRWProperty( "m_resourceStorageData", &IStaticData::ObjectStaticData::m_resourceStorageData )
		.withRWProperty( "m_playerData", &IStaticData::ObjectStaticData::m_playerData );

	exporter.exportClass< IStaticData >( "IStaticData" )
		->withMethod( "regObjectStaticData", &IStaticData::regObjectStaticData )
		.withMethod( "regResource", &IStaticData::regResource )
		.withMethod( "regRace", &IStaticData::regRace );

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


boost::intrusive_ptr< IModelLocker >
PluginInstance::getLandscapeModelLocker()
{
	return boost::intrusive_ptr< IModelLocker >( new ModelLocker( m_landscapeModel ) );

} // PluginInstance::getLandscapeModelLocker


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
