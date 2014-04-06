
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
#include "landscape_model/ih/components/lm_iplayer_component.hpp"
#include "landscape_model/ih/components/lm_iresource_holder_component.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"


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
	,	boost::shared_ptr< Object > _resourceStorage
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_resourceSource( _resourceSource )
	,	m_resourceStarage( _resourceStorage )
	,	m_collectingTicksCounter( 0 )
{
	assert( m_resourceSource || m_resourceStarage );
	assert( !m_resourceSource || !m_resourceStarage );

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
	return true;

} // CollectResourceAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
CollectResourceAction::processAction()
{
	assert( m_resourceSource || m_resourceStarage );
	assert( !m_resourceSource || !m_resourceStarage );

	// Common variables

	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );
	boost::intrusive_ptr< IPlayerComponent > playerComponent
		= m_object.getComponent< IPlayerComponent >( ComponentId::Player );
	boost::intrusive_ptr< IResourceHolderComponent > resourceHolderComponent
		= m_object.getComponent< IResourceHolderComponent >( ComponentId::ResourceHolder );

	// Check if object is dying

	if ( m_object.getState() == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		boost::shared_ptr< Object > targetObject = getTargetObject();
		boost::intrusive_ptr< ILocateComponent > targetLocateComponent
			= targetObject->getComponent< ILocateComponent >( ComponentId::Locate );

		// Check distance

		if (	Geometry::getDistance(
						locateComponent->getLocation()
					,	Geometry::getNearestPoint(
								locateComponent->getLocation()
							,	targetLocateComponent->getRect() ) )
			>	Geometry::DiagonalDistance )
		{
			IPathFinder::PointsCollection path;
			JumpPointSearch::pathToObject( path, *m_landscapeModel.getLandscape(), m_object, *targetObject, Geometry::DiagonalDistance );

			if ( !path.empty() )
			{
				actionsComponent->pushFrontAction(
					boost::intrusive_ptr< IAction >(
						new MoveAction(
								m_environment
							,	m_landscapeModel
							,	m_object
							,	targetObject
							,	path
							,	Geometry::DiagonalDistance ) ) );
				return;
			}
			else
			{
				m_isInProcessing = false;
			}
		}

		// Do action

		if ( m_isInProcessing )
		{
			if ( m_resourceSource )
			{
				if ( !locateComponent->isHidden() )
				{
				}
			}
			else if ( m_resourceStarage )
			{
			}
		}
	}

} // CollectResourceAction::processAction


/*---------------------------------------------------------------------------*/


const Actions::Enum
CollectResourceAction::getType() const
{
	return Actions::CollectResource;

} // CollectResourceAction::getType


/*---------------------------------------------------------------------------*/


boost::shared_ptr< Object >
CollectResourceAction::getTargetObject() const
{
	assert( m_resourceSource || m_resourceStarage );
	assert( !m_resourceSource || !m_resourceStarage );

	return m_resourceSource ? m_resourceSource : m_resourceStarage;

} // CollectResourceAction::getTargetObject


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
