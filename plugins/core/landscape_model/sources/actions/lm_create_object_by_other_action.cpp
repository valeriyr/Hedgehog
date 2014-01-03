
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_create_object_by_other_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/h/lm_events.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


CreateObjectByOtherAction::CreateObjectByOtherAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	)
	:	BaseAction( _environment, _landscapeModel )
{
} // CreateObjectByOtherAction::CreateObjectByOtherAction


/*---------------------------------------------------------------------------*/


CreateObjectByOtherAction::~CreateObjectByOtherAction()
{
} // CreateObjectByOtherAction::~CreateObjectByOtherAction


/*---------------------------------------------------------------------------*/


void
CreateObjectByOtherAction::processAction( const unsigned int _deltaTime )
{

} // CreateObjectByOtherAction::processAction


/*---------------------------------------------------------------------------*/


void
CreateObjectByOtherAction::unprocessAction( const unsigned int /*_deltaTime*/ )
{
} // CreateObjectByOtherAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
CreateObjectByOtherAction::hasFinished() const
{
	return true;

} // CreateObjectByOtherAction::hasFinished


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
