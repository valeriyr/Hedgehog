
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/replay_serializer/lm_replay_serializer.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_commands_queue.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"
#include "landscape_model/sources/player/lm_player.hpp"

#include "xml_library/sources/rules/xl_tag_rule.hpp"
#include "xml_library/sources/rules/xl_attribute_rule.hpp"
#include "xml_library/sources/visitors/xl_xml_parser.hpp"

#include "streaming/st_qvariant_extensions.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


ReplaySerializer::ReplaySerializer( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // ReplaySerializer::ReplaySerializer


/*---------------------------------------------------------------------------*/


ReplaySerializer::~ReplaySerializer()
{
} // ReplaySerializer::~ReplaySerializer


/*---------------------------------------------------------------------------*/


void
ReplaySerializer::load(
		const QString& _filePath
	,	QString& _landscapeName
	,	VictoryCondition::Enum& _victoryCondition
	,	ILandscapeModel::PlayersCollection& _players
	,	CommandsQueue& _commands )
{
	QFile file( _filePath );
	if ( !file.open( QIODevice::ReadOnly ) )
		throw std::exception();

	Tools::Core::XmlLibrary::Tag rule
		=
		Tools::Core::XmlLibrary::Tag( Resources::Xml::HReplay )
		[
				Tools::Core::XmlLibrary::Tag( Resources::Xml::Landscape )
				[
					Tools::Core::XmlLibrary::Attribute( Resources::Xml::Name, Tools::Core::XmlLibrary::AttributeType::String )
				]
				.handle(	boost::bind( &ReplaySerializer::onLandscapeElement, this, boost::ref( _landscapeName ), _1 )
						,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::Xml::Name ) )
			||
				Tools::Core::XmlLibrary::Tag( Resources::Xml::VictoryCondition )
				[
					Tools::Core::XmlLibrary::Attribute( Resources::Xml::Name, Tools::Core::XmlLibrary::AttributeType::String )
				]
				.handle(	boost::bind( &ReplaySerializer::onVictoryConditionElement, this, boost::ref( _victoryCondition ), _1 )
						,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::Xml::Name ) )
			||
				Tools::Core::XmlLibrary::Tag( Resources::Xml::Players )
				[
						+Tools::Core::XmlLibrary::Tag( Resources::Xml::Player )
						[
								Tools::Core::XmlLibrary::Attribute( Resources::Xml::Id, Tools::Core::XmlLibrary::AttributeType::Integer )
							&&
								Tools::Core::XmlLibrary::Attribute( Resources::Xml::StartPoint, Tools::Core::XmlLibrary::AttributeType::Integer )
							&&
								Tools::Core::XmlLibrary::Attribute( Resources::Xml::Type, Tools::Core::XmlLibrary::AttributeType::Integer )
							&&
								Tools::Core::XmlLibrary::Attribute( Resources::Xml::Race, Tools::Core::XmlLibrary::AttributeType::String )
							&&
								Tools::Core::XmlLibrary::Attribute( Resources::Xml::Name, Tools::Core::XmlLibrary::AttributeType::String )
						]
						.handle(
									boost::bind( &ReplaySerializer::onPlayerElement, this, boost::ref( _players ), _1, _2, _3, _4, _5 )
								,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::Id )
								,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::StartPoint )
								,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::Type )
								,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::Xml::Race )
								,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::Xml::Name )
								)
				]
			||
				Tools::Core::XmlLibrary::Tag( Resources::Xml::Commands )
				[
					*Tools::Core::XmlLibrary::Tag( Resources::Xml::Command )
					[
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::Id, Tools::Core::XmlLibrary::AttributeType::Integer )
						&&
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::StartPoint, Tools::Core::XmlLibrary::AttributeType::Integer )
						&&
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::Type, Tools::Core::XmlLibrary::AttributeType::Integer )
						&&
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::Race, Tools::Core::XmlLibrary::AttributeType::String )
						&&
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::Name, Tools::Core::XmlLibrary::AttributeType::String )
					]
					[
						*Tools::Core::XmlLibrary::Tag( Resources::Xml::Argument )
						[
							Tools::Core::XmlLibrary::Attribute( Resources::Xml::Value, Tools::Core::XmlLibrary::AttributeType::String )
						]
					]
					.handle(
								boost::bind( &ReplaySerializer::onCommandElement, this, boost::ref( _commands ), _1, _2, _3, _4, _5 )
							,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::Tick )
							,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::Xml::Name )
							,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::Player )
							,	Tools::Core::XmlLibrary::IntAttributeExtructor( Resources::Xml::TimeStamp )
							,	Tools::Core::XmlLibrary::ChildTagsStringAttributeExtructor( Resources::Xml::Argument, Resources::Xml::Value )
							)
				]
		]
		.handle(	boost::bind( &ReplaySerializer::onHReplayElement, this, _1 )
				,	Tools::Core::XmlLibrary::StringAttributeExtructor( Resources::Xml::Version ) );

	Tools::Core::XmlLibrary::Parser::parse( *rule.getElement(), file );

} // ReplaySerializer::load


/*---------------------------------------------------------------------------*/


void
ReplaySerializer::save(
		const QString& _filePath
	,	const QString& _landscapeName
	,	const VictoryCondition::Enum _victoryCondition
	,	const ILandscapeModel::PlayersCollection& _players
	,	const CommandsQueue& _commands ) const
{
	QFileInfo fileInfo( _filePath );
	if ( !fileInfo.absoluteDir().mkpath(".") )
		throw std::exception();

	QFile file( _filePath );

	if ( !file.open( QIODevice::WriteOnly ) )
		throw std::exception();

	QXmlStreamWriter xmlStream( &file );
	xmlStream. setAutoFormatting( true );

	xmlStream.writeStartDocument();

    xmlStream.writeDTD( Resources::Xml::ReplayDocTypeString );

    xmlStream.writeStartElement( Resources::Xml::HReplay );

	xmlStream.writeAttribute( Resources::Xml::Version, Resources::ReplayVersion );

	xmlStream.writeStartElement( Resources::Xml::Landscape );
	xmlStream.writeAttribute( Resources::Xml::Name, _landscapeName );
	xmlStream.writeEndElement();

	xmlStream.writeStartElement( Resources::Xml::VictoryCondition );
	xmlStream.writeAttribute( Resources::Xml::Name, VictoryCondition::toString( _victoryCondition ) );
	xmlStream.writeEndElement();

	xmlStream.writeStartElement( Resources::Xml::Players );

	ILandscapeModel::PlayersCollectionIterator
			beginPlayers = _players.begin()
		,	endPlayers = _players.end();

	for ( ; beginPlayers != endPlayers; ++beginPlayers )
	{
		xmlStream.writeStartElement( Resources::Xml::Player );

		xmlStream.writeAttribute( Resources::Xml::Id, QString::number( ( *beginPlayers )->getUniqueId() ) );
		xmlStream.writeAttribute( Resources::Xml::StartPoint, QString::number( ( *beginPlayers )->getStartPointId() ) );
		xmlStream.writeAttribute( Resources::Xml::Type, QString::number( ( *beginPlayers )->getType() ) );
		xmlStream.writeAttribute( Resources::Xml::Race, ( *beginPlayers )->getRace() );
		xmlStream.writeAttribute( Resources::Xml::Name, ( *beginPlayers )->getName() );

		xmlStream.writeEndElement();
	}

	xmlStream.writeEndElement();

	xmlStream.writeStartElement( Resources::Xml::Commands );

	CommandsQueue::CommandsByTickCollection commands;
	_commands.fetchCommands( commands );

	CommandsQueue::CommandsByTickCollectionConstIterator
			beginTicks = commands.begin()
		,	endTicks = commands.end();

	for ( ; beginTicks != endTicks; ++beginTicks )
	{
		bool hasCommands = false;

		CommandsQueue::CommandsByPlayerCollectionConstIterator
				beginCommandsByPlayer = beginTicks->second.begin()
			,	endCommandsByPlayer = beginTicks->second.end();

		for ( ; beginCommandsByPlayer != endCommandsByPlayer; ++beginCommandsByPlayer )
		{
			if ( !beginCommandsByPlayer->second.empty() )
			{
				hasCommands = true;
				break;
			}
		}

		if ( !hasCommands )
			continue;

		beginCommandsByPlayer = beginTicks->second.begin();
		endCommandsByPlayer = beginTicks->second.end();

		for ( ; beginCommandsByPlayer != endCommandsByPlayer; ++beginCommandsByPlayer )
		{
			CommandsQueue::CommandsCollectionConstIterator
					beginCommands = beginCommandsByPlayer->second.begin()
				,	endCommands = beginCommandsByPlayer->second.end();

			for ( ; beginCommands != endCommands; ++beginCommands )
			{
				xmlStream.writeStartElement( Resources::Xml::Command );

				xmlStream.writeAttribute( Resources::Xml::Name, CommandId::toString( beginCommands->m_id ) );
				xmlStream.writeAttribute( Resources::Xml::Player, QString::number( beginCommands->m_playerId ) );
				xmlStream.writeAttribute( Resources::Xml::Tick, QString::number( beginCommands->m_targetTick ) );
				xmlStream.writeAttribute( Resources::Xml::TimeStamp, QString::number( beginCommands->m_timeStamp ) );

				Command::CommandArgumentsCollectionIterator
						beginArguments = beginCommands->m_arguments.begin()
					,	endArguments = beginCommands->m_arguments.end();

				for ( ; beginArguments != endArguments; ++beginArguments )
				{
					xmlStream.writeStartElement( Resources::Xml::Argument );

					xmlStream.writeAttribute( Resources::Xml::Value, Tools::Core::Streaming::toString( *beginArguments ) );

					xmlStream.writeEndElement();
				}

				xmlStream.writeEndElement();
			}
		}
	}

	xmlStream.writeEndElement();
	xmlStream.writeEndElement();

	xmlStream.writeEndDocument();

} // ReplaySerializer::save


/*---------------------------------------------------------------------------*/


void
ReplaySerializer::onHReplayElement( const QString& _version )
{
	if ( _version != Resources::ReplayVersion )
		throw std::exception();

} // ReplaySerializer::onHReplayElement


/*---------------------------------------------------------------------------*/


void
ReplaySerializer::onLandscapeElement( QString& _landscapeName, const QString& _name ) const
{
	_landscapeName = _name;

} // ReplaySerializer::onLandscapeElement


/*---------------------------------------------------------------------------*/


void
ReplaySerializer::onVictoryConditionElement(
		VictoryCondition::Enum& _victoryCondition
	,	const QString& _condition ) const
{
	_victoryCondition = VictoryCondition::fromString( _condition );

} // ReplaySerializer::onVictoryConditionElement


/*---------------------------------------------------------------------------*/


void
ReplaySerializer::onPlayerElement(
		ILandscapeModel::PlayersCollection& _players
	,	const Tools::Core::Generators::IGenerator::IdType& _id
	,	const StartPoint::Id& _startPointId
	,	const int _type
	,	const QString& _race
	,	const QString& _name ) const
{
	_players.push_back(
		boost::intrusive_ptr< IPlayer >(
			new Player(
					m_environment
				,	_id
				,	_startPointId
				,	static_cast< PlayerType::Enum >( _type )
				,	_race
				,	_name ) ) );

} // ReplaySerializer::onPlayerElement


/*---------------------------------------------------------------------------*/


void
ReplaySerializer::onCommandElement(
		CommandsQueue& _commands
	,	const TickType& _targetTick
	,	const QString& _commandName
	,	const Tools::Core::Generators::IGenerator::IdType& _playerId
	,	const Tools::Core::Time::Milliseconds _timestamp
	,	const Tools::Core::XmlLibrary::ChildTagsStringAttributeExtructor::ResultCollection& _arguments ) const

{
	Command command( CommandId::fromString( _commandName ) );

	command.m_playerId = _playerId;
	command.m_timeStamp = _timestamp;
	command.m_targetTick = _targetTick;

	Tools::Core::XmlLibrary::ChildTagsStringAttributeExtructor::ResultCollectionIterator
			begin = _arguments.begin()
		,	end = _arguments.end();

	for ( ; begin != end; ++begin )
		command.m_arguments.push_back( Tools::Core::Streaming::fromString( *begin ) );

	_commands.pushCommand( _playerId, _targetTick, command );

} // ReplaySerializer::onCommandElement


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
