
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

		,	ChangePlayerRace
		,	ChangePlayerType
		,	ChangePlayerName
		,	ChangeMyPlayer

		,	SetSurfaceItem
		,	SelectById
		,	SelectByRect
		,	Send
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
		case Send:
			return "Send";
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

	static bool simulationTimeCommand( const Enum _enum )
	{
		switch( _enum )
		{
		case SetSurfaceItem:
		case SelectById:
		case SelectByRect:
		case Send:
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

struct CommandType
{
	enum Enum
	{
			Simple	= 0
		,	Silent
	};
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

	Command( const CommandId::Enum& _id, const CommandType::Enum _type = CommandType::Simple )
		:	m_id( _id )
		,	m_type( _type )
		,	m_arguments()
		,	m_timeStamp( 0 )
		,	m_pushToProcessingTick( 0 )
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
		stream << m_pushToProcessingTick;
		stream << m_playerId;
	}

	static Command deserialize( const CommandId::Enum& _id, const QByteArray& _data )
	{
		QDataStream stream( _data );

		Command command( _id );
		stream >> command.m_arguments;
		stream >> command.m_timeStamp;
		stream >> command.m_pushToProcessingTick;
		stream >> command.m_playerId;

		return command;
	}

/*---------------------------------------------------------------------------*/

	CommandId::Enum m_id;

	CommandType::Enum m_type;

	CommandArgumentsCollection m_arguments;

	Tools::Core::Time::Milliseconds m_timeStamp;

	TickType m_pushToProcessingTick;

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
