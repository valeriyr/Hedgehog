
#ifndef __EM_SOUND_MANAGER_HPP__
#define __EM_SOUND_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "event_manager/ih/em_ievent_manager.hpp"

#include "multithreading_manager/h/mm_task_handle.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class EventManager
	:	public Tools::Core::BaseWrapper< IEventManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	EventManager( IEnvironment& _environment );

	virtual ~EventManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void raise( const Event& _event );

/*---------------------------------------------------------------------------*/

	/*virtual*/ IEventManager::ConnectionId
		subscribe(		const QString& _threadForProcessing
					,	const QString& _eventType
					,	const IEventManager::ProcessingFunction& _function );

	/*virtual*/ void unsubscribe( const IEventManager::ConnectionId& _connectionId );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void task( const QString& _threadName );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct EventSubscribersData
	{
		typedef
			std::map< IEventManager::ConnectionId, IEventManager::ProcessingFunction >
			ProcessingFunctionsCollection;
		typedef
			ProcessingFunctionsCollection::iterator
			ProcessingFunctionsCollectionIterator;

		ProcessingFunctionsCollection m_processingFunctionsCollection;
	};

/*---------------------------------------------------------------------------*/

	struct SubscribersData
	{
		typedef
			std::map< QString, EventSubscribersData >
			EventSubscribersCollection;
		typedef
			EventSubscribersCollection::iterator
			EventSubscribersCollectionIterator;

		EventSubscribersCollection m_eventSubscribersCollection;

		MultithreadingManager::TaskHandle m_taskHandle;
	};

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, SubscribersData >
		SubscribersCollection;
	typedef
		SubscribersCollection::iterator
		SubscribersCollectionIterator;

	typedef
		std::vector< Event >
		EventsCollection;
	typedef
		EventsCollection::iterator
		EventsCollectionIterator;

/*---------------------------------------------------------------------------*/

	IEnvironment& m_environment;

	SubscribersCollection m_subscribersCollection;

	EventsCollection m_eventsCollection;

	QMutex m_mutex;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_SOUND_MANAGER_HPP__
