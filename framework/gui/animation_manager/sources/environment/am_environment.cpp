
#include "animation_manager/sources/ph/am_ph.hpp"

#include "animation_manager/sources/environment/am_environment.hpp"

#include "animation_manager/sources/plugin/am_plugin_instance.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/


Environment::Environment( const PluginInstance& _pluginInstance )
	:	m_pluginInstance( _pluginInstance )
{
} // Environment::Environment


/*---------------------------------------------------------------------------*/


Environment::~Environment()
{
} // Environment::~Environment


/*---------------------------------------------------------------------------*/


Core::MultithreadingManager::TaskHandle
Environment::pushPeriodicalTask(
		const QString& _threadName
	,	const Core::MultithreadingManager::RunnableFunction& _function ) const
{
	return m_pluginInstance.getMultithreadingManager()->pushPeriodicalTask( _threadName, _function, 100 );

} // Environment::pushPeriodicalTask


/*---------------------------------------------------------------------------*/


void
Environment::removeTask( const Core::MultithreadingManager::TaskHandle& _taskHandle ) const
{
	m_pluginInstance.getMultithreadingManager()->removeTask( _taskHandle );

} // Environment::removeTask


/*---------------------------------------------------------------------------*/


const QPixmap&
Environment::getPixmap(
		const QString& _resourcePath
	,	const Framework::GUI::ImagesManager::IImagesManager::TransformationData& _transformationData ) const
{
	return m_pluginInstance.getImagesManager()->getPixmap( _resourcePath, _transformationData );

} // Environment::getPixmap


/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
