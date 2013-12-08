
#ifndef __LM_ENVIRONMENT_HPP__
#define __LM_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void startThread( const QString& _threadName ) const;

	/*virtual*/ void stopThread( const QString& _threadName ) const;

	/*virtual*/ Framework::Core::MultithreadingManager::TaskHandle
		pushTask(
				const QString& _threadName
			,	Framework::Core::MultithreadingManager::RunnableFunction _function
			,	const qint64 _period ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessage( const QString& _message ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void riseEvent( const Framework::Core::EventManager::Event& _event ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ENVIRONMENT_HPP__
