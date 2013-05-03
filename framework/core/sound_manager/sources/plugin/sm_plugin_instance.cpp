
#include "sound_manager/sources/ph/sm_ph.hpp"

#include "sound_manager/sources/plugin/sm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "sound_manager/sources/sound_manager/sm_sound_manager.hpp"

#include "plugins_manager/h/pm_plugin_id.hpp"
#include "plugins_manager/ih/pm_isystem_information.hpp"


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
	m_soundManager.reset( new SoundManager( getSystemInformation()->getResourcesDirectory() ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_soundManager.reset();

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
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace SoundManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
