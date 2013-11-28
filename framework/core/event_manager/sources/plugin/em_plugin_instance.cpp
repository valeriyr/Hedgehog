
#include "event_manager/sources/ph/em_ph.hpp"

#include "event_manager/sources/plugin/em_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "event_manager/sources/event_manager/em_event_manager.hpp"
#include "event_manager/sources/environment/em_environment.hpp"

#include "multithreading_manager/h/mm_plugin_id.hpp"
#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_EVENT_MANAGER, m_eventManager.get() )

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
	m_eventManager.reset( new EventManager( *m_environment ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_eventManager.reset();
	m_environment.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::MultithreadingManager::IMultithreadingManager >
PluginInstance::getMultithreadingManager() const
{
	return
		getPluginInterface< Core::MultithreadingManager::IMultithreadingManager >(
				Core::MultithreadingManager::PID_MULTITHREADING_MANAGER
			,	Core::MultithreadingManager::IID_MULTITHREADING_MANAGER );

} // PluginInstance::getMultithreadingManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
