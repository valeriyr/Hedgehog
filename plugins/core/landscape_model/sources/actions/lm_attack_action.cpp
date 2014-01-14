
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
	return true;

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
