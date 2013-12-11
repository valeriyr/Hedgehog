
#ifndef __EM_IEVENT_MANAGER_HPP__
#define __EM_IEVENT_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "event_manager/h/em_event.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace EventManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_EVENT_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IEventManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		boost::function< void ( const Event& ) >
		ProcessingFunction;

	typedef QString ConnectionId;

/*---------------------------------------------------------------------------*/

	virtual void raise( const Event& _event ) = 0;

/*---------------------------------------------------------------------------*/

	virtual ConnectionId
		subscribe(		const QString& _threadForProcessing
					,	const QString& _eventType
					,	const ProcessingFunction& _function ) = 0;

	virtual void unsubscribe( const ConnectionId& _connectionId ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace EventManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __EM_IEVENT_MANAGER_HPP__
