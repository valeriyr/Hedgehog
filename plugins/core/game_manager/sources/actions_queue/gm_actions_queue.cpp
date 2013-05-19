
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/actions_queue/gm_actions_queue.hpp"

#include "game_manager/sources/actions/gm_iaction.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


ActionsQueue::ActionsQueue()
	:	m_actionsCollection()
{
} // ActionsQueue::ActionsQueue


/*---------------------------------------------------------------------------*/


ActionsQueue::~ActionsQueue()
{
} // ActionsQueue::~ActionsQueue


/*---------------------------------------------------------------------------*/


bool
ActionsQueue::hasActions() const
{
	return m_actionsCollection.size() != 0;

} // ActionsQueue::hasActions


/*---------------------------------------------------------------------------*/


void
ActionsQueue::pushBackAction( boost::intrusive_ptr< IAction > _action )
{
	m_actionsCollection.push_back( _action );

} // ActionsQueue::pushBackAction


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IAction >
ActionsQueue::popFrontAction()
{
	boost::intrusive_ptr< IAction > action = m_actionsCollection.front();

	m_actionsCollection.pop_front();

	return action;

} // ActionsQueue::popFrontAction


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
