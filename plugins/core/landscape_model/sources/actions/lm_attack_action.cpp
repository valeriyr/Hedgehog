
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_attack_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/geometry/lm_geometry.hpp"

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
	,	Object& _object
	,	boost::shared_ptr< Object > _target
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

	attackComponent->setTargetObject( boost::shared_ptr< Object >() );

	return true;

} // AttackAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
AttackAction::processAction( const unsigned int _deltaTime )
{
	// Common variables

	boost::intrusive_ptr< IAttackComponent > attackComponent
		= m_object.getComponent< IAttackComponent >( ComponentId::Attack );
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IActionsComponent > actionsComponent
		= m_object.getComponent< IActionsComponent >( ComponentId::Actions );

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

			if ( attackComponent->getTargetObject()->getState() == ObjectState::Dying )
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
						,	Geometry::getNearestPoint( locateComponent->getLocation(), targetObjectLocate->getRect() ) );

				if ( currentDirection != nextDirection )
				{
					locateComponent->setDirection( nextDirection );
					stateChanged = true;
				}

				if ( m_object.getState() != ObjectState::Attacking )
				{
					m_object.setState( ObjectState::Attacking );
					stateChanged = true;
					readyToAttack = true;
				}

				int prevAttackPhaseCounter = m_attackPhaseCounter;
				m_attackPhaseCounter += _deltaTime;

				if ( m_attackPhaseCounter >= attackComponent->getStaticData().m_aiming + attackComponent->getStaticData().m_reloading )
				{
					m_attackPhaseCounter = 0;
					readyToAttack = true;
				}
				else if ( prevAttackPhaseCounter < attackComponent->getStaticData().m_aiming && m_attackPhaseCounter >= attackComponent->getStaticData().m_aiming )
				{
					boost::intrusive_ptr< IHealthComponent > targetHealthComponent
						= attackComponent->getTargetObject()->getComponent< IHealthComponent >( ComponentId::Health );

					int damageBonus = attackComponent->getStaticData().m_maxDamage - attackComponent->getStaticData().m_minDamage;

					int damage = attackComponent->getStaticData().m_minDamage + ( rand() % damageBonus ) + 1;

					targetHealthComponent->setHealth( targetHealthComponent->getHealth() - damage );

					Framework::Core::EventManager::Event objectDataChangedEvent( Events::ObjectDataChanged::ms_type );
					objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectNameAttribute, attackComponent->getTargetObject()->getName() );
					objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectIdAttribute, attackComponent->getTargetObject()->getUniqueId() );
					objectDataChangedEvent.pushAttribute( Events::ObjectDataChanged::ms_objectHealth, targetHealthComponent->getHealth() );

					m_environment.riseEvent( objectDataChangedEvent );

					Framework::Core::EventManager::Event objectWasHitEvent( Events::ObjectWasHit::ms_type );
					objectWasHitEvent.pushAttribute( Events::ObjectWasHit::ms_objectNameAttribute, attackComponent->getTargetObject()->getName() );
					objectWasHitEvent.pushAttribute( Events::ObjectWasHit::ms_objectIdAttribute, attackComponent->getTargetObject()->getUniqueId() );
					objectWasHitEvent.pushAttribute( Events::ObjectWasHit::ms_objectHealth, targetHealthComponent->getHealth() );

					m_environment.riseEvent( objectWasHitEvent );

					if ( targetHealthComponent->getHealth() == 0 )
					{
						attackComponent->getTargetObject()->setState( ObjectState::Dying );
						attackComponent->getTargetObject()->getComponent< IActionsComponent >( ComponentId::Actions )->flushActions( IActionsComponent::FlushPolicy::Force );

						Framework::Core::EventManager::Event targetObjectStateChangedEvent( Events::ObjectStateChanged::ms_type );
						targetObjectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, attackComponent->getTargetObject()->getName() );
						targetObjectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, attackComponent->getTargetObject()->getUniqueId() );
						targetObjectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, attackComponent->getTargetObject()->getState() );
						targetObjectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, targetObjectLocate->getDirection() );

						m_environment.riseEvent( targetObjectStateChangedEvent );

						m_object.setState( ObjectState::Standing );
						stateChanged = true;

						m_isInProcessing = false;
					}
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

				if ( readyToAttack )
				{
					Framework::Core::EventManager::Event objectReadyToAttackEvent( Events::ObjectReadyToAttack::ms_type );
					objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectNameAttribute, m_object.getName() );
					objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectIdAttribute, m_object.getUniqueId() );
					objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectDirection, locateComponent->getDirection() );

					m_environment.riseEvent( objectReadyToAttackEvent );
				}
			}
		}
	}

	if ( !m_isInProcessing )
	{
		attackComponent->setTargetObject( boost::shared_ptr< Object >() );
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
