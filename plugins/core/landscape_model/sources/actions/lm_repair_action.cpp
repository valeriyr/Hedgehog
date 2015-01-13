
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_repair_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"
#include "landscape_model/sources/utils/lm_math.hpp"

#include "landscape_model/ih/components/lm_irepair_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_ihealth_component.hpp"
#include "landscape_model/ih/components/lm_iactions_component.hpp"
#include "landscape_model/ih/components/lm_ibuild_component.hpp"
#include "landscape_model/ih/components/lm_iplayer_component.hpp"

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
	,	m_healthRepaired( 0 )
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
RepairAction::processAction()
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
	boost::intrusive_ptr< IPlayerComponent > playerComponent
		= m_object.getComponent< IPlayerComponent >( ComponentId::Player );

	boost::intrusive_ptr< IHealthComponent > targetHealthComponent
		= repairComponent->getTargetObject()->getComponent< IHealthComponent >( ComponentId::Health );

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying || targetHealthComponent->isHealthy() )
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
			>	Geometry::DiagonalDistance )
		{
			IPathFinder::PointsCollection path;
			JumpPointSearch::pathToObject( path, *m_landscapeModel.getLandscape(), m_object, *repairComponent->getTargetObject(), Geometry::DiagonalDistance );

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
			boost::intrusive_ptr< ILocateComponent > targetLocateComponent
				= repairComponent->getTargetObject()->getComponent< ILocateComponent >( ComponentId::Locate );

			bool stateChanged = false;

			if ( repairComponent->getTargetObject()->getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
			{
				if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) != ObjectState::Standing )
				{
					m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;
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

				if ( m_object.getMember< Core::LandscapeModel::ObjectState::Enum >( ObjectStateKey ) != ObjectState::Repairing )
				{
					m_object.getMember< Core::LandscapeModel::ObjectState::Enum >( ObjectStateKey ) = ObjectState::Repairing;
					stateChanged = true;
				}

				m_healthRepaired += repairComponent->getStaticData().m_healthByTick;
				int repairHealthPercent = Math::calculatePercent( m_healthRepaired, targetHealthComponent->getStaticData().m_maximumHealth );

				if ( repairHealthPercent != 0 )
				{
					boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getPlayerId() );

					// TODO: CRASH while repairing wrong building
					ResourcesData repairCostData 
						= buildComponent->getStaticData().m_buildDatas.find( repairComponent->getTargetObject()->getMember< QString >( ObjectNameKey ) )
							->second->m_resourcesData.getResourceDataPart( repairComponent->getStaticData().m_costPercent ).getResourceDataPart( repairHealthPercent );

					if ( player && player->getResourcesData().isEnaught( repairCostData ) )
					{
						player->substructResources( repairCostData );

						targetHealthComponent->setHealth( targetHealthComponent->getHealth() + m_healthRepaired );
						m_healthRepaired = 0;

						m_environment.riseEvent(
							Framework::Core::EventManager::Event( Events::ObjectHealthChanged::ms_type )
								.pushMember( Events::ObjectHealthChanged::ms_objectNameAttribute, repairComponent->getTargetObject()->getMember< QString >( ObjectNameKey ) )
								.pushMember( Events::ObjectHealthChanged::ms_objectIdAttribute, repairComponent->getTargetObject()->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
								.pushMember( Events::ObjectHealthChanged::ms_objectHealth, targetHealthComponent->getHealth() ) );

						if ( targetHealthComponent->getHealth() == targetHealthComponent->getStaticData().m_maximumHealth )
						{
							m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;
							stateChanged = true;

							m_isInProcessing = false;
						}
					}
					else
					{
						m_isInProcessing = false;
					}
				}

				if ( stateChanged )
				{
					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ObjectStateChanged::ms_type )
							.pushMember( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getMember< QString >( ObjectNameKey ) )
							.pushMember( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ObjectStateChanged::ms_objectState, m_object.getMember< Core::LandscapeModel::ObjectState::Enum >( ObjectStateKey ) )
							.pushMember( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() ) );
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
