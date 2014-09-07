
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_multi_player_mode.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/h/lm_resources.hpp"

#include "network_manager/ih/nm_iudp_connection.hpp"
#include "network_manager/h/nm_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

static const TickType gs_tickLatency = 2;
static const TickType gs_syncTickLatency = 1;

/*---------------------------------------------------------------------------*/

struct PlayerData
{
	PlayerData()
		:	m_id( IPlayer::ms_wrondId )
		,	m_type( PlayerType::Blocked )
		,	m_name()
		,	m_race()
		,	m_address()
		,	m_port( 0 )
	{}

	PlayerData(
			const IPlayer::Id _id
		,	const PlayerType::Enum _type
		,	const QString _name
		,	const QString _race
		)
		:	m_id( _id )
		,	m_type( _type )
		,	m_name( _name )
		,	m_race( _race )
		,	m_address()
		,	m_port( 0 )
	{}

	PlayerData(
			const IPlayer::Id _id
		,	const PlayerType::Enum _type
		,	const QString _name
		,	const QString _race
		,	const QString _address
		,	const int _port
		)
		:	m_id( _id )
		,	m_type( _type )
		,	m_name( _name )
		,	m_race( _race )
		,	m_address( _address )
		,	m_port( _port )
	{}

	operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }

	bool hasConnectionInfo() const
	{
		return !m_address.isEmpty() && m_port != 0;
	}

	IPlayer::Id m_id;

	PlayerType::Enum m_type;

	QString m_name;
	QString m_race;

	QString m_address;
	int m_port;
};

Q_DECLARE_METATYPE(PlayerData);

QDataStream& operator << ( QDataStream& _out, const PlayerData& _data )
{
	_out << _data.m_id;
	_out << _data.m_type;
	_out << _data.m_name;
	_out << _data.m_race;
	_out << _data.m_address;
	_out << _data.m_port;

	return _out;
}

QDataStream& operator >> ( QDataStream& _in, PlayerData& _data )
{
	_in >> _data.m_id;

	int type = PlayerType::Blocked;
	_in >> type;
	_data.m_type = static_cast< PlayerType::Enum >( type );

	_in >> _data.m_name;
	_in >> _data.m_race;
	_in >> _data.m_address;
	_in >> _data.m_port;

	return _in;
}

/*---------------------------------------------------------------------------*/


MultiPlayerMode::MultiPlayerMode(
		const IEnvironment& _environment
	,	const Framework::Core::NetworkManager::ConnectionInfo& _myConnectionInfo
	,	const Framework::Core::NetworkManager::ConnectionInfo& _connectTo
	)
	:	m_environment( _environment )
	,	m_myConnectionInfo( _myConnectionInfo )
	,	m_myConnection()
	,	m_connections()
	,	m_commandsQueue()
{
	registerMetatypes();

	m_myConnection = m_environment.getConnection( m_myConnectionInfo, m_environment.getUInt( Resources::Properties::ConnectionTimeOut ) );
	m_myConnection->addConnectionListener( this );

	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Info
		,	QString( Resources::SocketHasBeenOpenedMessage ).arg( m_myConnectionInfo.m_address ).arg( m_myConnectionInfo.m_port ) );

	if ( !_connectTo.isEmpty() && _connectTo != _myConnectionInfo )
	{
		Command connectRequest( CommandId::ConnectRequest );
		connectRequest.pushArgument( m_environment.getString( Resources::Properties::PlayerName ) );

		sendCommand( _connectTo, connectRequest );
	}

} // MultiPlayerMode::MultiPlayerMode


/*---------------------------------------------------------------------------*/


MultiPlayerMode::~MultiPlayerMode()
{
	{
		boost::intrusive_ptr< IModelLocker > locker = m_environment.lockModel();

		if ( locker->getLandscapeModel()->getMyPlayer() )
			spreadCommand( Command( CommandId::Disconnect ).pushArgument( locker->getLandscapeModel()->getMyPlayer()->getUniqueId() ) );
	}

	m_myConnection->removeConnectionListener( this );
	m_environment.closeConnection( m_myConnectionInfo );

	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Info
		,	QString( Resources::SocketHasBeenClosedMessage ).arg( m_myConnectionInfo.m_address ).arg( m_myConnectionInfo.m_port ) );

} // MultiPlayerMode::~MultiPlayerMode


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processCommand( const Command& _command )
{
	if ( !CommandId::simulationTimeCommand( _command.m_id ) )
	{
		m_environment.lockModel()->getLandscapeModel()->processCommand( _command );
		spreadCommand( _command );
	}
	else
	{
		m_commandsQueue.pushCommand( _command.m_pushToProcessingTick + gs_tickLatency, _command );
	}

} // MultiPlayerMode::processCommand


/*---------------------------------------------------------------------------*/


bool
MultiPlayerMode::prepareToTick( const TickType& _tick )
{
	// Check sync latency
	if ( _tick <= gs_syncTickLatency )
		return true;

	// Send data about my player commands
	boost::intrusive_ptr< IModelLocker > locker = m_environment.lockModel();
	boost::intrusive_ptr< ILandscapeModel > model = locker->getLandscapeModel();

	boost::intrusive_ptr< IPlayer > myPlayer = model->getMyPlayer();
	assert( myPlayer );

	CommandsQueue::CommandsCollection myCommands;
	m_commandsQueue.fetchPlayerCommands( myPlayer->getUniqueId(), _tick + gs_syncTickLatency, myCommands );

	spreadCommands( myPlayer->getUniqueId(), _tick + gs_syncTickLatency, myCommands );

	// Check latency
	if ( _tick <= gs_tickLatency )
		return true;

	// On this time we should have all commands from another players
	if ( !m_commandsQueue.hasCommands( _tick ) )
		return false;

	ILandscapeModel::PlayersCollection players;
	model->fetchPlayers( players );

	ILandscapeModel::PlayersCollectionIterator
			playersBegin = players.begin()
		,	playersEnd = players.end();

	for ( ; playersBegin != playersEnd; ++playersBegin )
	{
		if ( !m_commandsQueue.hasCommands( ( *playersBegin )->getUniqueId(), _tick) )
			return false;
	}

	// Collect all commands for tick and execute
	CommandsQueue::CommandsByTimeCollection commandsForExecution;
	m_commandsQueue.fetchCommandsByTime( _tick, commandsForExecution );

	CommandsQueue::CommandsByTimeCollectionIterator
			commandsForExecutionBegin = commandsForExecution.begin()
		,	commandsForExecutionEnd = commandsForExecution.end();

	for ( ; commandsForExecutionBegin != commandsForExecutionEnd; ++commandsForExecutionBegin )
		model->processCommand( commandsForExecutionBegin->second );

	return true;

} // MultiPlayerMode::prepareToTick


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::onDataReceive(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Framework::Core::NetworkManager::Data& _data )
{
	Command command( Command::deserialize( static_cast< CommandId::Enum >( _data.m_id ), _data.m_data ) );

	command.m_sourceConnectionInfo = Framework::Core::NetworkManager::ConnectionInfo( _fromAddress, _fromPort );

	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Info
		,	QString( Resources::CommandReceivedMessage )
				.arg( _fromAddress )
				.arg( _fromPort )
				.arg( CommandId::toString( command.m_id ) )
				.arg( command.m_timeStamp )
				.arg( command.m_pushToProcessingTick ) );

	processCommand( _fromAddress, _fromPort, command );

} // MultiPlayerMode::onDataReceive


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::sendCommand(
		const Framework::Core::NetworkManager::ConnectionInfo& _sendTo
	,	const Command& _command )
{
	QByteArray data;
	_command.serialize( data );

	m_myConnection->sendDataTo( _sendTo, Framework::Core::NetworkManager::Data( _command.m_id, data ) );

} // MultiPlayerMode::sendCommand


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::spreadCommand( const Command& _command )
{
	if ( !CommandId::silentCommand( _command.m_id ) && _command.m_type != CommandType::Silent )
	{
		ConnectionsInfosCollectionIterator
				begin = m_connections.begin()
			,	end = m_connections.end();

		for ( ; begin != end; ++begin )
		{
			if ( begin->second != _command.m_sourceConnectionInfo )
				sendCommand( begin->second, _command );
		}
	}

} // MultiPlayerMode::spreadCommand


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processCommand(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Command& _command )
{
	if ( _command.m_id == CommandId::ConnectRequest )
	{
		processConnectRequest( _fromAddress, _fromPort, _command );
	}
	else if ( _command.m_id == CommandId::ConnectResponse )
	{
		processConnectResponse( _fromAddress, _fromPort, _command );
	}
	else if ( _command.m_id == CommandId::PlayerConnected )
	{
		processPlayerConnected( _fromAddress, _fromPort, _command );
	}
	else if ( _command.m_id == CommandId::Disconnect )
	{
		processDisconnect( _fromAddress, _fromPort, _command );
	}
	else if ( _command.m_id == CommandId::PassCommands )
	{
		processPassCommands( _fromAddress, _fromPort, _command );
	}
	else
	{
		m_environment.lockModel()->getLandscapeModel()->processCommand( _command );
	}

} // MultiPlayerMode::processCommand


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processConnectRequest(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Command& _command )
{
	Command connectResponce( CommandId::ConnectResponse );

	boost::intrusive_ptr< IModelLocker > locker = m_environment.lockModel();
	boost::intrusive_ptr< ILandscapeModel > model = locker->getLandscapeModel();

	boost::intrusive_ptr< IPlayer > freePlayer = model->getFirstFreePlayer();

	if ( freePlayer )
	{
		model->pushCommand( Command( CommandId::ChangePlayerName ).pushArgument( freePlayer->getUniqueId() ).pushArgument( _command.m_arguments[0].toString() ) );
		model->pushCommand( Command( CommandId::ChangePlayerType ).pushArgument( freePlayer->getUniqueId() ).pushArgument( PlayerType::Player ) );

		QList< QVariant > playersList;

		ILandscapeModel::PlayersCollection players;
		model->fetchPlayers( players );

		ILandscapeModel::PlayersCollectionIterator
				begin = players.begin()
			,	end = players.end();

		for ( ; begin != end; ++begin )
		{
			ConnectionsInfosCollectionIterator iterator = m_connections.find( ( *begin )->getUniqueId() );

			if ( iterator != m_connections.end() )
			{
				playersList.push_back(
					PlayerData(
							( *begin )->getUniqueId()
						,	( *begin )->getType()
						,	( *begin )->getName()
						,	( *begin )->getRace()
						,	iterator->second.m_address
						,	iterator->second.m_port ) );
			}
			else if ( ( *begin )->getUniqueId() == model->getMyPlayer()->getUniqueId() )
			{
				playersList.push_back(
					PlayerData(
							( *begin )->getUniqueId()
						,	( *begin )->getType()
						,	( *begin )->getName()
						,	( *begin )->getRace()
						,	m_myConnectionInfo.m_address
						,	m_myConnectionInfo.m_port ) );
			}
			else
			{
				playersList.push_back( PlayerData( ( *begin )->getUniqueId(), ( *begin )->getType(), ( *begin )->getName(), ( *begin )->getRace() ) );
			}
		}

		connectResponce.pushArgument( freePlayer->getUniqueId() );
		connectResponce.pushArgument( model->getFilePath() );
		connectResponce.pushArgument( model->getVictoryConditionType() );
		connectResponce.pushArgument( playersList );

		spreadPlayerConnectedCommand( freePlayer->getUniqueId(), freePlayer->getName(), _fromAddress, _fromPort );

		m_connections.insert( std::make_pair( freePlayer->getUniqueId(), Framework::Core::NetworkManager::ConnectionInfo( _fromAddress, _fromPort ) ) );
	}
	else
	{
		connectResponce.pushArgument( IPlayer::ms_wrondId );
	}

	sendCommand( Framework::Core::NetworkManager::ConnectionInfo( _fromAddress, _fromPort ), connectResponce );

} // MultiPlayerMode::processConnectRequest


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processConnectResponse(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Command& _command )
{
	IPlayer::Id playerId = _command.m_arguments[ 0 ].toInt();

	if ( playerId == IPlayer::ms_wrondId )
		return;

	boost::intrusive_ptr< IModelLocker > locker = m_environment.lockModel();
	boost::intrusive_ptr< ILandscapeModel > model = locker->getLandscapeModel();

	// TODO: should initialize landscape correctly
	QString filePath = _command.m_arguments[ 1 ].toString();

	const VictoryCondition::Enum victoryCondition
		= static_cast< VictoryCondition::Enum >( _command.m_arguments[ 2 ].toInt() );

	model->pushCommand( Command( CommandId::ChangeVictoryCondition, CommandType::Silent ).pushArgument( victoryCondition ) );

	QList< QVariant > playersList = _command.m_arguments[ 3 ].toList();

	QList< QVariant >::ConstIterator
			begin = playersList.begin()
		,	end = playersList.end();

	for ( ; begin != end; ++begin )
	{
		PlayerData data( begin->value< PlayerData >() );

		if ( data.m_id == playerId )
		{
			model->pushCommand( Command( CommandId::ChangeMyPlayer )
				.pushArgument( data.m_id )
				.pushArgument( data.m_name )
				.pushArgument( data.m_race )
				.pushArgument( data.m_type ) );
		}
		else
		{
			model->pushCommand( Command( CommandId::ChangePlayerName, CommandType::Silent ).pushArgument( data.m_id ).pushArgument( data.m_name ) );
			model->pushCommand( Command( CommandId::ChangePlayerRace, CommandType::Silent ).pushArgument( data.m_id ).pushArgument( data.m_race ) );
			model->pushCommand( Command( CommandId::ChangePlayerType, CommandType::Silent ).pushArgument( data.m_id ).pushArgument( data.m_type ) );

			if ( data.hasConnectionInfo() )
				m_connections.insert( std::make_pair( data.m_id, Framework::Core::NetworkManager::ConnectionInfo( data.m_address, data.m_port ) ) );
		}
	}

} // MultiPlayerMode::processConnectResponse


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processPlayerConnected(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Command& _command )
{
	IPlayer::Id playerId = _command.m_arguments[ 0 ].toInt();
	QString name = _command.m_arguments[ 1 ].toString();

	m_environment.lockModel()->getLandscapeModel()
		->pushCommand( Command( CommandId::ChangePlayerName, CommandType::Silent ).pushArgument( playerId ).pushArgument( name ) );

	m_connections.insert(
		std::make_pair(
				playerId
			,	Framework::Core::NetworkManager::ConnectionInfo(
						_command.m_arguments[ 2 ].toString()
					,	_command.m_arguments[ 3 ].toInt() ) ) );

} // MultiPlayerMode::processPlayerConnected


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processDisconnect(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Command& _command )
{
	IPlayer::Id playerId = _command.m_arguments[ 0 ].toInt();

	m_connections.erase( playerId );

	boost::intrusive_ptr< IModelLocker > locker = m_environment.lockModel();
	boost::intrusive_ptr< ILandscapeModel > model = locker->getLandscapeModel();

	model->pushCommand( Command( CommandId::ChangePlayerName, CommandType::Silent ).pushArgument( playerId ).pushArgument( Resources::DefaultPlayerName ) );
	model->pushCommand( Command( CommandId::ChangePlayerType, CommandType::Silent ).pushArgument( playerId ).pushArgument( PlayerType::Open ) );

} // MultiPlayerMode::processDisconnect


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processPassCommands(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Command& _command )
{
	IPlayer::Id playerId = _command.m_arguments[ 0 ].toInt();
	TickType targetTick = _command.m_arguments[ 1 ].toInt();

	if ( m_commandsQueue.hasCommands( playerId, targetTick ) )
		return;

	QMap< QString, QVariant > commands = _command.m_arguments[ 2 ].toMap();

	if ( commands.empty() )
	{
		m_commandsQueue.ensureCommandsList( playerId, targetTick );
	}
	else
	{
		QMap< QString, QVariant >::ConstIterator
				begin = commands.begin()
			,	end = commands.end();

		for ( ; begin != end; ++begin )
			m_commandsQueue.pushCommand( playerId, targetTick, Command::deserialize( static_cast< CommandId::Enum >( begin.key().toInt() ), begin.value().toByteArray() ) );
	}

} // MultiPlayerMode::processPassCommands


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::spreadPlayerConnectedCommand(
		const IPlayer::Id& _playerId
	,	const QString& _playerName
	,	const QString& _playerAddress
	,	const unsigned int _playerPort )
{
	Command command( CommandId::PlayerConnected );

	command.pushArgument( _playerId );
	command.pushArgument( _playerName );
	command.pushArgument( _playerAddress );
	command.pushArgument( _playerPort );

	spreadCommand( command );

} // MultiPlayerMode::spreadPlayerConnectedCommand


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::spreadCommands(
		const IPlayer::Id& _playerId
	,	const TickType& _targetTick
	,	const CommandsQueue::CommandsCollection& _commands )
{
	Command command( CommandId::PassCommands );

	QMap< QString, QVariant > commands;

	CommandsQueue::CommandsCollectionIterator
			begin = _commands.begin()
		,	end = _commands.end();

	for ( ; begin != end; ++begin )
	{
		QByteArray commandData;
		begin->serialize( commandData );

		assert( _playerId == begin->m_playerId );

		commands.insert( QString::number( begin->m_id ), commandData );
	}

	command.pushArgument( _playerId );
	command.pushArgument( _targetTick );
	command.pushArgument( commands );

	spreadCommand( command );

} // MultiPlayerMode::spreadCommands


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::registerMetatypes()
{
	qRegisterMetaTypeStreamOperators< PlayerData >( "PlayerData" );

} // MultiPlayerMode::registerMetatypes


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
