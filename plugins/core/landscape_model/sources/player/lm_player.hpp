
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

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class Player
	:	public Tools::Core::BaseWrapper< IPlayer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Player(
			const IEnvironment& _environment
		,	const QString& _race
		,	const StartPoint::Id& _startPointId );

	Player(
			const IEnvironment& _environment
		,	const IPlayer::Id _id
		,	const StartPoint::Id& _startPointId
		,	const PlayerType::Enum _type
		,	const QString& _race
		,	const QString& _name );

	virtual ~Player();

/*---------------------------------------------------------------------------*/

	/*virtual*/ IPlayer::Id getUniqueId() const;

	/*virtual*/ PlayerType::Enum getType() const;

	/*virtual*/ const QString& getRace() const;

	/*virtual*/ const StartPoint::Id& getStartPointId() const;

	/*virtual*/ const QString& getName() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const ResourcesData& getResourcesData() const;

	/*virtual*/ void substructResources( const ResourcesData& _data );

	/*virtual*/ void addResources( const ResourcesData& _data );

	/*virtual*/ void addResources( const QString& _resourceName, const int _value );

/*---------------------------------------------------------------------------*/

	void setName( const QString& _name );

	void setRace( const QString& _race );

	void setType( const PlayerType::Enum _type );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void riseResourcesChanedEvent();

	void setupResources();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const IPlayer::Id m_id;

	const StartPoint::Id m_startPointId;

	QString m_race;

	QString m_name;

	PlayerType::Enum m_type;

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
