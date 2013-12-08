
#ifndef __LM_ACTIONS_QUEUE_HPP__
#define __LM_ACTIONS_QUEUE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions_queue/lm_iactions_queue.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class ActionsQueue
	:	public Tools::Core::BaseWrapper< IActionsQueue >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ActionsQueue();

	virtual ~ActionsQueue();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushAction( boost::intrusive_ptr< IAction > _action );

	/*virtual*/ void processAction( const unsigned int _deltaTime );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::vector< boost::intrusive_ptr< IAction > >
		ActionsCollection;
	typedef ActionsCollection::iterator ActionsCollectionIterator;

/*---------------------------------------------------------------------------*/

	ActionsCollection m_actionsCollection;
	QMutex m_actionsQueueLocker;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ACTIONS_QUEUE_HPP__
