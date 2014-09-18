
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
		pushPeriodicalTask(
				const QString& _threadName
			,	Framework::Core::MultithreadingManager::RunnableFunction _function
			,	const Tools::Core::Time::Milliseconds _period ) const;

	/*virtual*/ Framework::Core::MultithreadingManager::TaskHandle
		pushTask(
				const QString& _threadName
			,	Framework::Core::MultithreadingManager::RunnableFunction _function ) const;

	/*virtual*/ void removeTask( const Framework::Core::MultithreadingManager::TaskHandle& _handle ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void riseEvent( const Framework::Core::EventManager::Event& _event ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< INotificationCenter > getNotificationCenter() const;

	/*virtual*/ boost::intrusive_ptr< IStaticData > getStaticData() const;

	/*virtual*/ boost::intrusive_ptr< IModelInformation > getModelInformation() const;

	/*virtual*/ boost::intrusive_ptr< ISurfaceItemsCache > getSurfaceItemsCache() const;

	/*virtual*/ boost::intrusive_ptr< ILandscapeSerializer > getLandscapeSerializer() const;

	/*virtual*/ boost::intrusive_ptr< IReplaySerializer > getReplaySerializer() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString getApplicationDirectory() const;

	/*virtual*/ QString getConfigDirectory() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< Framework::Core::NetworkManager::IUdpConnection >
		getConnection(
				const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo
			,	const unsigned int _connectionTimeOut ) const;

	/*virtual*/ void closeConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString getString( const QString& _key ) const;

	/*virtual*/ unsigned int getUInt( const QString& _key ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IModelLocker > lockModel() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void executeLuaFunction( const QString& _function ) const;

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
