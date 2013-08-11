
#include "network_manager/sources/ph/nm_ph.hpp"

#include "network_manager/sources/udp_connection/nm_udp_connection.hpp"

#include "network_manager/ih/nm_iconnection_listener.hpp"

#include "nm_udp_connection.moc"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/


UdpConnection::UdpConnection( const ConnectionInfo& _connectionInfo, QObject* _parent )
	:	QObject( _parent )
	,	m_connectionInfo( _connectionInfo )
	,	m_udpSocket( new QUdpSocket( this ) )
	,	m_listenersCollection()
{
	m_udpSocket->bind( QHostAddress( m_connectionInfo.m_address ), m_connectionInfo.m_port );
	connect(m_udpSocket, SIGNAL( readyRead() ), this, SLOT( onReadReady() ) );

} // UdpConnection::UdpConnection


/*---------------------------------------------------------------------------*/


UdpConnection::~UdpConnection()
{
} // UdpConnection::~UdpConnection


/*---------------------------------------------------------------------------*/


void
UdpConnection::sendDataTo( const ConnectionInfo& _connectionInfo, const QByteArray& _data )
{
	m_udpSocket->writeDatagram( _data, QHostAddress( _connectionInfo.m_address ), _connectionInfo.m_port);

} // UdpConnection::sendData


/*---------------------------------------------------------------------------*/


void
UdpConnection::addConnectionListener( boost::intrusive_ptr< IConnectionListener > _listener )
{
	ListenersCollectionIterator iterator = m_listenersCollection.find( _listener );

	if ( iterator == m_listenersCollection.end() )
	{
		m_listenersCollection.insert( _listener );
	}

} // UdpConnection::addConnectionListener


/*---------------------------------------------------------------------------*/


void
UdpConnection::removeConnectionListener( boost::intrusive_ptr< IConnectionListener > _listener )
{
	ListenersCollectionIterator iterator = m_listenersCollection.find( _listener );

	if ( iterator != m_listenersCollection.end() )
	{
		m_listenersCollection.erase( iterator );
	}

} // UdpConnection::removeConnectionListener


/*---------------------------------------------------------------------------*/


void
UdpConnection::onReadReady()
{
	while ( m_udpSocket->hasPendingDatagrams() )
	{
        QByteArray datagram;
        datagram.resize( m_udpSocket->pendingDatagramSize() );

        QHostAddress sender;
        quint16 senderPort;

        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

		ListenersCollectionIterator
				begin = m_listenersCollection.begin()
			,	end = m_listenersCollection.end();

		for( ; begin != end; ++begin )
			( *begin )->onDataReceive( sender.toString(), senderPort, datagram );
    }

} // UdpConnection::onReadReady


/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
