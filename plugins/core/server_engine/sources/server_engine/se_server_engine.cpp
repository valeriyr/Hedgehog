
#include "server_engine/sources/ph/se_ph.hpp"

#include "server_engine/sources/server_engine/se_server_engine.hpp"

#include "server_engine/sources/environment/se_ienvironment.hpp"

#include "network_manager/ih/nm_iudp_connection.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

/*---------------------------------------------------------------------------*/


ServerEngine::ServerEngine( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_connectionInfo( "127.0.0.1", 2013 )
	,	m_connection( _environment.getConnection( m_connectionInfo ) )
{
	m_connection.addConnectionListener( this );

	m_environment.printMessage( QString( "Socket was opened on: '%1:%2'." ).arg( m_connectionInfo.m_address ).arg( m_connectionInfo.m_port ) );

} // ServerEngine::ServerEngine


/*---------------------------------------------------------------------------*/


ServerEngine::~ServerEngine()
{
	m_connection.removeConnectionListener( this );
	m_environment.closeConnection( m_connectionInfo );

	m_environment.printMessage( QString( "Socket was closed on: '%1:%2'." ).arg( m_connectionInfo.m_address ).arg( m_connectionInfo.m_port ) );

} // ServerEngine::~ServerEngine


/*---------------------------------------------------------------------------*/


void
ServerEngine::onDataReceive(
		const QString& _fromAddress
	,	const unsigned int _fromPort
	,	const QByteArray& _data )
{
	m_environment.printMessage( QString( "Received data from '%1:%2': '%3'." ).arg( _fromAddress ).arg( _fromPort ).arg( _data.data() ) );

	m_connection.sendDataTo( Framework::Core::NetworkManager::ConnectionInfo( "127.0.0.1", 1988 ), QString( "waiting for the new actions" ).toUtf8() );

} // ServerEngine::onDataReceive


/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
