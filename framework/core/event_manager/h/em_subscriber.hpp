
#ifndef __EM_SUBSCRIBER_HPP__
#define __EM_SUBSCRIBER_HPP__

#include "event_manager/ih/em_ievent_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/

class Subscriber
{

/*---------------------------------------------------------------------------*/

	struct ConnectionData
	{
		ConnectionData(
				const IEventManager::ConnectionId& _connectionId
			,	const QString& _eventType
			)
			:	m_connectionId( _connectionId )
			,	m_eventType( _eventType )
		{}

		const IEventManager::ConnectionId m_connectionId;
		const QString m_eventType;
	};

	typedef
		std::list< ConnectionData >
		ConnectionsCollection;
	typedef
		ConnectionsCollection::iterator
		ConnectionsCollectionIterator;

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Subscriber( IEventManager& _eventManager )
		:	m_eventManager( _eventManager )
		,	m_connectionsCollection()
	{}

	~Subscriber()
	{
		unsubscribe();
	}

/*---------------------------------------------------------------------------*/

	void subscribe(		const QString& _threadForProcessing
					,	const QString& _eventType
					,	const IEventManager::ProcessingFunction& _function )
	{
		m_connectionsCollection.push_back(
			ConnectionData(
					m_eventManager.subscribe( _threadForProcessing, _eventType, _function )
				,	_eventType ) );
	}

	void unsubscribe()
	{
		ConnectionsCollectionIterator
				begin = m_connectionsCollection.begin()
			,	end = m_connectionsCollection.end();

		for ( ; begin != end; ++begin )
			m_eventManager.unsubscribe( begin->m_connectionId );

		m_connectionsCollection.clear();
	}

	void unsubscribe( const QString& _eventType )
	{
		ConnectionsCollectionIterator begin = m_connectionsCollection.begin();

		for ( ; begin != m_connectionsCollection.end(); ++begin )
		{
			if ( begin->m_eventType == _eventType )
			{
				m_eventManager.unsubscribe( begin->m_connectionId );
				begin = m_connectionsCollection.erase( begin );
			}
		}
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	IEventManager& m_eventManager;

	ConnectionsCollection m_connectionsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_SUBSCRIBER_HPP__
