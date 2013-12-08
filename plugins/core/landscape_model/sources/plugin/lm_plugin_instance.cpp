
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/plugin/lm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "multithreading_manager/h/mm_plugin_id.hpp"

#include "event_manager/ih/em_ievent_manager.hpp"
#include "event_manager/h/em_plugin_id.hpp"

#include "landscape_model/sources/landscape_editor/lm_landscape_editor.hpp"
#include "landscape_model/sources/landscape_model/lm_landscape_model.hpp"
#include "landscape_model/sources/landscape_serializer/lm_landscape_serializer.hpp"
#include "landscape_model/sources/surface_items_cache/lm_surface_items_cache.hpp"
#include "landscape_model/sources/object_types_cache/lm_object_types_cache.hpp"

#include "landscape_model/sources/surface_item/lm_surface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_LANDSCAPE_EDITOR, m_landscapeEditor.get() )
	INTERFACE_DECLARATION( IID_LANDSCAPE_MODEL, m_landscapeModel.get() )
	INTERFACE_DECLARATION( IID_SURFACE_ITEMS_CACHE, m_surfaceItemsCache.get() )
	INTERFACE_DECLARATION( IID_OBJECT_TYPES_CACHE, m_objectTypesCache.get() )

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
	m_objectTypesCache.reset( new ObjectTypesCache() );
	m_surfaceItemsCache.reset( new SurfaceItemsCache() );
	m_landscapeSerializer.reset( new LandscapeSerializer() );
	m_landscapeEditor.reset( new LandscapeEditor( *m_landscapeSerializer, *m_surfaceItemsCache, *m_objectTypesCache ) );
	m_landscapeModel.reset( new LandscapeModel( *m_landscapeSerializer, *m_surfaceItemsCache, *m_objectTypesCache ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_landscapeModel.reset();
	m_landscapeEditor.reset();
	m_landscapeSerializer.reset();
	m_surfaceItemsCache.reset();
	m_objectTypesCache.reset();

} // PluginInstance::close


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
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
