
#include "settings/sources/ph/st_ph.hpp"

#include "settings/sources/plugin/st_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "settings/sources/settings/st_settings.hpp"
#include "settings/sources/environment/st_environment.hpp"

#include "event_manager/h/em_plugin_id.hpp"
#include "event_manager/ih/em_ievent_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_SETTINGS, m_settings.get() )

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
	m_settings.reset( new Settings( *m_environment ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_settings.reset();
	m_environment.reset();

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::EventManager::IEventManager >
PluginInstance::getEventManager() const
{
	return
		getPluginInterface< Core::EventManager::IEventManager >(
				Core::EventManager::PID_EVENT_MANAGER
			,	Core::EventManager::IID_EVENT_MANAGER );

} // PluginInstance::getEventManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
