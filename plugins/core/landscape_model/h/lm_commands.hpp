
#ifndef __LM_COMMANDS_HPP__
#define __LM_COMMANDS_HPP__

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

		,	Connect
		,	PlayerData
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
		,	Begin = Connect
	};

	static bool doesNeedToSyncOnSimulation( const Enum _enum )
	{
		switch( _enum )
		{
		case Send:
		case TrainObject:
		case BuildObject:
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
		QDataStream stream( _data );
		stream << m_arguments;
	}

	static Command deserialize( const CommandId::Enum& _id, QByteArray& _data )
	{
		QDataStream stream( _data );

		Command command( _id );
		stream >> command.m_arguments;

		return command;
	}

/*---------------------------------------------------------------------------*/

	const CommandId::Enum m_id;

	CommandArgumentsCollection m_arguments;

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
