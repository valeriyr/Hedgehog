
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

#include "network_manager/ih/nm_iconnection_manager.hpp"
#include "network_manager/h/nm_plugin_id.hpp"
#include "network_manager/h/nm_resources.hpp"

#include "settings/ih/st_isettings.hpp"
#include "settings/h/st_plugin_id.hpp"

#include "landscape_model/h/lm_resources.hpp"

#include "landscape_model/sources/environment/lm_environment.hpp"
#include "landscape_model/sources/model_locker/lm_model_locker.hpp"
#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"
#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"
#include "landscape_model/sources/replay_serializer/lm_replay_serializer.hpp"
#include "landscape_model/sources/surface_items_cache/lm_surface_items_cache.hpp"
#include "landscape_model/sources/static_data/lm_static_data.hpp"
#include "landscape_model/sources/model_information/lm_model_information.hpp"
#include "landscape_model/sources/surface_item/lm_surface_item.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"
#include "landscape_model/sources/notification_center/lm_notification_center.hpp"

#include "landscape_model/sources/ai/ai_manager/lm_ai_manager.hpp"


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
	// TODO: Force loading of the network manager.
	getConnectionManager();

	getSettings()->regUInt( Resources::Properties::Port, Resources::Properties::DefaultPortValue );
	getSettings()->regString( Resources::Properties::Ip, Framework::Core::NetworkManager::Resources::LocalHost );
	getSettings()->regUInt( Resources::Properties::ConnectionTimeOut, 10000 );
	getSettings()->regString( Resources::Properties::PlayerName, "amator" );

	m_environment.reset( new Environment( *this ) );
	m_notificationCenter.reset( new NotificationCenter() );
	m_staticData.reset( new StaticData() );
	m_modelInformation.reset( new ModelInformation( *m_environment ) );
	m_surfaceItemsCache.reset( new SurfaceItemsCache() );
	m_landscapeSerializer.reset( new LandscapeSerializer() );
	m_replaySerializer.reset( new ReplaySerializer( *m_environment ) );
	m_landscapeModel.reset( new LandscapeModel( *m_environment ) );
	m_aiManager.reset( new AIManager( *m_environment ) );

	exportScriptAPI();
	executeConfigurationScripts( m_modelInformation->getObjectsScriptsDirectory() );
	executeConfigurationScripts( m_modelInformation->getAIScriptsDirectory() );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_aiManager.reset();
	m_landscapeModel.reset();
	m_replaySerializer.reset();
	m_landscapeSerializer.reset();
	m_surfaceItemsCache.reset();
	m_modelInformation.reset();
	m_staticData.reset();
	m_notificationCenter.reset();
	m_environment.reset();

	getSettings()->unregProperty( Resources::Properties::Port );
	getSettings()->unregProperty( Resources::Properties::Ip );
	getSettings()->unregProperty( Resources::Properties::ConnectionTimeOut );
	getSettings()->unregProperty( Resources::Properties::PlayerName );

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


boost::intrusive_ptr< Framework::Core::NetworkManager::IConnectionManager >
PluginInstance::getConnectionManager() const
{
	return
		getPluginInterface< Framework::Core::NetworkManager::IConnectionManager >(
				Framework::Core::NetworkManager::PID_NETWORK_MANAGER
			,	Framework::Core::NetworkManager::IID_CONNECTION_MANAGER );

} // PluginInstance::getConnectionManager


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


boost::intrusive_ptr< INotificationCenter >
PluginInstance::getNotificationCenter() const
{
	return m_notificationCenter;

} // PluginInstance::getNotificationCenter


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IStaticData >
PluginInstance::getStaticData() const
{
	return m_staticData;

} // PluginInstance::getStaticData


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IModelInformation >
PluginInstance::getModelInformation() const
{
	return m_modelInformation;

} // PluginInstance::getModelInformation


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ISurfaceItemsCache >
PluginInstance::getSurfaceItemsCache() const
{
	return m_surfaceItemsCache;

} // PluginInstance::getSurfaceItemsCache


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeSerializer >
PluginInstance::getLandscapeSerializer() const
{
	return m_landscapeSerializer;

} // PluginInstance::getLandscapeSerializer


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IReplaySerializer >
PluginInstance::getReplaySerializer() const
{
	return m_replaySerializer;

} // PluginInstance::getReplaySerializer


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IAIManager >
PluginInstance::getAIManager() const
{
	return m_aiManager;

} // PluginInstance::getAIManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IModelLocker >
PluginInstance::getLandscapeModelLocker()
{
	return boost::intrusive_ptr< IModelLocker >( new ModelLocker( m_landscapeModel ) );

} // PluginInstance::getLandscapeModelLocker


/*---------------------------------------------------------------------------*/


void
PluginInstance::exportScriptAPI()
{
	Framework::Core::ScriptEngine::DataExporter exporter = getScriptExporter()->getDataExporter();

	// Types

	exporter.exportClass< std::list< QPoint > >( "ListOfPoints" )
		->withConstructor();

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

	// GameObject

	exporter.exportClassWithShared< GameObject >( "GameObject" );
	exporter.exportClass< boost::shared_ptr< GameObject > >( "GameObjectPtr" )
		->withConstructor();

	// Object

	exporter.exportClassWithShared< Tools::Core::Object >( "Object" )
		->withConstructor()
		.withMethod( "pushEmplacementMember", &Tools::Core::Object::pushMember< Emplacement::Enum > )
		.withMethod( "pushDirectionMember", &Tools::Core::Object::pushMember< Direction::Enum > )
		.withMethod( "pushIntMember", &Tools::Core::Object::pushMember< qint32 > )
		.withMethod( "pushUIntMember", &Tools::Core::Object::pushMember< quint32 > )
		.withMethod( "pushBoolMember", &Tools::Core::Object::pushMember< bool > )
		.withMethod( "pushTickTypeMember", &Tools::Core::Object::pushMember< TickType > )
		.withMethod( "pushStringMember", &Tools::Core::Object::pushMember< QString > )
		.withMethod( "pushPointMember", &Tools::Core::Object::pushMember< QPoint > )
		.withMethod( "pushSizeMember", &Tools::Core::Object::pushMember< QSize > )
		.withMethod( "pushRectMember", &Tools::Core::Object::pushMember< QRect > )
		.withMethod( "pushListOfPointsMember", &Tools::Core::Object::pushMember< std::list< QPoint > > )
		.withMethod( "pushResourcesDataMember", &Tools::Core::Object::pushMember< ResourcesData > )
		.withMethod( "pushHoldStaticDataMember", &Tools::Core::Object::pushMember< ResourceHolderComponent::StaticData::HoldStaticData > )
		.withMethod(	"getObjectPtrMember"
					,	( Tools::Core::Object::Ptr& (Tools::Core::Object::*)( const QString& ) )
							&Tools::Core::Object::getMember< Tools::Core::Object::Ptr > )
		.withMethod(	"getObjectMember"
					,	( Tools::Core::Object& (Tools::Core::Object::*)( const QString& ) )
							&Tools::Core::Object::getMember< Tools::Core::Object > )
		.withMethod( "pushGameObjectPtrMember", &Tools::Core::Object::pushMember< boost::shared_ptr< GameObject > > )
		.withMethod( "pushBuildStaticDataMember", &Tools::Core::Object::pushMember< BuildComponent::StaticData::Data::Ptr > )
		.withMethod( "pushVoidMethod", &Tools::Core::Object::pushMethod< void > )
		.withMethod( "pushBoolMethod", &Tools::Core::Object::pushMethod< bool > )
		.withMethod( "pushVoidIntMethod", &Tools::Core::Object::pushMethod< void, qint32 > );

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

	exporter.exportVariable( "BuildComponentName", BuildComponent::Name );

	exporter.exportVariable( "BuildComponentObjectName", BuildComponent::ObjectName );
	exporter.exportVariable( "BuildComponentAtRect", BuildComponent::AtRect );
	exporter.exportVariable( "BuildComponentBuildProgress", BuildComponent::BuildProgress );
	exporter.exportVariable( "BuildComponentObjectId", BuildComponent::ObjectId );

	exporter.exportVariable( "BuildComponentStaticDataKey", BuildComponent::StaticData::DataKey );

	exporter.exportClassWithShared< BuildComponent::StaticData::Data::BuildData >( "BuildData" )
		->withConstructor< const TickType, const ResourcesData& >();

	exporter.exportClassWithShared< BuildComponent::StaticData::Data >( "BuildComponentStaticData" )
		->withConstructor()
		.withMethod( "pushBuildData", &BuildComponent::StaticData::Data::pushBuildData );

	// RepairComponent

	exporter.exportVariable( "RepairComponentName", RepairComponent::Name );
	exporter.exportVariable( "RepairComponentHealthByTick", RepairComponent::StaticData::HealthByTick );
	exporter.exportVariable( "RepairComponentCostPercent", RepairComponent::StaticData::CostPercent );
	exporter.exportVariable( "RepairComponentTargetObject", RepairComponent::TargetObject );

	// HealthComponent

	exporter.exportVariable( "HealthComponentName", HealthComponent::Name );
	exporter.exportVariable( "HealthComponentMaxHealth", HealthComponent::StaticData::MaxHealth );
	exporter.exportVariable( "HealthComponentCanBeRepair", HealthComponent::StaticData::CanBeRepair );
	exporter.exportVariable( "HealthComponentHealth", HealthComponent::Health );
	//exporter.exportVariable( "HealthComponentSetHealth", HealthComponent::SetHealth );
	//exporter.exportVariable( "HealthComponentIsHealthy", HealthComponent::IsHealthy );

	exporter.exportFunction( "HealthComponentSetHealthDefault", &HealthComponent::setHealth );
	exporter.exportFunction( "HealthComponentIsHealthyDefault", &HealthComponent::isHealthy );

	// LocateComponent

	exporter.exportVariable( "LocateComponentName", LocateComponent::Name );
	exporter.exportVariable( "LocateComponentSize", LocateComponent::StaticData::Size );
	exporter.exportVariable( "LocateComponentPassability", LocateComponent::StaticData::Passability );
	exporter.exportVariable( "LocateComponentEmplacement", LocateComponent::StaticData::Emplacement );
	exporter.exportVariable( "LocateComponentDirection", LocateComponent::Direction);
	exporter.exportVariable( "LocateComponentLocation", LocateComponent::Location);
	exporter.exportVariable( "LocateComponentIsHidden", LocateComponent::IsHidden);

	// SelectionComponent

	exporter.exportVariable( "SelectionComponentName", SelectionComponent::Name );
	exporter.exportVariable( "SelectionComponentIsSelected", SelectionComponent::IsSelected );

	// MoveComponent

	exporter.exportVariable( "MoveComponentName", MoveComponent::Name );
	exporter.exportVariable( "MoveComponentMovingSpeed", MoveComponent::StaticData::MovingSpeed );
	exporter.exportVariable( "MoveComponentPath", MoveComponent::Path );
	exporter.exportVariable( "MoveComponentMovingProgress", MoveComponent::MovingProgress );
	exporter.exportVariable( "MoveComponentMovingTo", MoveComponent::MovingTo );
	exporter.exportVariable( "MoveComponentMovingToObject", MoveComponent::MovingToObject );

	// AttackComponent

	exporter.exportVariable( "AttackComponentName", AttackComponent::Name );
	exporter.exportVariable( "AttackComponentTargetObject", AttackComponent::TargetObject );
	exporter.exportVariable( "AttackComponentAiming", AttackComponent::StaticData::Aiming );
	exporter.exportVariable( "AttackComponentDistance", AttackComponent::StaticData::Distance );
	exporter.exportVariable( "AttackComponentMaxDamage", AttackComponent::StaticData::MaxDamage );
	exporter.exportVariable( "AttackComponentMinDamage", AttackComponent::StaticData::MinDamage );
	exporter.exportVariable( "AttackComponentReloading", AttackComponent::StaticData::Reloading );

	// PlayerComponent

	exporter.exportVariable( "PlayerComponentName", PlayerComponent::Name );
	exporter.exportVariable( "PlayerComponentPlayerId", PlayerComponent::PlayerId );

	// GenerateResourcesComponent

	exporter.exportVariable( "GenerateResourcesComponentName", GenerateResourcesComponent::Name );
	exporter.exportVariable( "GenerateResourcesComponentResourcesByTick", GenerateResourcesComponent::StaticData::ResourcesByTick );

	// ResourceHolderComponent

	exporter.exportVariable( "ResourceHolderComponentName", ResourceHolderComponent::Name );
	exporter.exportVariable( "ResourceHolderComponentHoldStaticData", ResourceHolderComponent::StaticData::HoldStaticDataKey );
	exporter.exportVariable( "ResourceHolderComponentHeldResources", ResourceHolderComponent::HeldResources );

	exporter.exportClass< ResourceHolderComponent::StaticData::HoldResourceData >( "HoldResourceData" )
		->withConstructor< const int, const int >();

	exporter.exportClass< ResourceHolderComponent::StaticData::HoldStaticData >( "HoldStaticData" )
		->withConstructor()
		.withMethod( "pushData", &ResourceHolderComponent::StaticData::HoldStaticData::pushData )
		.withMethod( "getData", &ResourceHolderComponent::StaticData::HoldStaticData::getData );

	exporter.exportFunction( "initResourceHolderComponent", ResourceHolderComponent::initComponent );

	// ResourceSourceComponent

	exporter.exportClassWithShared< IResourceSourceComponent::StaticData >( "ResourceSourceComponentStaticData" )
		->withConstructor< const QString& >();

	// ResourceStorageComponent

	exporter.exportClassWithShared< IResourceStorageComponent::StaticData >( "ResourceStorageComponentStaticData" )
		->withConstructor()
		.withMethod( "canStore", &IResourceStorageComponent::StaticData::canStore );

	// StaticData

	exporter.exportVariable( "StaticDataName", StaticDataTools::Name );

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
		.withMethod( "regRace", &IStaticData::regRace )
		.withMethod( "regObjectCreator", &IStaticData::regObjectCreator );

	exporter.exportVariable( "StaticData", m_staticData.get() );

	// AIManager

	exporter.exportClass< IAIManager >( "IAIManager" )
		->withMethod( "regAI", &IAIManager::regAI );

	exporter.exportVariable( "AIManager", m_aiManager.get() );

} // PluginInstance::exportScriptAPI


/*---------------------------------------------------------------------------*/


void
PluginInstance::executeConfigurationScripts( const QString& _directory )
{
	QDir scriptsDirectory = QDir( _directory );

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
