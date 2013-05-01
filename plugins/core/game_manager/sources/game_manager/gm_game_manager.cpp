
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/game_manager/gm_game_manager.hpp"

#include "landscape_model/ih/lm_iunit.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


GameManager::GameManager()
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

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
