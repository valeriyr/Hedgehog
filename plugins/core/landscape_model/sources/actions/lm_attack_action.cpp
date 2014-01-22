
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_attack_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


AttackAction::AttackAction(
		const IEnvironment& _environment
	,	Object& _object
	,	IPlayer& _player
	,	ILandscape& _landscape
	,	boost::intrusive_ptr< IPathFinder > _pathFinder
	)
	:	BaseAction( _environment, _object )
	,	m_player( _player )
	,	m_landscape( _landscape )
	,	m_pathFinder( _pathFinder )
	,	m_moveAction()
	,	m_attakingFinished( false )
	,	m_attackPhaseCounter( 0 )
{
} // AttackAction::AttackAction


/*---------------------------------------------------------------------------*/


AttackAction::~AttackAction()
{
} // AttackAction::~AttackAction


/*---------------------------------------------------------------------------*/


void
AttackAction::processAction( const unsigned int _deltaTime )
{
	boost::intrusive_ptr< IAttackComponent > attackComponent
		= m_object.getComponent< IAttackComponent >( ComponentId::Attack );
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );

	boost::intrusive_ptr< ILocateComponent > targetObjectLocate
		= attackComponent->getTargetObject()->getComponent< ILocateComponent >( ComponentId::Locate );

	QPoint point = locateComponent->getLocation() - targetObjectLocate->getLocation();

	if ( ( (int)sqrt(pow((double)point.x(), 2) + pow((double)point.y(), 2)) > attackComponent->getStaticData().m_distance ) && !m_moveAction )
	{
		boost::intrusive_ptr< IMoveComponent > moveComponent
			= m_object.getComponent< IMoveComponent >( ComponentId::Move );
		moveComponent->getMovingData().m_movingToObject = attackComponent->getTargetObject();

		m_moveAction.reset( new MoveAction( m_environment, m_object, m_landscape, m_pathFinder, attackComponent->getStaticData().m_distance ) );
	}

	if ( m_moveAction )
	{
		m_moveAction->processAction( _deltaTime );

		if ( m_moveAction->hasFinished() )
		{
			m_moveAction.reset();
		}
	}
	else
	{
		if ( attackComponent->getTargetObject()->getState() == ObjectState::Dying )
		{
			if ( m_object.getState() != ObjectState::Standing )
			{
				m_object.setState( ObjectState::Standing );

				Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

				m_environment.riseEvent( objectStateChangedEvent );
			}

			m_attakingFinished = true;
		}
		else
		{
			if ( m_object.getState() != ObjectState::Attacking )
			{
				m_object.setState( ObjectState::Attacking );

				Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
				objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

				m_environment.riseEvent( objectStateChangedEvent );

				Framework::Core::EventManager::Event objectReadyToAttackEvent( Events::ObjectReadyToAttack::ms_type );
				objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectNameAttribute, m_object.getName() );
				objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectIdAttribute, m_object.getUniqueId() );
				objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectDirection, locateComponent->getDirection() );

				m_environment.riseEvent( objectReadyToAttackEvent );
			}

			int prevAttackPhaseCounter = m_attackPhaseCounter;
			m_attackPhaseCounter += _deltaTime;

			if ( m_attackPhaseCounter >= attackComponent->getStaticData().m_aiming + attackComponent->getStaticData().m_reloading )
			{
				m_attackPhaseCounter = 0;

				Framework::Core::EventManager::Event objectReadyToAttackEvent( Events::ObjectReadyToAttack::ms_type );
				objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectNameAttribute, m_object.getName() );
				objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectIdAttribute, m_object.getUniqueId() );
				objectReadyToAttackEvent.pushAttribute( Events::ObjectReadyToAttack::ms_objectDirection, locateComponent->getDirection() );

				m_environment.riseEvent( objectReadyToAttackEvent );
			}
			else if ( prevAttackPhaseCounter < attackComponent->getStaticData().m_aiming && m_attackPhaseCounter >= attackComponent->getStaticData().m_aiming )
			{
				boost::intrusive_ptr< IHealthComponent > targetHealthComponent
					= attackComponent->getTargetObject()->getComponent< IHealthComponent >( ComponentId::Health );

				int damageBonus = attackComponent->getStaticData().m_maxDamage - attackComponent->getStaticData().m_minDamage;

				int damage = attackComponent->getStaticData().m_minDamage + ( rand() % damageBonus ) + 1;

				targetHealthComponent->setHealth( targetHealthComponent->getHealth() - damage );

				Framework::Core::EventManager::Event objectWasHitEvent( Events::ObjectWasHit::ms_type );
				objectWasHitEvent.pushAttribute( Events::ObjectWasHit::ms_objectNameAttribute, attackComponent->getTargetObject()->getName() );
				objectWasHitEvent.pushAttribute( Events::ObjectWasHit::ms_objectIdAttribute, attackComponent->getTargetObject()->getUniqueId() );
				objectWasHitEvent.pushAttribute( Events::ObjectWasHit::ms_objectHealth, targetHealthComponent->getHealth() );

				m_environment.riseEvent( objectWasHitEvent );

				if ( targetHealthComponent->getHealth() == 0 )
				{
					attackComponent->getTargetObject()->setState( ObjectState::Dying );

					Framework::Core::EventManager::Event targetObjectStateChangedEvent( Events::ObjectStateChanged::ms_type );
					targetObjectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, attackComponent->getTargetObject()->getName() );
					targetObjectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, attackComponent->getTargetObject()->getUniqueId() );
					targetObjectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, attackComponent->getTargetObject()->getState() );
					targetObjectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, targetObjectLocate->getDirection() );

					m_environment.riseEvent( targetObjectStateChangedEvent );

					m_object.setState( ObjectState::Standing );

					Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

					m_environment.riseEvent( objectStateChangedEvent );

					m_attakingFinished = true;
				}
			}
		}
	}

} // AttackAction::processAction


/*---------------------------------------------------------------------------*/


void
AttackAction::unprocessAction( const unsigned int _deltaTime )
{
} // AttackAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
AttackAction::hasFinished() const
{
	return ( !m_moveAction || m_moveAction->hasFinished() ) && m_attakingFinished;

} // AttackAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
AttackAction::getType() const
{
	return Actions::Attack;

} // AttackAction::getType


/*---------------------------------------------------------------------------*/


void
AttackAction::updateWithData( const QVariant& _data )
{
} // AttackAction::updateWithData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
