
#ifndef __LM_COMMANDS_HPP__
#define __LM_COMMANDS_HPP__

/*---------------------------------------------------------------------------*/

#include "time/t_time.hpp"

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

		,	ChangePlayerRace
		,	ChangePlayerType
		,	ChangePlayerName
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
		,	m_targetTick( 0 )
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
	}

	static Command deserialize( const CommandId::Enum& _id, const QByteArray& _data )
	{
		QDataStream stream( _data );

		Command command( _id );
		stream >> command.m_arguments;
		stream >> command.m_timeStamp;
		stream >> command.m_targetTick;

		return command;
	}

/*---------------------------------------------------------------------------*/

	const CommandId::Enum m_id;

	const CommandType::Enum m_type;

	CommandArgumentsCollection m_arguments;

	Tools::Core::Time::Milliseconds m_timeStamp;

	TickType m_targetTick;

	Framework::Core::NetworkManager::ConnectionInfo m_sourceConnectionInfo;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

#define COMMAND_MAP_DECLARE_INTERFACE														\
																							\
virtual void processCommand( const Command& _command ) = 0;									\

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
