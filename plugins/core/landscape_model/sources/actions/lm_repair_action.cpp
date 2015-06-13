
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_repair_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"
#include "landscape_model/sources/utils/lm_math.hpp"

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
	Tools::Core::Object::Ptr repairComponent = m_object.getMemberObject( RepairComponent::Name );

	repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject ) = m_target;

	return true;

} // RepairAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
RepairAction::cancelProcessingInternal()
{
	Tools::Core::Object::Ptr repairComponent = m_object.getMemberObject( RepairComponent::Name );

	repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject ).reset();

	return true;

} // RepairAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
RepairAction::processAction()
{
	// Common variables

	Tools::Core::Object::Ptr repairComponent = m_object.getMemberObject( RepairComponent::Name );
	Tools::Core::Object::Ptr locateComponent = m_object.getMemberObject( LocateComponent::Name );
	boost::intrusive_ptr< IActionsComponent > actionsComponent = m_object.getComponent< IActionsComponent >( ComponentId::Actions );
	Tools::Core::Object::Ptr buildComponent = m_object.getMemberObject( BuildComponent::Name );
	Tools::Core::Object::Ptr playerComponent = m_object.getMemberObject( PlayerComponent::Name );

	Tools::Core::Object::Ptr targetHealthComponent
		= repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject )->getMemberObject( HealthComponent::Name );

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying || HealthComponent::isHealthy( *targetHealthComponent ) /*targetHealthComponent->callMethod< bool >( HealthComponent::IsHealthy )*/ )
	{
		m_isInProcessing = false;
	}
	else
	{
		// Check distance

		if (	Geometry::getDistance(
						locateComponent->getMember< QPoint >( LocateComponent::Location )
					,	Geometry::getNearestPoint(
									locateComponent->getMember< QPoint >( LocateComponent::Location )
								,	LocateComponent::getRect( *repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject )
										->getMemberObject( LocateComponent::Name ) ) ) )
			>	Geometry::DiagonalDistance )
		{
			IPathFinder::PointsCollection path;
			JumpPointSearch::pathToObject( path, *m_landscapeModel.getLandscape(), m_object, *repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject ), Geometry::DiagonalDistance );

			if ( !path.empty() )
			{
				actionsComponent->pushFrontAction(
					boost::intrusive_ptr< IAction >(
						new MoveAction(
								m_environment
							,	m_landscapeModel
							,	m_object
							,	repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject )
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
			Tools::Core::Object::Ptr targetLocateComponent
				= repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject )
					->getMemberObject( LocateComponent::Name );

			bool stateChanged = false;

			if ( repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject )->getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
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
				Direction::Enum currentDirection = locateComponent->getMember< Direction::Enum >( LocateComponent::Direction );
				Direction::Enum nextDirection
					= Direction::getDirection(
							locateComponent->getMember< QPoint >( LocateComponent::Location )
						,	Geometry::getNearestPoint( locateComponent->getMember< QPoint >( LocateComponent::Location ), LocateComponent::getRect( *targetLocateComponent ) ) );

				if ( currentDirection != nextDirection )
				{
					locateComponent->getMember< Direction::Enum >( LocateComponent::Direction ) = nextDirection;
					stateChanged = true;
				}

				if ( m_object.getMember< Core::LandscapeModel::ObjectState::Enum >( ObjectStateKey ) != ObjectState::Repairing )
				{
					m_object.getMember< Core::LandscapeModel::ObjectState::Enum >( ObjectStateKey ) = ObjectState::Repairing;
					stateChanged = true;
				}

				m_healthRepaired += repairComponent->getMember< TickType >( StaticDataTools::generateName( RepairComponent::StaticData::HealthByTick ) );
				int repairHealthPercent = Math::calculatePercent( m_healthRepaired, targetHealthComponent->getMember< qint32 >( StaticDataTools::generateName( HealthComponent::StaticData::MaxHealth ) ) );

				if ( repairHealthPercent != 0 )
				{
					boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );

					// TODO: CRASH while repairing wrong building
					ResourcesData repairCostData 
						= buildComponent->getMember< BuildComponent::StaticData::Data::Ptr >( StaticDataTools::generateName( BuildComponent::StaticData::DataKey ) )
							->m_buildDatas.find( repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject )->getMember< QString >( ObjectNameKey ) )
								->second->m_resourcesData.getResourceDataPart( repairComponent->getMember< qint32 >( StaticDataTools::generateName( RepairComponent::StaticData::CostPercent ) ) ).getResourceDataPart( repairHealthPercent );

					if ( player && player->getResourcesData().isEnaught( repairCostData ) )
					{
						player->substructResources( repairCostData );

						//targetHealthComponent->callVoidMethod< const qint32 >( HealthComponent::SetHealth, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) + m_healthRepaired );
						HealthComponent::setHealth( *targetHealthComponent, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) + m_healthRepaired );
						m_healthRepaired = 0;

						m_environment.riseEvent(
							Framework::Core::EventManager::Event( Events::ObjectHealthChanged::Type )
								.pushMember( Events::ObjectHealthChanged::ObjectNameAttribute, repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject )->getMember< QString >( ObjectNameKey ) )
								.pushMember( Events::ObjectHealthChanged::ObjectIdAttribute, repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject )->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
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
							.pushMember( Events::ObjectStateChanged::ObjectDirection, locateComponent->getMember< Direction::Enum >( LocateComponent::Direction ) ) );
				}
			}
		}
	}

	if ( !m_isInProcessing )
	{
		repairComponent->getMember< boost::shared_ptr< GameObject > >( RepairComponent::TargetObject ).reset();
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
