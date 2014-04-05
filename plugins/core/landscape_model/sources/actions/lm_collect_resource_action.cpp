
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_collect_resource_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iactions_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


CollectResourceAction::CollectResourceAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	boost::shared_ptr< Object > _resourceSource
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_resourceSource( _resourceSource )
{
} // CollectResourceAction::CollectResourceAction


/*---------------------------------------------------------------------------*/


CollectResourceAction::~CollectResourceAction()
{
} // CollectResourceAction::~CollectResourceAction


/*---------------------------------------------------------------------------*/


bool
CollectResourceAction::prepareToProcessingInternal()
{
	/*boost::intrusive_ptr< IAttackComponent > attackComponent
		= m_object.getComponent< IAttackComponent >( ComponentId::Attack );

	attackComponent->setTargetObject( m_target );*/

	return true;

} // CollectResourceAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
CollectResourceAction::cancelProcessingInternal()
{
	/*boost::intrusive_ptr< IAttackComponent > attackComponent
		= m_object.getComponent< IAttackComponent >( ComponentId::Attack );

	attackComponent->setTargetObject( boost::shared_ptr< Object >() );*/

	return true;

} // CollectResourceAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
CollectResourceAction::processAction()
{

} // CollectResourceAction::processAction


/*---------------------------------------------------------------------------*/


const Actions::Enum
CollectResourceAction::getType() const
{
	return Actions::CollectResource;

} // CollectResourceAction::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
