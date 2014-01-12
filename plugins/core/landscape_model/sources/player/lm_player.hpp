
#ifndef __LM_PLAYER_HPP__
#define __LM_PLAYER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iplayer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IStaticData;

/*---------------------------------------------------------------------------*/

class Player
	:	public Tools::Core::BaseWrapper< IPlayer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Player( const IStaticData& _staticData );

	virtual ~Player();

/*---------------------------------------------------------------------------*/

	/*virtual*/ IPlayer::Id getUniqueId() const;

	/*virtual*/ IPlayer::ResourcesData& getResourcesData();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IStaticData& m_staticData;

	const IPlayer::Id m_id;

	IPlayer::ResourcesData m_resourceData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLAYER_HPP__
