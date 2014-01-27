
#include "sound_manager/sources/ph/sm_ph.hpp"

#include "sound_manager/sources/environment/sm_environment.hpp"

#include "sound_manager/sources/plugin/sm_plugin_instance.hpp"

#include "settings/ih/st_isettings.hpp"

#include "plugins_manager/ih/pm_isystem_information.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace SoundManager {

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


const QString&
Environment::getResourcesDirectory() const
{
	return m_pluginInstance.getSystemInformation()->getResourcesDirectory();

} // Environment::getResourcesDirectory


/*---------------------------------------------------------------------------*/


bool
Environment::getBool( const QString& _key ) const
{
	return m_pluginInstance.getSettings()->getBool( _key );

} // Environment::getBool


/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
