
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
		,	const Tools::Core::Generators::IGenerator::IdType _id
		,	const QString& _race
		,	const Tools::Core::Generators::IGenerator::IdType& _startPointId );

	Player(
			const IEnvironment& _environment
		,	const Tools::Core::Generators::IGenerator::IdType _id
		,	const Tools::Core::Generators::IGenerator::IdType& _startPointId
		,	const PlayerType::Enum _type
		,	const QString& _race
		,	const QString& _name );

	virtual ~Player();

/*---------------------------------------------------------------------------*/

	/*virtual*/ Tools::Core::Generators::IGenerator::IdType getUniqueId() const;

	/*virtual*/ PlayerType::Enum getType() const;

	/*virtual*/ const QString& getRace() const;

	/*virtual*/ const Tools::Core::Generators::IGenerator::IdType& getStartPointId() const;

	/*virtual*/ const QString& getName() const;

	/*virtual*/ const QString& getAIName() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const ResourcesData& getResourcesData() const;

	/*virtual*/ void substructResources( const ResourcesData& _data );

	/*virtual*/ void addResources( const ResourcesData& _data );

	/*virtual*/ void addResources( const QString& _resourceName, const int _value );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushGoal( const Priority::Enum _priority, const IGoal::Ptr _goal );

/*---------------------------------------------------------------------------*/

	void setName( const QString& _name );

	void setRace( const QString& _race );

	void setType( const PlayerType::Enum _type );

/*---------------------------------------------------------------------------*/

	void processGoals();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void riseResourcesChanedEvent();

	void setupResources();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< Priority::Enum, IGoal::Ptr >
		GoalsCollection;
	typedef
		GoalsCollection::const_iterator
		GoalsCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const Tools::Core::Generators::IGenerator::IdType m_id;

	const Tools::Core::Generators::IGenerator::IdType m_startPointId;

	QString m_race;

	QString m_name;

	QString m_aiName;

	PlayerType::Enum m_type;

	ResourcesData m_resourceData;

	Notifier< Player > m_notifier;

	GoalsCollection m_goals;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PLAYER_HPP__
