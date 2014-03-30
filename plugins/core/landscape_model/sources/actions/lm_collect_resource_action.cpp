
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_collect_resource_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/geometry/lm_geometry.hpp"


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
	,	m_collectingFinished( false )
	,	m_moveAction()
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
	return true;

} // CollectResourceAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
CollectResourceAction::cancelProcessingInternal()
{
	m_collectingFinished = true;

	return !m_moveAction || m_moveAction->cancelProcessing();

} // CollectResourceAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
CollectResourceAction::processAction( const unsigned int _deltaTime )
{
} // CollectResourceAction::processAction


/*---------------------------------------------------------------------------*/


bool
CollectResourceAction::hasFinished() const
{
	return ( !m_moveAction || m_moveAction->hasFinished() ) && m_collectingFinished;

} // CollectResourceAction::hasFinished


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
