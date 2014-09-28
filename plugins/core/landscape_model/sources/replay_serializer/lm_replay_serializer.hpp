
#ifndef __LM_REPLAY_SERIALIZER_HPP__
#define __LM_REPLAY_SERIALIZER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/replay_serializer/lm_ireplay_serializer.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class ReplaySerializer
	:	public Tools::Core::BaseWrapper< IReplaySerializer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ReplaySerializer( const IEnvironment& _environment );

	virtual ~ReplaySerializer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void load(
			const QString& _filePath
		,	QString& _landscapeName
		,	VictoryCondition::Enum& _victoryCondition
		,	ILandscapeModel::PlayersCollection& _players
		,	CommandsQueue& _commands );

	/*virtual*/ void save(
			const QString& _filePath
		,	const QString& _landscapeName
		,	const VictoryCondition::Enum _victoryCondition
		,	const ILandscapeModel::PlayersCollection& _players
		,	const CommandsQueue& _commands ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onHReplayElement( const QString& _version );

	void onLandscapeElement( QString& _landscapeName, const QString& _name ) const;

	void onVictoryConditionElement( VictoryCondition::Enum& _victoryCondition, const QString& _condition ) const;

	void onPlayerElement(
			ILandscapeModel::PlayersCollection& _players
		,	const Tools::Core::Generators::IGenerator::IdType& _id
		,	const Tools::Core::Generators::IGenerator::IdType& _startPointId
		,	const int _type
		,	const QString& _race
		,	const QString& _name ) const;

	void onCommandElement(
			CommandsQueue& _commands
		,	const TickType& _targetTick
		,	const QString& _commandName
		,	const Tools::Core::Generators::IGenerator::IdType& _playerId
		,	const Tools::Core::Time::Milliseconds _timestamp
		,	const Tools::Core::XmlLibrary::ChildTagsStringAttributeExtructor::ResultCollection& _arguments ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_LANDSCAPE_SERIALIZER_HPP__
