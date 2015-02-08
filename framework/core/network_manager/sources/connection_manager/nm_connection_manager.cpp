
#include "network_manager/sources/ph/nm_ph.hpp"

#include "network_manager/sources/connection_manager/nm_connection_manager.hpp"

#include "network_manager/sources/udp_connection/nm_udp_connection.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/


ConnectionManager::ConnectionManager()
	:	m_connectionsCollection()
{
} // ConnectionManager::ConnectionManager


/*---------------------------------------------------------------------------*/


ConnectionManager::~ConnectionManager()
{
	assert( m_connectionsCollection.empty() );

} // ConnectionManager::~ConnectionManager


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IUdpConnection >
ConnectionManager::getUdpConnection( const ConnectionInfo& _connectionInfo, const quint32 _connectionTimeOut )
{
	ConnectionsCollectionIterator iterator = m_connectionsCollection.find( _connectionInfo );

	if ( iterator != m_connectionsCollection.end() )
		return iterator->second;

	boost::intrusive_ptr< IUdpConnection > connection( new UdpConnection( _connectionInfo, _connectionTimeOut ) );

	m_connectionsCollection.insert( std::make_pair( _connectionInfo, connection ) );

	return connection;

} // ConnectionManager::getUdpConnection


/*---------------------------------------------------------------------------*/


void
ConnectionManager::closeUdpConnection( const ConnectionInfo& _connectionInfo )
{
	m_connectionsCollection.erase( _connectionInfo );

} // ConnectionManager::closeUdpConnection


/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
