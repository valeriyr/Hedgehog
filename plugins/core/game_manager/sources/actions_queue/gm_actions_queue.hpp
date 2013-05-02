
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

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_ACTIONS_QUEUE_HPP__
