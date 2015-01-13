
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_attack_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"

#include "landscape_model/ih/components/lm_iattack_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_ihealth_component.hpp"
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
	boost::intrusive_ptr< IAttackComponent > attackComponent
		= m_object.getComponent< IAttackComponent >( ComponentId::Attack );

	attackComponent->setTargetObject( m_target );

	return true;

} // AttackAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
AttackAction::cancelProcessingInternal()
{
	boost::intrusive_ptr< IAttackComponent > attackComponent
		= m_object.getComponent< IAttackComponent >( ComponentId::Attack );

	attackComponent->setTargetObject( boost::shared_ptr< GameObject >() );

	return true;

} // AttackAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
AttackAction::processAction()
{
	// Common variables

	boost::intrusive_ptr< IAttackComponent > attackComponent
		= m_object.getComponent< IAttackComponent >( ComponentId::Attack );
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );

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
							,	attackComponent->getTargetObject()->getComponent< ILocateComponent >( ComponentId::Locate )->getRect() ) )
			>	attackComponent->getStaticData().m_distance )
		{
			IPathFinder::PointsCollection path;
			JumpPointSearch::pathToObject( path, *m_landscapeModel.getLandscape(), m_object, *attackComponent->getTargetObject(), attackComponent->getStaticData().m_distance );

			if ( !path.empty() )
			{
				actionsComponent->pushFrontAction(
					boost::intrusive_ptr< IAction >(
						new MoveAction(
								m_environment
							,	m_landscapeModel
							,	m_object
							,	attackComponent->getTargetObject()
							,	path
							,	attackComponent->getStaticData().m_distance ) ) );
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
				= attackComponent->getTargetObject()->getComponent< ILocateComponent >( ComponentId::Locate );

			bool stateChanged = false;
			bool readyToAttack = false;

			if ( attackComponent->getTargetObject()->getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
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
					&&	m_attackPhaseCounter >= ( attackComponent->getStaticData().m_aiming + attackComponent->getStaticData().m_reloading ) )
				{
					m_attackPhaseCounter = 0;
					readyToAttack = true;
				}
				else if (	m_isInProcessing
						&&	prevAttackPhaseCounter < attackComponent->getStaticData().m_aiming
						&& m_attackPhaseCounter >= attackComponent->getStaticData().m_aiming )
				{
					boost::intrusive_ptr< IHealthComponent > targetHealthComponent
						= attackComponent->getTargetObject()->getComponent< IHealthComponent >( ComponentId::Health );

					int damageBonus = attackComponent->getStaticData().m_maxDamage - attackComponent->getStaticData().m_minDamage;

					int damage = attackComponent->getStaticData().m_minDamage + ( rand() % ( damageBonus + 1 ) );

					targetHealthComponent->setHealth( targetHealthComponent->getHealth() - damage );

					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ObjectHealthChanged::Type )
							.pushMember( Events::ObjectHealthChanged::ObjectNameAttribute, attackComponent->getTargetObject()->getMember< QString >( ObjectNameKey ) )
							.pushMember( Events::ObjectHealthChanged::ObjectIdAttribute, attackComponent->getTargetObject()->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ObjectHealthChanged::ObjectHealth, targetHealthComponent->getHealth() ) );

					m_environment.riseEvent(
						Framework::Core::EventManager::Event( Events::ObjectWasHit::Type )
							.pushMember( Events::ObjectWasHit::ObjectNameAttribute, attackComponent->getTargetObject()->getMember< QString >( ObjectNameKey ) )
							.pushMember( Events::ObjectWasHit::ObjectIdAttribute, attackComponent->getTargetObject()->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
							.pushMember( Events::ObjectWasHit::ObjectHealth, targetHealthComponent->getHealth() ) );

					if ( targetHealthComponent->getHealth() == 0 )
					{
						attackComponent->getTargetObject()->getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Dying;
						attackComponent->getTargetObject()->getComponent< IActionsComponent >( ComponentId::Actions )->flushActions( IActionsComponent::FlushPolicy::Force );

						m_environment.riseEvent(
							Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
								.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, attackComponent->getTargetObject()->getMember< QString >( ObjectNameKey ) )
								.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, attackComponent->getTargetObject()->getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
								.pushMember( Events::ObjectStateChanged::ObjectState, attackComponent->getTargetObject()->getMember< ObjectState::Enum >( ObjectStateKey ) )
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
		attackComponent->setTargetObject( boost::shared_ptr< GameObject >() );
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
