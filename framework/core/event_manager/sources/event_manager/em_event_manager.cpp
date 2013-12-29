
#include "event_manager/sources/ph/em_ph.hpp"

#include "event_manager/sources/event_manager/em_event_manager.hpp"

#include "event_manager/sources/environment/em_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/


EventManager::EventManager( IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscribersCollection()
	,	m_eventsCollection()
	,	m_locker()
{
} // EventManager::EventManager


/*---------------------------------------------------------------------------*/


EventManager::~EventManager()
{
	assert( m_subscribersCollection.empty() && "Subscribers collection should be empty!" );

} // EventManager::~EventManager


/*---------------------------------------------------------------------------*/


void
EventManager::raise( const Event& _event )
{
	QMutexLocker locker( &m_locker );
	
	m_eventsCollection.push_back( _event );

} // EventManager::raise


/*---------------------------------------------------------------------------*/


IEventManager::ConnectionId
EventManager::subscribe(	const QString& _threadForProcessing
						,	const QString& _eventType
						,	const IEventManager::ProcessingFunction& _function )
{
	QMutexLocker locker( &m_locker );

	const IEventManager::ConnectionId connectionId( QUuid::createUuid().toString() );

	SubscribersCollectionIterator subscribersIterator = m_subscribersCollection.find( _threadForProcessing );
	if ( subscribersIterator == m_subscribersCollection.end() )
	{
		subscribersIterator
			= m_subscribersCollection.insert( std::make_pair( _threadForProcessing, SubscribersData() ) ).first;
		subscribersIterator->second.m_taskHandle
			= m_environment.pushPeriodicalTask( _threadForProcessing, boost::bind( &EventManager::task, this, _threadForProcessing ) );

		assert( subscribersIterator->second.m_taskHandle.isValid() && "Task handle should be valid!" );
	}

	SubscribersData::EventSubscribersCollectionIterator eventSubscribersIterator
		= subscribersIterator->second.m_eventSubscribersCollection.find( _eventType );
	if ( eventSubscribersIterator == subscribersIterator->second.m_eventSubscribersCollection.end() )
	{
		eventSubscribersIterator
			= subscribersIterator->second.m_eventSubscribersCollection
				.insert( std::make_pair( _eventType, EventSubscribersData() ) ).first;
	}

	SubscribersCollectionIterator
			subscribersBegin = m_subscribersCollection.begin()
		,	subscribersEnd = m_subscribersCollection.end();

	for ( ; subscribersBegin != subscribersEnd; ++subscribersBegin)
	{
		SubscribersData::EventSubscribersCollectionIterator
				eventSubscribersBegin = subscribersBegin->second.m_eventSubscribersCollection.begin()
			,	eventSubscribersEnd = subscribersBegin->second.m_eventSubscribersCollection.end();

		for ( ; eventSubscribersBegin != eventSubscribersEnd; ++eventSubscribersBegin )
		{
			assert(			eventSubscribersBegin->second.m_processingFunctionsCollection.find( connectionId )
						==	eventSubscribersBegin->second.m_processingFunctionsCollection.end()
					&&	"Connection id should not be presented in the collection!" );
		}
	}

	eventSubscribersIterator->second.m_processingFunctionsCollection.insert( std::make_pair( connectionId, _function ) );

	return connectionId;

} // EventManager::subscribe


/*---------------------------------------------------------------------------*/


void
EventManager::unsubscribe( const IEventManager::ConnectionId& _connectionId )
{
	QMutexLocker locker( &m_locker );

	SubscribersCollectionIterator
			subscribersBegin = m_subscribersCollection.begin()
		,	subscribersEnd = m_subscribersCollection.end();

	for ( ; subscribersBegin != subscribersEnd; ++subscribersBegin)
	{
		SubscribersData::EventSubscribersCollectionIterator
				eventSubscribersBegin = subscribersBegin->second.m_eventSubscribersCollection.begin()
			,	eventSubscribersEnd = subscribersBegin->second.m_eventSubscribersCollection.end();

		for ( ; eventSubscribersBegin != eventSubscribersEnd; ++eventSubscribersBegin )
		{
			EventSubscribersData::ProcessingFunctionsCollectionIterator iterator
				= eventSubscribersBegin->second.m_processingFunctionsCollection.find( _connectionId );

			if ( iterator != eventSubscribersBegin->second.m_processingFunctionsCollection.end() )
			{
				eventSubscribersBegin->second.m_processingFunctionsCollection.erase( iterator );

				if ( eventSubscribersBegin->second.m_processingFunctionsCollection.empty() )
				{
					subscribersBegin->second.m_eventSubscribersCollection.erase( eventSubscribersBegin );

					if ( subscribersBegin->second.m_eventSubscribersCollection.empty() )
					{
						m_environment.removeTask( subscribersBegin->second.m_taskHandle );
						m_subscribersCollection.erase( subscribersBegin );
					}
				}

				break;
			}
		}
	}

} // EventManager::unsubscribe


/*---------------------------------------------------------------------------*/


void
EventManager::task( const QString& _threadName )
{
	QMutexLocker locker( &m_locker );

	SubscribersCollectionIterator subscribersIterator = m_subscribersCollection.find( _threadName );

	if ( subscribersIterator == m_subscribersCollection.end() )
		return;

	EventsCollectionIterator
			eventsBegin = m_eventsCollection.begin()
		,	eventsEnd = m_eventsCollection.end();

	for ( ; eventsBegin != eventsEnd; ++eventsBegin )
	{
		SubscribersData::EventSubscribersCollectionIterator eventSubscribersIterator
			= subscribersIterator->second.m_eventSubscribersCollection.find( eventsBegin->getType() );

		if ( eventSubscribersIterator != subscribersIterator->second.m_eventSubscribersCollection.end() )
		{
			EventSubscribersData::ProcessingFunctionsCollectionIterator
					processingFunctionsBegin = eventSubscribersIterator->second.m_processingFunctionsCollection.begin()
				,	processingFunctionsEnd = eventSubscribersIterator->second.m_processingFunctionsCollection.end();

			for ( ; processingFunctionsBegin != processingFunctionsEnd; ++processingFunctionsBegin )
			{
				processingFunctionsBegin->second( *eventsBegin );
			}
		}
	}

	m_eventsCollection.clear();

} // EventManager::task


/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
