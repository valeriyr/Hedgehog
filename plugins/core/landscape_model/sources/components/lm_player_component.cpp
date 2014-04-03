
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_player_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


PlayerComponent::PlayerComponent(
		Object& _object
	,	const IPlayerComponent::StaticData& _staticData
	,	const IPlayer::Id& _playerId
	)
	:	BaseComponent< IPlayerComponent >( _object )
	,	m_staticData( _staticData )
	,	m_playerId( _playerId )
{
} // PlayerComponent::PlayerComponent


/*---------------------------------------------------------------------------*/


PlayerComponent::~PlayerComponent()
{
} // PlayerComponent::~PlayerComponent


/*---------------------------------------------------------------------------*/


const IPlayerComponent::StaticData&
PlayerComponent::getStaticData() const
{
	return m_staticData;

} // PlayerComponent::getStaticData


/*---------------------------------------------------------------------------*/


IPlayer::Id
PlayerComponent::getPlayerId() const
{
	return m_playerId;

} // PlayerComponent::getPlayerId


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
