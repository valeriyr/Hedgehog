
#ifndef __GM_ACTIONS_QUEUE_HPP__
#define __GM_ACTIONS_QUEUE_HPP__

/*---------------------------------------------------------------------------*/

#include "game_manager/sources/actions_queue/gm_iactions_queue.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

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

	/*virtual*/ bool hasActions() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushBackAction( boost::intrusive_ptr< IAction > _action );

	/*virtual*/ boost::intrusive_ptr< IAction > popFrontAction();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::deque< boost::intrusive_ptr< IAction > >
		ActionsCollection;
	typedef ActionsCollection::iterator ActionsCollectionIterator;

/*---------------------------------------------------------------------------*/

	ActionsCollection m_actionsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_ACTIONS_QUEUE_HPP__
