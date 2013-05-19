
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/actions/gm_select_items_action.hpp"

#include "game_manager/sources/environment/gm_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


SelectAction::SelectAction(
		const IEnvironment& _environment
	,	const LandscapeModel::Point& _from
	,	const LandscapeModel::Point& _to
	)
	:	BaseAction( _environment )
	,	m_from( _from )
	,	m_to( _to )
{
} // SelectAction::SelectAction


/*---------------------------------------------------------------------------*/


SelectAction::~SelectAction()
{
} // SelectAction::~SelectAction


/*---------------------------------------------------------------------------*/


void
SelectAction::doAction()
{
	m_environment.getCurrentLandscape()->setSelectedUnit( m_to );

} // SelectAction::doAction


/*---------------------------------------------------------------------------*/


void
SelectAction::undoAction()
{
} // SelectAction::undoAction


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
