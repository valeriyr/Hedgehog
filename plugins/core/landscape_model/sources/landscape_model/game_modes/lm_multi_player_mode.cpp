
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_multi_player_mode.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/h/lm_resources.hpp"
#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/sources/internal_resources/lm_internal_resources.hpp"

#include "network_manager/ih/nm_iudp_connection.hpp"
#include "network_manager/h/nm_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct PlayerData
{
	PlayerData()
		:	m_id( IPlayer::ms_wrondId )
		,	m_type( PlayerType::Blocked )
		,	m_name()
		,	m_race()
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
	{}

	operator QVariant() const
    {
        return QVariant::fromValue(*this);
    }

	IPlayer::Id m_id;

	PlayerType::Enum m_type;

	QString m_name;
	QString m_race;
};

Q_DECLARE_METATYPE(PlayerData);

QDataStream& operator << ( QDataStream& _out, const PlayerData& _data )
{
	_out << _data.m_id;
	_out << _data.m_type;
	_out << _data.m_name;
	_out << _data.m_race;
	//_out.writeRawData( reinterpret_cast< const char* >( &_data ), sizeof( _data ) );
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
	//_in.readRawData( reinterpret_cast< char* >( &_data ), sizeof( _data ) );
	return _in;
}

/*---------------------------------------------------------------------------*/


MultiPlayerMode::MultiPlayerMode(
		ILandscapeModel& _landscapeModel
	,	const IEnvironment& _environment
	,	const Framework::Core::NetworkManager::ConnectionInfo& _myConnectionInfo
	,	const Framework::Core::NetworkManager::ConnectionInfo& _connectTo
	)
	:	m_landscapeModel( _landscapeModel )
	,	m_environment( _environment )
	,	m_myConnectionInfo( _myConnectionInfo )
	,	m_myConnection()
	,	m_connections()
{
	registerMetatypes();

	m_myConnection = m_environment.getConnection( m_myConnectionInfo, m_environment.getUInt( Resources::Properties::ConnectionTimeOut ) );
	m_myConnection->addConnectionListener( this );

	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Info
		,	QString( Resources::SocketHasBeenOpenedMessage ).arg( m_myConnectionInfo.m_address ).arg( m_myConnectionInfo.m_port ) );

	if ( !_connectTo.isEmpty() )
	{
		Command connectRequest( CommandId::ConnectRequest, CommandType::Silent );
		connectRequest.pushArgument( m_environment.getString( Resources::Properties::PlayerName ) );

		sendCommand( _connectTo, connectRequest );
	}

} // MultiPlayerMode::MultiPlayerMode


/*---------------------------------------------------------------------------*/


MultiPlayerMode::~MultiPlayerMode()
{
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
	// TODO: algorithm shoul be more smarter

	m_landscapeModel.processCommand( _command );

	spreadCommand( _command );

} // MultiPlayerMode::processCommand


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
				.arg( command.m_id )
				.arg( command.m_timeStamp )
				.arg( command.m_targetTick ) );

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
	if ( _command.m_type != CommandType::Silent )
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
	else
	{
		processCommand( _command );
	}

} // MultiPlayerMode::processCommand


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processConnectRequest(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Command& _command )
{
	Command connectResponce( CommandId::ConnectResponse, CommandType::Silent );

	boost::intrusive_ptr< IPlayer > freePlayer = m_landscapeModel.getFirstFreePlayer();

	if ( freePlayer )
	{
		m_landscapeModel.pushCommand( Command( CommandId::ChangePlayerName ).pushArgument( freePlayer->getUniqueId() ).pushArgument( _command.m_arguments[0].toString() ) );
		m_landscapeModel.pushCommand( Command( CommandId::ChangePlayerType ).pushArgument( freePlayer->getUniqueId() ).pushArgument( PlayerType::Player ) );

		QList< QVariant > playersList;

		ILandscapeModel::PlayersCollection players;
		m_landscapeModel.fetchPlayers( players );

		ILandscapeModel::PlayersCollectionIterator
				begin = players.begin()
			,	end = players.end();

		for ( ; begin != end; ++begin )
			playersList.push_back( PlayerData( ( *begin )->getUniqueId(), ( *begin )->getType(), ( *begin )->getName(), ( *begin )->getRace() ) );

		connectResponce.pushArgument( freePlayer->getUniqueId() );
		connectResponce.pushArgument( m_landscapeModel.getFilePath() );
		connectResponce.pushArgument( m_landscapeModel.getMyPlayer()->getUniqueId() );
		connectResponce.pushArgument( playersList );

		// TODO: other players should take data about new one

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

	// TODO: should not be like this

	QString filePath = _command.m_arguments[ 1 ].toString();

	if ( filePath != m_landscapeModel.getFilePath() )
		return;

	QList< QVariant > playersList =  _command.m_arguments[ 3 ].toList();

	QList< QVariant >::ConstIterator
			begin = playersList.begin()
		,	end = playersList.end();

	for ( ; begin != end; ++begin )
	{
		PlayerData data( begin->value< PlayerData >() );

		m_landscapeModel.pushCommand( Command( CommandId::ChangePlayerName, CommandType::Silent ).pushArgument( data.m_id ).pushArgument( data.m_name ) );
		m_landscapeModel.pushCommand( Command( CommandId::ChangePlayerRace, CommandType::Silent ).pushArgument( data.m_id ).pushArgument( data.m_race ) );
		m_landscapeModel.pushCommand( Command( CommandId::ChangePlayerType, CommandType::Silent ).pushArgument( data.m_id ).pushArgument( data.m_type ) );
	}

	m_connections.insert( std::make_pair( _command.m_arguments[ 2 ].toInt(), Framework::Core::NetworkManager::ConnectionInfo( _fromAddress, _fromPort ) ) );

} // MultiPlayerMode::processConnectResponse


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
