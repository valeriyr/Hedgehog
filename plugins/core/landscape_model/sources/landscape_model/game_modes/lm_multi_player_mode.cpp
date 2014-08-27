
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


MultiPlayerMode::MultiPlayerMode(
		ILandscapeModel& _landscapeModel
	,	const IEnvironment& _environment
	,	const Framework::Core::NetworkManager::ConnectionInfo& _myConnectionInfo
	,	const Framework::Core::NetworkManager::ConnectionInfo& _connectTo
	)
	:	m_landscapeModel( _landscapeModel )
	,	m_environment( _environment )
	,	m_myConnectionInfo( _myConnectionInfo )
	,	m_connection()
{
	m_connection = m_environment.getConnection( m_myConnectionInfo, m_environment.getUInt( Resources::Properties::ConnectionTimeOut ) );
	m_connection->addConnectionListener( this );

	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Info
		,	QString( Resources::SocketHasBeenOpenedMessage ).arg( m_myConnectionInfo.m_address ).arg( m_myConnectionInfo.m_port ) );

	if ( !_connectTo.isEmpty() )
	{
		Framework::Core::NetworkManager::Data data( 12345, "CONNECT" );
		m_connection->sendDataTo( _connectTo, data );
	}

} // MultiPlayerMode::MultiPlayerMode


/*---------------------------------------------------------------------------*/


MultiPlayerMode::~MultiPlayerMode()
{
	m_connection->removeConnectionListener( this );
	m_environment.closeConnection( m_myConnectionInfo );

	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Info
		,	QString( Resources::SocketHasBeenClosedMessage ).arg( m_myConnectionInfo.m_address ).arg( m_myConnectionInfo.m_port ) );

} // MultiPlayerMode::~MultiPlayerMode


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::processCommand( const Command& _command )
{
	m_landscapeModel.processCommand( _command );

} // MultiPlayerMode::processCommand


/*---------------------------------------------------------------------------*/


void
MultiPlayerMode::onDataReceive(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const Framework::Core::NetworkManager::Data& _data )
{
	m_environment.printMessage(
			Tools::Core::IMessenger::MessegeLevel::Info
		,	QString( Resources::CommandReceivedMessage )
				.arg( _fromAddress )
				.arg( _fromPort )
				.arg( _data.m_id )
				.arg( QString( _data.m_data ) ) );

} // MultiPlayerMode::onDataReceive


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
