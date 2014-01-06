
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/plugin/lm_plugin_instance.hpp"

#include "messenger/ms_imessenger.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "multithreading_manager/h/mm_plugin_id.hpp"

#include "event_manager/ih/em_ievent_manager.hpp"
#include "event_manager/h/em_plugin_id.hpp"

#include "landscape_model/sources/environment/lm_environment.hpp"
#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"
#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"
#include "landscape_model/sources/surface_items_cache/lm_surface_items_cache.hpp"
#include "landscape_model/sources/static_data/lm_static_data.hpp"

#include "landscape_model/sources/surface_item/lm_surface_item.hpp"


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
	m_staticData.reset( new StaticData() );
	m_surfaceItemsCache.reset( new SurfaceItemsCache() );
	m_landscapeSerializer.reset( new LandscapeSerializer() );
	m_landscapeModel.reset( new LandscapeModel( *m_environment, *m_landscapeSerializer, *m_surfaceItemsCache, *m_staticData ) );

	fillSurfaceItemsCache();
	fillObjectsCache();

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_landscapeModel.reset();
	m_landscapeSerializer.reset();
	m_surfaceItemsCache.reset();
	m_staticData.reset();
	m_environment.reset();

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


void
PluginInstance::fillSurfaceItemsCache()
{
	// Ground tiles with water borders

	// 1 --- 2 --- 3
	// |     |     |
	// 4 --- 5 --- 6
	// |     |     |
	// 7 --- 8 --- 9

	m_surfaceItemsCache->regSurfaceItem( 1, TerrainMapItem::NotAvailable );
	m_surfaceItemsCache->regSurfaceItem( 2, TerrainMapItem::NotAvailable );
	m_surfaceItemsCache->regSurfaceItem( 3, TerrainMapItem::NotAvailable );
	m_surfaceItemsCache->regSurfaceItem( 4, TerrainMapItem::NotAvailable );
	m_surfaceItemsCache->regSurfaceItem( 5, TerrainMapItem::Ground );
	m_surfaceItemsCache->regSurfaceItem( 6, TerrainMapItem::NotAvailable );
	m_surfaceItemsCache->regSurfaceItem( 7, TerrainMapItem::NotAvailable );
	m_surfaceItemsCache->regSurfaceItem( 8, TerrainMapItem::NotAvailable );
	m_surfaceItemsCache->regSurfaceItem( 9, TerrainMapItem::NotAvailable );

	// Water tiles

	m_surfaceItemsCache->regSurfaceItem( 101, TerrainMapItem::Water );

	//Default surface item

	m_surfaceItemsCache->setDefaultSurfaceItem( 5 );

} // PluginInstance::fillSurfaceItemsCache


/*---------------------------------------------------------------------------*/


void
PluginInstance::fillObjectsCache()
{
	// Elven Archer
	{
		m_staticData->regHealthStaticData( "Elven Archer", boost::shared_ptr< const HealthComponentStaticData >( new HealthComponentStaticData( 100 ) ) );
		m_staticData->regLocateStaticData( "Elven Archer", boost::shared_ptr< const LocateComponentStaticData >( new LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem::Ground ) ) );
		m_staticData->regMoveStaticData( "Elven Archer", boost::shared_ptr< const MoveComponentStaticData >( new MoveComponentStaticData( 800 ) ) );
		m_staticData->regSelectionStaticData( "Elven Archer", boost::shared_ptr< const SelectionComponentStaticData >( new SelectionComponentStaticData( true ) ) );

		ActionsComponentStaticData::ActionsCollection actions;
		actions.insert( Actions::Move );

		m_staticData->regActionsStaticData( "Elven Archer", boost::shared_ptr< const ActionsComponentStaticData >( new ActionsComponentStaticData( actions ) ) );
	}

	// Grunt
	{
		m_staticData->regHealthStaticData( "Grunt", boost::shared_ptr< const HealthComponentStaticData >( new HealthComponentStaticData( 200 ) ) );
		m_staticData->regLocateStaticData( "Grunt", boost::shared_ptr< const LocateComponentStaticData >( new LocateComponentStaticData( QSize( 1, 1 ), TerrainMapItem::Ground ) ) );
		m_staticData->regMoveStaticData( "Grunt", boost::shared_ptr< const MoveComponentStaticData >( new MoveComponentStaticData( 1000 ) ) );
		m_staticData->regSelectionStaticData( "Grunt", boost::shared_ptr< const SelectionComponentStaticData >( new SelectionComponentStaticData( true ) ) );

		ActionsComponentStaticData::ActionsCollection actions;
		actions.insert( Actions::Move );

		m_staticData->regActionsStaticData( "Grunt", boost::shared_ptr< const ActionsComponentStaticData >( new ActionsComponentStaticData( actions ) ) );
	}

	// Orc Barracks
	{
		m_staticData->regHealthStaticData( "Orc Barracks", boost::shared_ptr< const HealthComponentStaticData >( new HealthComponentStaticData( 1200 ) ) );
		m_staticData->regLocateStaticData( "Orc Barracks", boost::shared_ptr< const LocateComponentStaticData >( new LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem::Ground ) ) );
		m_staticData->regSelectionStaticData( "Orc Barracks", boost::shared_ptr< const SelectionComponentStaticData >( new SelectionComponentStaticData( true ) ) );

		ActionsComponentStaticData::ActionsCollection actions;
		actions.insert( Actions::Build );

		m_staticData->regActionsStaticData( "Orc Barracks", boost::shared_ptr< const ActionsComponentStaticData >( new ActionsComponentStaticData( actions ) ) );

		BuilderComponentStaticData::BuildObjectsDataCollection orcBarracksUnits;
		orcBarracksUnits.push_back( boost::shared_ptr< const BuildObjectsData >( new BuildObjectsData( 3000, "Grunt" ) ) );

		m_staticData->regBuilderStaticData( "Orc Barracks", boost::shared_ptr< const BuilderComponentStaticData >( new BuilderComponentStaticData( orcBarracksUnits ) ) );
	}

	// Human Barracks
	{
		m_staticData->regHealthStaticData( "Human Barracks", boost::shared_ptr< const HealthComponentStaticData >( new HealthComponentStaticData( 1000 ) ) );
		m_staticData->regLocateStaticData( "Human Barracks", boost::shared_ptr< const LocateComponentStaticData >( new LocateComponentStaticData( QSize( 3, 3 ), TerrainMapItem::Ground ) ) );
		m_staticData->regSelectionStaticData( "Human Barracks", boost::shared_ptr< const SelectionComponentStaticData >( new SelectionComponentStaticData( true ) ) );

		ActionsComponentStaticData::ActionsCollection actions;
		actions.insert( Actions::Build );

		m_staticData->regActionsStaticData( "Human Barracks", boost::shared_ptr< const ActionsComponentStaticData >( new ActionsComponentStaticData( actions ) ) );

		BuilderComponentStaticData::BuildObjectsDataCollection humanBarracksUnits;
		humanBarracksUnits.push_back( boost::shared_ptr< const BuildObjectsData >( new BuildObjectsData( 4500, "Elven Archer" ) ) );

		m_staticData->regBuilderStaticData( "Human Barracks", boost::shared_ptr< const BuilderComponentStaticData >( new BuilderComponentStaticData( humanBarracksUnits ) ) );
	}

} // PluginInstance::fillObjectsCache


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
