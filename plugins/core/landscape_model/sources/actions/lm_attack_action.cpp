
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_attack_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"


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
	)
	:	BaseAction( _environment, _object )
	,	m_player( _player )
	,	m_landscape( _landscape )
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
	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );

	if ( m_object.getState() !=  ObjectState::Attacking )
	{
		boost::intrusive_ptr< ILocateComponent > locateComponent
			= m_object.getComponent< ILocateComponent >( ComponentId::Locate );

		m_object.setState( ObjectState::Attacking );

		Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

		m_environment.riseEvent( objectStateChangedEvent );
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
	return false;

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
