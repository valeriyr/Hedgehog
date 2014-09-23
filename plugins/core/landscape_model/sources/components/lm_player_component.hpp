
#ifndef __LM_PLAYER_COMPONENT_HPP__
#define __LM_PLAYER_COMPONENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/components/lm_iplayer_component.hpp"

#include "landscape_model/sources/components/lm_base_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class PlayerComponent
	:	public BaseComponent< IPlayerComponent >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PlayerComponent(
			Object& _object
		,	const IPlayerComponent::StaticData& _staticData
		,	const Tools::Core::Generators::IGenerator::IdType& _playerId );

	virtual ~PlayerComponent();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const IPlayerComponent::StaticData& getStaticData() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ Tools::Core::Generators::IGenerator::IdType getPlayerId() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IPlayerComponent::StaticData& m_staticData;

	Tools::Core::Generators::IGenerator::IdType m_playerId;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLAYER_COMPONENT_HPP__
