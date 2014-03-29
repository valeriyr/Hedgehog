
#include "multithreading_manager/sources/ph/mm_ph.hpp"

#include "multithreading_manager/sources/plugin/mm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "multithreading_manager/sources/multithreading_manager/mm_multithreading_manager.hpp"
#include "multithreading_manager/sources/resources_manager/mm_resources_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace MultithreadingManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_MULTITHREADING_MANAGER, m_multithreadingManager )
	INTERFACE_DECLARATION( IID_RESOURCES_MANAGER, m_resourcesManager )

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
	m_resourcesManager.reset( new ResourcesManager() );
	m_multithreadingManager.reset( new MultithreadingManager() );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_multithreadingManager.reset();
	m_resourcesManager.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace MultithreadingManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
