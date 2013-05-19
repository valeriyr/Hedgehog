
#ifndef __GM_ENVIRONMENT_HPP__
#define __GM_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "game_manager/sources/environment/gm_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

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

	/*virtual*/ boost::intrusive_ptr< LandscapeModel::IEditableLandscape > getCurrentLandscape() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void runThread(
			const QString& _threadName
		,	Framework::Core::MultithreadingManager::RunnableFunction _function ) const;

	/*virtual*/ void stopThread( const QString& _threadName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void playSound( const QString& _resourcePath ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_ENVIRONMENT_HPP__
