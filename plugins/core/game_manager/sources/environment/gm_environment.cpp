
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/environment/gm_environment.hpp"

#include "game_manager/sources/plugin/gm_plugin_instance.hpp"

#include "multithreading_manager/ih/mm_imultithreading_manager.hpp"
#include "sound_manager/ih/sm_isound_manager.hpp"
#include "landscape_model/ih/lm_ilandscape_manager.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

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


boost::intrusive_ptr< LandscapeModel::IEditableLandscape >
Environment::getCurrentLandscape() const
{
	return m_pluginInstance.getLandscapeManager()->getCurrentLandscape();

} // Environment::getCurrentLandscape


/*---------------------------------------------------------------------------*/


void
Environment::runThread(
		const QString& _threadName
	,	Framework::Core::MultithreadingManager::RunnableFunction _function ) const
{
	m_pluginInstance.getMultithreadingManager()->run( _threadName, _function, 1000 );

} // Environment::runThread


/*---------------------------------------------------------------------------*/


void
Environment::stopThread( const QString& _threadName ) const
{
	m_pluginInstance.getMultithreadingManager()->stop( _threadName );

} // Environment::stopThread


/*---------------------------------------------------------------------------*/


void
Environment::playSound( const QString& _resourcePath ) const
{
	m_pluginInstance.getSoundManager()->play( _resourcePath );

} // Environment::playSound


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
