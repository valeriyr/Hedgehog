
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_attack_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iactions_component.hpp"

#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


AttackAction::AttackAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	GameObject& _object
	,	boost::shared_ptr< GameObject > _target
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_target( _target )
	,	m_attackPhaseCounter( 0 )
{
} // AttackAction::AttackAction


/*---------------------------------------------------------------------------*/


AttackAction::~AttackAction()
{
} // AttackAction::~AttackAction


/*---------------------------------------------------------------------------*/


bool
AttackAction::prepareToProcessingInternal()
{
	Tools::Core::Object::Ptr attackComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( AttackComponent::Name );

	attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject ) = m_target;

	return true;

} // AttackAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
AttackAction::cancelProcessingInternal()
{
	Tools::Core::Object::Ptr attackComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( AttackComponent::Name );

	attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject ).reset();

	return true;

} // AttackAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
AttackAction::processAction()
{
	// Common variables

	Tools::Core::Object::Ptr attackComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( AttackComponent::Name );
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );

	const qint32 distance = attackComponent->getMember< qint32 >( StaticDataTools::generateName( AttackComponent::StaticData::Distance ) );
	const qint32 minDamage = attackComponent->getMember< qint32 >( StaticDataTools::generateName( AttackComponent::StaticData::MinDamage ) );
	const qint32 maxDamage = attackComponent->getMember< qint32 >( StaticDataTools::generateName( AttackComponent::StaticData::MaxDamage ) );

	const TickType aiming = attackComponent->getMember< TickType >( StaticDataTools::generateName( AttackComponent::StaticData::Aiming ) );
	const TickType reloading = attackComponent->getMember< TickType >( StaticDataTools::generateName( AttackComponent::StaticData::Reloading ) );

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
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
							,	attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getComponent< ILocateComponent >( ComponentId::Locate )->getRect() ) )
			>	distance )
		{
			IPathFinder::PointsCollection path;
			JumpPointSearch::pathToObject(
					path
				,	*m_landscapeModel.getLandscape()
				,	m_object
				,	*attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )
				,	distance );

			if ( !path.empty() )
			{
				actionsComponent->pushFrontAction(
					boost::intrusive_ptr< IAction >(
						new MoveAction(
								m_environment
							,	m_landscapeModel
							,	m_object
							,	attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )
							,	path
							,	distance ) ) );
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
			boost::intrusive_ptr< ILocateComponent > targetObjectLocate
				= attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getComponent< ILocateComponent >( ComponentId::Locate );

			bool stateChanged = false;
			bool readyToAttack = false;

			if (attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
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
						,	Geometry::getNearestPoint( locateComponent->getLocation(), targetObjectLocate->getRect() ) );

				if ( currentDirection != nextDirection )
				{
					locateComponent->setDirection( nextDirection );
					stateChanged = true;
				}

				if ( targetObjectLocate->isHidden() )
				{
					m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;
					stateChanged = true;

					m_isInProcessing = false;
				}
				else if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) != ObjectState::Attacking )
				{
					m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Attacking;
					stateChanged = true;
					readyToAttack = true;
				}

				TickType prevAttackPhaseCounter = m_attackPhaseCounter;
				++m_attackPhaseCounter;

				
				if (	m_isInProcessing
					&&	m_attackPhaseCounter >= ( aiming + reloading ) )
				{
					m_attackPhaseCounter = 0;
					readyToAttack = true;
				}
				else if (	m_isInProcessing
						&&	prevAttackPhaseCounter < aiming
						&& m_attackPhaseCounter >= aiming )
				{
					Tools::Core::Object::Ptr targetHealthComponent
						= attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< Tools::Core::Object::Ptr >( HealthComponent::Name );

					qint32 damageBonus = maxDamage - minDamage;

					qint32 damage = minDamage + ( rand() % ( damageBonus + 1 ) );

					//targetHealthComponent->callVoidMethod< const qint32 >( HealthComponent::SetHealth, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) - damage );
					HealthComponent::setHealth( *targetHealthComponent, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) - damage );

					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ObjectHealthChanged::Type )
							.pushMember( Events::ObjectHealthChanged::ObjectNameAttribute, attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< QString >( ObjectNameKey ) )
							.pushMember( Events::ObjectHealthChanged::ObjectIdAttribute, attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ObjectHealthChanged::ObjectHealth, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) ) );

					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ObjectWasHit::Type )
							.pushMember( Events::ObjectWasHit::ObjectNameAttribute,attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< QString >( ObjectNameKey ) )
							.pushMember( Events::ObjectWasHit::ObjectIdAttribute, attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ObjectWasHit::ObjectHealth, targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) ) );

					if ( targetHealthComponent->getMember< qint32 >( HealthComponent::Health ) == 0 )
					{
						attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Dying;
						attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getComponent< IActionsComponent >( ComponentId::Actions )->flushActions( IActionsComponent::FlushPolicy::Force );

						m_environment.riseEvent(
							Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
								.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< QString >( ObjectNameKey ) )
								.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
								.pushMember( Events::ObjectStateChanged::ObjectState, attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject )->getMember< ObjectState::Enum >( ObjectStateKey ) )
								.pushMember( Events::ObjectStateChanged::ObjectDirection, targetObjectLocate->getDirection() ) );

						m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;
						stateChanged = true;

						m_isInProcessing = false;
					}
				}

				if ( stateChanged )
				{
					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
							.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, m_object.getMember< QString >( ObjectNameKey ) )
							.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ObjectStateChanged::ObjectState, m_object.getMember< ObjectState::Enum >( ObjectStateKey ) )
							.pushMember( Events::ObjectStateChanged::ObjectDirection, locateComponent->getDirection() ) );
				}

				if ( readyToAttack )
				{
					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ObjectReadyToAttack::Type )
							.pushMember( Events::ObjectReadyToAttack::ObjectNameAttribute, m_object.getMember< QString >( ObjectNameKey ) )
							.pushMember( Events::ObjectReadyToAttack::ObjectIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ObjectReadyToAttack::ObjectDirection, locateComponent->getDirection() ) );
				}
			}
		}
	}

	if ( !m_isInProcessing )
	{
		attackComponent->getMember< boost::shared_ptr< GameObject > >( AttackComponent::TargetObject ).reset();
	}

} // AttackAction::processAction


/*---------------------------------------------------------------------------*/


const Actions::Enum
AttackAction::getType() const
{
	return Actions::Attack;

} // AttackAction::getType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
