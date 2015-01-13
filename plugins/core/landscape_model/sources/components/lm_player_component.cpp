
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/components/lm_player_component.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


PlayerComponent::PlayerComponent(
		GameObject& _object
	,	const IPlayerComponent::StaticData& _staticData
	,	const Tools::Core::Generators::IGenerator::IdType& _playerId
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


Tools::Core::Generators::IGenerator::IdType
PlayerComponent::getPlayerId() const
{
	return m_playerId;

} // PlayerComponent::getPlayerId


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
