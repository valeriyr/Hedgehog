
#ifndef __LM_PLAYER_HPP__
#define __LM_PLAYER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_iplayer.hpp"

#include "landscape_model/sources/notification_center/lm_notifier.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IStaticData;
struct IEnvironment;

/*---------------------------------------------------------------------------*/

class Player
	:	public Tools::Core::BaseWrapper< IPlayer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Player( const IEnvironment& _environment, const IStaticData& _staticData );

	virtual ~Player();

/*---------------------------------------------------------------------------*/

	/*virtual*/ IPlayer::Id getUniqueId() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ ResourcesData& getResourcesData();

	/*virtual*/ void substructResources( const ResourcesData& _data );

	/*virtual*/ void addResources( const ResourcesData& _data );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void riseResourcesChanedEvent();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const IStaticData& m_staticData;

	const IPlayer::Id m_id;

	ResourcesData m_resourceData;

	Notifier< Player > m_notifier;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLAYER_HPP__
