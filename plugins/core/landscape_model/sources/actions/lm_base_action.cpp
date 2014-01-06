
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_base_action.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BaseAction::BaseAction(
		const IEnvironment& _environment
	,	Object& _object
	)
	:	m_environment( _environment )
	,	m_object( _object )
{
} // BaseAction::BaseAction


/*---------------------------------------------------------------------------*/


BaseAction::~BaseAction()
{
} // BaseAction::~BaseAction


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
