
#ifndef __AM_ENVIRONMENT_HPP__
#define __AM_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "animation_manager/sources/environment/am_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( const PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ Core::MultithreadingManager::TaskHandle
		pushPeriodicalTask(
					const QString& _threadName
				,	const Core::MultithreadingManager::RunnableFunction& _function ) const;

	/*virtual*/ void removeTask( const Core::MultithreadingManager::TaskHandle& _taskHandle ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QPixmap& getPixmap(
			const QString& _resourcePath
		,	const Framework::GUI::ImagesManager::IImagesManager::TransformationData& _transformationData ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_ENVIRONMENT_HPP__
