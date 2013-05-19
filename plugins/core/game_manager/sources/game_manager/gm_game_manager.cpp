
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/game_manager/gm_game_manager.hpp"

#include "game_manager/sources/actions_queue/gm_iactions_queue.hpp"
#include "game_manager/sources/environment/gm_ienvironment.hpp"

#include "game_manager/sources/actions/gm_move_items_action.hpp"
#include "game_manager/sources/actions/gm_select_items_action.hpp"

#include "landscape_model/ih/lm_iunit.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


GameManager::GameManager(
		const IEnvironment& _environment
	,	boost::intrusive_ptr< IActionsQueue > _actionsQueue
	)
	:	m_environment( _environment )
	,	m_actionsQueue( _actionsQueue )
{
} // GameManager::GameManager


/*---------------------------------------------------------------------------*/


GameManager::~GameManager()
{
} // GameManager::~GameManager


/*---------------------------------------------------------------------------*/


void
GameManager::run()
{
	m_environment.runThread( "actionsProcessingLoop", boost::bind( &GameManager::runActionsProcessing, this ) );

} // GameManager::run


/*---------------------------------------------------------------------------*/


void
GameManager::stop()
{
	m_environment.stopThread( "actionsProcessingLoop" );

} // GameManager::stop


/*---------------------------------------------------------------------------*/


void
GameManager::pushMoveAction( const LandscapeModel::Point& _moveTo )
{
	m_actionsQueue->pushBackAction(
		boost::intrusive_ptr< IAction >( new MoveAction( m_environment, _moveTo ) ) );

} // GameManager::pushMoveAction


/*---------------------------------------------------------------------------*/


void
GameManager::pushSelectAction(
		const LandscapeModel::Point& _from
	,	const LandscapeModel::Point& _to )
{
	m_actionsQueue->pushBackAction(
		boost::intrusive_ptr< IAction >( new SelectAction( m_environment, _from, _to ) ) );

} // GameManager::pushSelectAction


/*---------------------------------------------------------------------------*/


void
GameManager::runActionsProcessing()
{
	while( m_actionsQueue->hasActions() )
	{
		boost::intrusive_ptr< IAction > action = m_actionsQueue->popFrontAction();

		action->doAction();
	}

} // GameManager::runActionsProcessing


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
