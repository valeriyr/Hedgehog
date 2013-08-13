
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/plugin/gm_plugin_instance.hpp"

#include "messenger/ms_imessenger.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"
#include "plugins_manager/h/pm_plugin_id.hpp"

#include "game_manager/sources/game_manager/gm_game_manager.hpp"
#include "game_manager/sources/environment/gm_environment.hpp"
#include "game_manager/sources/actions_queue/gm_actions_queue.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "multithreading_manager/h/mm_plugin_id.hpp"

#include "network_manager/h/nm_plugin_id.hpp"
#include "network_manager/ih/nm_iconnection_manager.hpp"

#include "sound_manager/ih/sm_isound_manager.hpp"
#include "sound_manager/h/sm_plugin_id.hpp"

#include "landscape_model/ih/lm_ilandscape_manager.hpp"
#include "landscape_model/h/lm_plugin_id.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


BEGIN_INTERFACE_MAP( PluginInstance )

	INTERFACE_DECLARATION( IID_GAME_MANAGER, m_gameManager.get() )

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
	m_gameManager.reset(
		new GameManager(
				*m_environment
			,	boost::intrusive_ptr< IActionsQueue >( new ActionsQueue() ) ) );

} // PluginInstance::initialize


/*---------------------------------------------------------------------------*/


void
PluginInstance::close()
{
	m_gameManager.reset();
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


boost::intrusive_ptr< Framework::Core::SoundManager::ISoundManager >
PluginInstance::getSoundManager() const
{
	return
		getPluginInterface< Framework::Core::SoundManager::ISoundManager >(
				Framework::Core::SoundManager::PID_SOUND_MANAGER
			,	Framework::Core::SoundManager::IID_SOUND_MANAGER );

} // PluginInstance::getSoundManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeManager >
PluginInstance::getLandscapeManager() const
{
	return
		getPluginInterface< Plugins::Core::LandscapeModel::ILandscapeManager >(
				Plugins::Core::LandscapeModel::PID_LANDSCAPE_MODEL
			,	Plugins::Core::LandscapeModel::IID_LANDSCAPE_MANAGER );

} // PluginInstance::getLandscapeManager


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
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
