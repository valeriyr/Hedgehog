
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/actions/gm_move_items_action.hpp"

#include "game_manager/sources/environment/gm_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_iunit.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	const LandscapeModel::Point& _to
	)
	:	BaseAction( _environment )
	,	m_to( _to )
{
} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::~MoveAction()
{
} // MoveAction::~MoveAction


/*---------------------------------------------------------------------------*/


void
MoveAction::doAction()
{
	m_environment.getCurrentLandscape()->moveUnit(
		m_environment.getCurrentLandscape()->getSelectedUnit(), m_to );

} // MoveAction::doAction


/*---------------------------------------------------------------------------*/


void
MoveAction::undoAction()
{
} // MoveAction::undoAction


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
