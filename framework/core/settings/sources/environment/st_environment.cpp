
#include "settings/sources/ph/st_ph.hpp"

#include "settings/sources/environment/st_environment.hpp"

#include "settings/sources/plugin/st_plugin_instance.hpp"

#include "event_manager/ih/em_ievent_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace Settings {

/*---------------------------------------------------------------------------*/


Environment::Environment( PluginInstance& _pluginInstance )
	:	m_pluginInstance( _pluginInstance )
{
} // Environment::Environment


/*---------------------------------------------------------------------------*/


Environment::~Environment()
{
} // Environment::~Environment


/*---------------------------------------------------------------------------*/


void
Environment::riseEvent( const Framework::Core::EventManager::Event& _event ) const
{
	m_pluginInstance.getEventManager()->raise( _event );

} // Environment::riseEvent



/*---------------------------------------------------------------------------*/

} // namespace Settings
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
