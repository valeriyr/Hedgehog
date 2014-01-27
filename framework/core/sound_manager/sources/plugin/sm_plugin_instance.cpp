
#include "sound_manager/sources/ph/sm_ph.hpp"

#include "sound_manager/sources/plugin/sm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "sound_manager/sources/sound_manager/sm_sound_manager.hpp"

#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"

#include "settings/ih/st_isettings.hpp"
#include "settings/h/st_plugin_id.hpp"

#include "sound_manager/sources/environment/sm_environment.hpp"

#include "sound_manager/h/sm_resources.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace SoundManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_SOUND_MANAGER, m_soundManager.get() )

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
	getSettings()->regBool( Resources::Properties::PlaySound, true );

	m_environment.reset( new Environment( *this ) );
	m_soundManager.reset( new SoundManager( *m_environment ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_soundManager.reset();
	m_environment.reset();

	getSettings()->unregProperty( Resources::Properties::PlaySound );

} // PluginInstance::close


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::PluginsManager::ISystemInformation >
PluginInstance::getSystemInformation() const
{
	return
		getPluginInterface< Core::PluginsManager::ISystemInformation >(
				Core::PluginsManager::PID_PLUGINS_MANAGER
			,	Core::PluginsManager::IID_SYSTEM_INFORMATION );

} // PluginInstance::getSystemInformation


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
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
