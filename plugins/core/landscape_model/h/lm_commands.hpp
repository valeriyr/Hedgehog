
#ifndef __LM_COMMANDS_HPP__
#define __LM_COMMANDS_HPP__

/*---------------------------------------------------------------------------*/

#include "time/t_time.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"
#include "landscape_model/h/lm_constants.hpp"

#include "network_manager/h/nm_connection_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct CommandId
{
	enum Enum
	{
			Undefined	= 0

		,	ConnectRequest
		,	ConnectResponse
		,	PlayerConnected
		,	Disconnect
		,	ChangeVictoryCondition
		,	StartSimulation
		,	StopSimulation
		,	PassCommands
		,	CommandsRequest

		,	ChangePlayerRace
		,	ChangePlayerType
		,	ChangePlayerName
		,	ChangeMyPlayer

		,	SetSurfaceItem
		,	SelectById
		,	SelectByRect
		,	SendToPoint
		,	SendToObject
		,	CreateObject
		,	TrainObject
		,	BuildObject

		,	Size
		,	Begin = ConnectRequest
	};

	static QString toString( const Enum _enum )
	{
		switch( _enum )
		{
		case ConnectRequest:
			return "ConnectRequest";
		case ConnectResponse:
			return "ConnectResponse";
		case PlayerConnected:
			return "PlayerConnected";
		case Disconnect:
			return "Disconnect";
		case ChangeVictoryCondition:
			return "ChangeVictoryCondition";
		case StartSimulation:
			return "StartSimulation";
		case StopSimulation:
			return "StopSimulation";
		case PassCommands:
			return "PassCommands";
		case CommandsRequest:
			return "CommandsRequest";
		case ChangePlayerRace:
			return "ChangePlayerRace";
		case ChangePlayerType:
			return "ChangePlayerType";
		case ChangePlayerName:
			return "ChangePlayerName";
		case ChangeMyPlayer:
			return "ChangeMyPlayer";
		case SetSurfaceItem:
			return "SetSurfaceItem";
		case SelectById:
			return "SelectById";
		case SelectByRect:
			return "SelectByRect";
		case SendToPoint:
			return "SendToPoint";
		case SendToObject:
			return "SendToObject";
		case CreateObject:
			return "CreateObject";
		case TrainObject:
			return "TrainObject";
		case BuildObject:
			return "BuildObject";
		default:
			return "Undefined";
		}
	}

	static Enum fromString( const QString& _type )
	{
		if ( _type == "ConnectRequest" )
			return ConnectRequest;
		else if ( _type == "ConnectResponse" )
			return ConnectResponse;
		else if ( _type == "PlayerConnected" )
			return PlayerConnected;
		else if ( _type == "Disconnect" )
			return Disconnect;
		else if ( _type == "ChangeVictoryCondition" )
			return ChangeVictoryCondition;
		else if ( _type == "StartSimulation" )
			return StartSimulation;
		else if ( _type == "StopSimulation" )
			return StopSimulation;
		else if ( _type == "PassCommands" )
			return PassCommands;
		else if ( _type == "CommandsRequest" )
			return CommandsRequest;
		else if ( _type == "ChangePlayerRace" )
			return ChangePlayerRace;
		else if ( _type == "ChangePlayerType" )
			return ChangePlayerType;
		else if ( _type == "ChangePlayerName" )
			return ChangePlayerName;
		else if ( _type == "ChangeMyPlayer" )
			return ChangeMyPlayer;
		else if ( _type == "SetSurfaceItem" )
			return SetSurfaceItem;
		else if ( _type == "SelectById" )
			return SelectById;
		else if ( _type == "SelectByRect" )
			return SelectByRect;
		else if ( _type == "SendToPoint" )
			return SendToPoint;
		else if ( _type == "SendToObject" )
			return SendToObject;
		else if ( _type == "CreateObject" )
			return CreateObject;
		else if ( _type == "TrainObject" )
			return TrainObject;
		else if ( _type == "BuildObject" )
			return BuildObject;
		else
			return Undefined;
	}

	static bool simulationTimeCommand( const Enum _enum )
	{
		switch( _enum )
		{
		case SetSurfaceItem:
		case SendToPoint:
		case SendToObject:
		case TrainObject:
		case BuildObject:
			return true;
		}

		return false;
	}

	static bool silentCommand( const Enum _enum )
	{
		switch( _enum )
		{
		case ConnectRequest:
		case ConnectResponse:
		case CommandsRequest:
		case ChangeMyPlayer:
		case SelectById:
		case SelectByRect:
		case CreateObject:
			return true;
		}

		return false;
	}
};

/*---------------------------------------------------------------------------*/

struct Command
{

/*---------------------------------------------------------------------------*/

	typedef
		QList< QVariant >
		CommandArgumentsCollection;
	typedef
		CommandArgumentsCollection::const_iterator
		CommandArgumentsCollectionIterator;

/*---------------------------------------------------------------------------*/

	Command( const CommandId::Enum& _id )
		:	m_id( _id )
		,	m_arguments()
		,	m_timeStamp( 0 )
		,	m_targetTick( 0 )
		,	m_playerId( IPlayer::ms_wrondId )
		,	m_sourceConnectionInfo()
	{}

	template< typename _TArgument >
	Command& pushArgument( const _TArgument& _argument )
	{
		m_arguments.push_back( QVariant( _argument ) );
		return *this;
	}

/*---------------------------------------------------------------------------*/

	void serialize( QByteArray& _data ) const
	{
		QDataStream stream( &_data, QIODevice::WriteOnly );
		stream << m_arguments;
		stream << m_timeStamp;
		stream << m_targetTick;
		stream << m_playerId;
	}

	static Command deserialize( const CommandId::Enum& _id, const QByteArray& _data )
	{
		QDataStream stream( _data );

		Command command( _id );
		stream >> command.m_arguments;
		stream >> command.m_timeStamp;
		stream >> command.m_targetTick;
		stream >> command.m_playerId;

		return command;
	}

/*---------------------------------------------------------------------------*/

	CommandId::Enum m_id;

	CommandArgumentsCollection m_arguments;

	Tools::Core::Time::Milliseconds m_timeStamp;

	TickType m_targetTick;

	IPlayer::Id m_playerId;

	Framework::Core::NetworkManager::ConnectionInfo m_sourceConnectionInfo;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

#define COMMAND_MAP_DECLARE_INTERFACE														\
																							\
virtual void processCommand( const Command& _command ) = 0;									\

/*---------------------------------------------------------------------------*/

#define DECLARE_PROCESSOR( COMMAND )														\
																							\
	void on##COMMAND##Processor( const Command& _command );									\

/*---------------------------------------------------------------------------*/

#define COMMAND_MAP_DECLARE																	\
																							\
void processCommand( const Command& _command );												\

/*---------------------------------------------------------------------------*/

#define COMMAND_MAP_BEGIN( HOLDER_CLASS )													\
																							\
void HOLDER_CLASS::processCommand( const Command& _command )								\
{																							\
	switch( _command.m_id )																	\
	{																						\

/*---------------------------------------------------------------------------*/

#define COMMAND_MAP_END()																	\
																							\
	default:																				\
		break;																				\
	}																						\
}																							\

/*---------------------------------------------------------------------------*/

#define PROCESSOR( COMMAND )																\
																							\
	case CommandId::COMMAND:																\
		on##COMMAND##Processor( _command );													\
		break;																				\

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COMMANDS_HPP__
