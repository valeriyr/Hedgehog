
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/game_manager/gm_game_manager.hpp"

#include "game_manager/sources/actions_queue/gm_iactions_queue.hpp"

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
} // GameManager::run


/*---------------------------------------------------------------------------*/


void
GameManager::stop()
{
} // GameManager::stop


/*---------------------------------------------------------------------------*/


void
GameManager::pushMoveAction(
		boost::intrusive_ptr< LandscapeModel::IUnit > _unit
	,	const LandscapeModel::Point& _moveTo )
{
} // GameManager::pushMoveAction


/*---------------------------------------------------------------------------*/


void
GameManager::pushSelectAction(
		const LandscapeModel::Point& _from
	,	const LandscapeModel::Point& _to )
{
} // GameManager::pushSelectAction


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
