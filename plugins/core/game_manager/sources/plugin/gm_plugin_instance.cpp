
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/plugin/gm_plugin_instance.hpp"

#include "plugins_manager/h/pm_plugin_factory.hpp"

#include "game_manager/sources/game_manager/gm_game_manager.hpp"
#include "game_manager/sources/environment/gm_environment.hpp"
#include "game_manager/sources/actions_queue/gm_actions_queue.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "multithreading_manager/h/mm_plugin_id.hpp"


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


boost::intrusive_ptr< Framework::Core::MultithreadingManager::IMultithreadingManager >
PluginInstance::getMultithreadingManager() const
{
	return
		getPluginInterface< Framework::Core::MultithreadingManager::IMultithreadingManager >(
				Framework::Core::MultithreadingManager::PID_MULTITHREADING_MANAGER
			,	Framework::Core::MultithreadingManager::IID_MULTITHREADING_MANAGER );

} // PluginInstance::getMultithreadingManager


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PLUGIN_FACTORY_DECLARATION( PluginInstance )

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
