
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_repair_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/geometry/lm_geometry.hpp"

#include "landscape_model/ih/components/lm_irepair_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_ihealth_component.hpp"
#include "landscape_model/ih/components/lm_iactions_component.hpp"
#include "landscape_model/ih/components/lm_ibuild_component.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


RepairAction::RepairAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	boost::shared_ptr< Object > _target
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_target( _target )
{
} // RepairAction::RepairAction


/*---------------------------------------------------------------------------*/


RepairAction::~RepairAction()
{
} // RepairAction::~RepairAction


/*---------------------------------------------------------------------------*/


bool
RepairAction::prepareToProcessingInternal()
{
	boost::intrusive_ptr< IRepairComponent > repairComponent
		= m_object.getComponent< IRepairComponent >( ComponentId::Repair );

	repairComponent->setTargetObject( m_target );

	return true;

} // RepairAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
RepairAction::cancelProcessingInternal()
{
	boost::intrusive_ptr< IRepairComponent > repairComponent
		= m_object.getComponent< IRepairComponent >( ComponentId::Repair );

	repairComponent->setTargetObject( boost::shared_ptr< Object >() );

	return true;

} // RepairAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
RepairAction::processAction( const unsigned int _deltaTime )
{
	// Common variables

	boost::intrusive_ptr< IRepairComponent > repairComponent
		= m_object.getComponent< IRepairComponent >( ComponentId::Repair );
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );
	boost::intrusive_ptr< IBuildComponent > buildComponent
		= m_object.getComponent< IBuildComponent >( ComponentId::Build );

	// Check if object is dying

	if ( m_object.getState() == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		// Check distance

		if (	Geometry::getDistance(
						locateComponent->getLocation()
					,	Geometry::getNearestPoint(
								locateComponent->getLocation()
							,	repairComponent->getTargetObject()->getComponent< ILocateComponent >( ComponentId::Locate )->getRect() ) )
			>	1.5f )
		{
			IPathFinder::PointsCollection path;
			JumpPointSearch::pathToObject( path, *m_landscapeModel.getLandscape(), m_object, *repairComponent->getTargetObject(), 1.5f );

			if ( !path.empty() )
			{
				actionsComponent->pushFrontAction(
					boost::intrusive_ptr< IAction >(
						new MoveAction(
								m_environment
							,	m_landscapeModel
							,	m_object
							,	repairComponent->getTargetObject()
							,	path
							,	1.5f ) ) );
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
			boost::intrusive_ptr< IHealthComponent > targetHealthComponent
				= repairComponent->getTargetObject()->getComponent< IHealthComponent >( ComponentId::Health );
			boost::intrusive_ptr< ILocateComponent > targetLocateComponent
				= repairComponent->getTargetObject()->getComponent< ILocateComponent >( ComponentId::Locate );

			bool stateChanged = false;

			if ( repairComponent->getTargetObject()->getState() == ObjectState::Dying )
			{
				if ( m_object.getState() != ObjectState::Standing )
				{
					m_object.setState( ObjectState::Standing );
					stateChanged = true;
				}

				m_isInProcessing = false;
			}
			else
			{
				Direction::Enum currentDirection = locateComponent->getDirection();
				Direction::Enum nextDirection
					= Direction::getDirection(
							locateComponent->getLocation()
						,	Geometry::getNearestPoint( locateComponent->getLocation(), targetLocateComponent->getRect() ) );

				if ( currentDirection != nextDirection )
				{
					locateComponent->setDirection( nextDirection );
					stateChanged = true;
				}

				if ( m_object.getState() != ObjectState::Repairing )
				{
					m_object.setState( ObjectState::Repairing );
					stateChanged = true;
				}

				const ResourcesData& repairCostData 
					= buildComponent->getStaticData().m_buildDatas.find( repairComponent->getTargetObject()->getName() )
						->second->m_resourcesData.getResourceDataPart( repairComponent->getStaticData().m_costPercent );

				int repairHealth = repairComponent->getStaticData().m_healthBySecond * _deltaTime / 1000;

				targetHealthComponent->setHealth( targetHealthComponent->getHealth() + repairHealth );

				Framework::Core::EventManager::Event objectDataChangedEvent( Events::ObjectDataChanged::ms_type );
				objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectNameAttribute, repairComponent->getTargetObject()->getName() );
				objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectIdAttribute, repairComponent->getTargetObject()->getUniqueId() );
				objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectHealth, targetHealthComponent->getHealth() );

				m_environment.riseEvent( objectDataChangedEvent );

				if ( targetHealthComponent->getHealth() == targetHealthComponent->getStaticData().m_maximumHealth )
				{
					m_object.setState( ObjectState::Standing );
					stateChanged = true;

					m_isInProcessing = false;
				}

				if ( stateChanged )
				{
					Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

					m_environment.riseEvent( objectStateChangedEvent );
				}
			}
		}
	}

	if ( !m_isInProcessing )
	{
		repairComponent->setTargetObject( boost::shared_ptr< Object >() );
	}

} // RepairAction::processAction


/*---------------------------------------------------------------------------*/


const Actions::Enum
RepairAction::getType() const
{
	return Actions::Repair;

} // RepairAction::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
