
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/player/lm_player.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

static IPlayer::Id IdGenerator = 0;

/*---------------------------------------------------------------------------*/


Player::Player( const IStaticData& _staticData )
	:	m_staticData( _staticData )
	,	m_id( ++IdGenerator )
{
} // Player::Player


/*---------------------------------------------------------------------------*/


Player::~Player()
{
} // Player::~Player


/*---------------------------------------------------------------------------*/


IPlayer::Id
Player::getUniqueId() const
{
	return m_id;

} // Player::getUniqueId


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
