
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
		m_connectionsCollection.push_back( m_eventManager.subscribe( _threadForProcessing, _eventType, _function ) );
	}

	void unsubscribe()
	{
		ConnectionsCollectionIterator
				begin = m_connectionsCollection.begin()
			,	end = m_connectionsCollection.end();

		for ( ; begin != end; ++begin )
			m_eventManager.unsubscribe( *begin );

		m_connectionsCollection.clear();
	}

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< IEventManager::ConnectionId >
		ConnectionsCollection;
	typedef
		ConnectionsCollection::const_iterator
		ConnectionsCollectionIterator;

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
