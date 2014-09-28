
#ifndef __LM_IENVIRONMENT_HPP__
#define __LM_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "multithreading_manager/h/mm_runnable_function.hpp"
#include "multithreading_manager/h/mm_task_handle.hpp"

#include "event_manager/h/em_event.hpp"
#include "event_manager/h/em_subscriber.hpp"
#include "messenger/ms_imessenger.hpp"
#include "time/t_time.hpp"
#include "script_engine/h/se_function_caller.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace Core
	{
		namespace NetworkManager
		{
			struct IUdpConnection;
			struct ConnectionInfo;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct INotificationCenter;
struct IStaticData;
struct IModelInformation;
struct ISurfaceItemsCache;
struct ILandscapeSerializer;
struct IReplaySerializer;
struct IModelLocker;
struct IAIManager;

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void startThread( const QString& _threadName ) const = 0;

	virtual void stopThread( const QString& _threadName ) const = 0;

	virtual Framework::Core::MultithreadingManager::TaskHandle
		pushPeriodicalTask(
			const QString& _threadName
		,	Framework::Core::MultithreadingManager::RunnableFunction _function
		,	const Tools::Core::Time::Milliseconds _period ) const = 0;

	virtual Framework::Core::MultithreadingManager::TaskHandle
		pushTask(
				const QString& _threadName
			,	Framework::Core::MultithreadingManager::RunnableFunction _function ) const = 0;

	virtual void removeTask( const Framework::Core::MultithreadingManager::TaskHandle& _handle ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual Framework::Core::EventManager::Subscriber createSubscriber() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void riseEvent( const Framework::Core::EventManager::Event& _event ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< INotificationCenter > getNotificationCenter() const = 0;

	virtual boost::intrusive_ptr< IStaticData > getStaticData() const = 0;

	virtual boost::intrusive_ptr< IModelInformation > getModelInformation() const = 0;

	virtual boost::intrusive_ptr< ISurfaceItemsCache > getSurfaceItemsCache() const = 0;

	virtual boost::intrusive_ptr< ILandscapeSerializer > getLandscapeSerializer() const = 0;

	virtual boost::intrusive_ptr< IReplaySerializer > getReplaySerializer() const = 0;

	virtual boost::intrusive_ptr< IAIManager > getAIManager() const = 0;

/*---------------------------------------------------------------------------*/

	virtual QString getApplicationDirectory() const = 0;

	virtual QString getConfigDirectory() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Framework::Core::NetworkManager::IUdpConnection >
		getConnection(
				const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo
			,	const unsigned int _connectionTimeOut ) const = 0;

	virtual void closeConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual QString getString( const QString& _key ) const = 0;

	virtual unsigned int getUInt( const QString& _key ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IModelLocker > lockModel() const = 0;

/*---------------------------------------------------------------------------*/

	virtual Framework::Core::ScriptEngine::FunctionCaller getFunctionCaller() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_IENVIRONMENT_HPP__
