
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
#include "landscape_model/ih/components/lm_iactions_component.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


RepairAction::RepairAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	GameObject& _object
	,	boost::shared_ptr< GameObject > _target
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

	repairComponent->setTargetObject( boost::shared_ptr< GameObject >() );

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
	Tools::Core::Object::Ptr buildComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( BuildComponent::Name );
	Tools::Core::Object::Ptr playerComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

	Tools::Core::Object::Ptr targetHealthComponent
		= repairComponent->getTargetObject()->getMember< Tools::Core::Object::Ptr >( HealthComponent::Name );

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying || HealthComponent::isHealthy( *targetHealthComponent ) /*targetHealthComponent->callMethod< bool >( HealthComponent::IsHealthy )*/ )
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
				int repairHealthPercent = Math::calculatePercent( m_healthRepaired, targetHealthComponent->getMember< qint32 >( StaticDataTools::generateName( HealthComponent::StaticData::MaxHealth ) ) );

				if ( repairHealthPercent != 0 )
				{
					boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );

					// TODO: CRASH while repairing wrong building
					ResourcesData repairCostData 
						= buildComponent->getMember< BuildComponent::StaticData::Data::Ptr >( StaticDataTools::generateName( BuildComponent::StaticData::DataKey ) )
							->m_buildDatas.find( repairComponent->getTargetObject()->getMember< QString >( ObjectNameKey ) )
								->second->m_resourcesData.getResourceDataPart( repairComponent->getStaticData().m_costPercent ).getResourceDataPart( repairHealthPercent );

					if ( player && player->getResourcesData().isEnaught( repairCostData ) )
					{
						player->substructResources( repairCostData );

						//targetHealthComponent->callVoidMethod< const qint32 >( HealthComponent::SetHealth, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) + m_healthRepaired );
						HealthComponent::setHealth( *targetHealthComponent, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) + m_healthRepaired );
						m_healthRepaired = 0;

						m_environment.riseEvent(
							Framework::Core::EventManager::Event( Events::ObjectHealthChanged::Type )
								.pushMember( Events::ObjectHealthChanged::ObjectNameAttribute, repairComponent->getTargetObject()->getMember< QString >( ObjectNameKey ) )
								.pushMember( Events::ObjectHealthChanged::ObjectIdAttribute, repairComponent->getTargetObject()->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
								.pushMember( Events::ObjectHealthChanged::ObjectHealth, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) ) );

						//if ( targetHealthComponent->callMethod< bool >( HealthComponent::IsHealthy ) )
						if ( HealthComponent::isHealthy( *targetHealthComponent ) )
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
						Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
							.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, m_object.getMember< QString >( ObjectNameKey ) )
							.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ObjectStateChanged::ObjectState, m_object.getMember< Core::LandscapeModel::ObjectState::Enum >( ObjectStateKey ) )
							.pushMember( Events::ObjectStateChanged::ObjectDirection, locateComponent->getDirection() ) );
				}
			}
		}
	}

	if ( !m_isInProcessing )
	{
		repairComponent->setTargetObject( boost::shared_ptr< GameObject >() );
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
