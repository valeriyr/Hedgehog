
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_base_action.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BaseAction::BaseAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	)
	:	m_environment( _environment )
	,	m_landscapeModel( _landscapeModel )
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
