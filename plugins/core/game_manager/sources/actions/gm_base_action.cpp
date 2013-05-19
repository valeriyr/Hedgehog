
#include "game_manager/sources/ph/gm_ph.hpp"

#include "game_manager/sources/actions/gm_base_action.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/


BaseAction::BaseAction( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // BaseAction::BaseAction


/*---------------------------------------------------------------------------*/


BaseAction::~BaseAction()
{
} // BaseAction::~BaseAction


/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
