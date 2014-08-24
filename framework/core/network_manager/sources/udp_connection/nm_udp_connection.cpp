
#include "network_manager/sources/ph/nm_ph.hpp"

#include "network_manager/sources/udp_connection/nm_udp_connection.hpp"

#include "network_manager/ih/nm_iconnection_listener.hpp"
#include "network_manager/h/nm_resources.hpp"

#include "nm_udp_connection.moc"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

static const qint32 ms_protocolIdentifier = 11223344;

/*---------------------------------------------------------------------------*/


UdpConnection::UdpConnection(
		const ConnectionInfo& _connectionInfo
	,	const unsigned int _connectionTimeOut
	,	QObject* _parent
	)
	:	QObject( _parent )
	,	m_connectionInfo( _connectionInfo )
	,	m_udpSocket( new QUdpSocket( this ) )
	,	m_listenersCollection()
{
	m_udpSocket->bind( createHostAddress( m_connectionInfo.m_address ), m_connectionInfo.m_port );

	QObject::connect(m_udpSocket, SIGNAL( readyRead() ), this, SLOT( onReadReady() ) );

} // UdpConnection::UdpConnection


/*---------------------------------------------------------------------------*/


UdpConnection::~UdpConnection()
{
	assert( m_listenersCollection.empty() );

	QObject::disconnect(m_udpSocket, SIGNAL( readyRead() ), this, SLOT( onReadReady() ) );

} // UdpConnection::~UdpConnection


/*---------------------------------------------------------------------------*/


void
UdpConnection::sendDataTo( const ConnectionInfo& _to, const Data& _data )
{
	QByteArray data;

	data.append( static_cast< const char* >( static_cast< const void* >( &ms_protocolIdentifier ) ), sizeof( qint32 ) );
	data.append( static_cast< const char* >( static_cast< const void* >( &_data.m_id ) ), sizeof( Data::Id ) );
	data.append( _data.m_data );

	m_udpSocket->writeDatagram( _data.m_data, createHostAddress( _to.m_address ), _to.m_port );

} // UdpConnection::sendData


/*---------------------------------------------------------------------------*/


void
UdpConnection::addConnectionListener( IConnectionListener* _listener )
{
	ListenersCollectionIterator iterator = m_listenersCollection.find( _listener );

	if ( iterator == m_listenersCollection.end() )
		m_listenersCollection.insert( _listener );

} // UdpConnection::addConnectionListener


/*---------------------------------------------------------------------------*/


void
UdpConnection::removeConnectionListener( IConnectionListener* _listener )
{
	m_listenersCollection.erase( _listener );

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

		qint32 protocolId = *static_cast< const qint32* >( static_cast< const void* >( datagram.left( sizeof( qint32 ) ).data() ) );

		if ( protocolId != ms_protocolIdentifier )
			return;

		datagram.remove( 0, sizeof( qint32 ) );

		ListenersCollectionIterator
				begin = m_listenersCollection.begin()
			,	end = m_listenersCollection.end();

		Data::Id id = *static_cast< const Data::Id* >( static_cast< const void* >( datagram.left( sizeof( Data::Id ) ).data() ) );

		datagram.remove( 0, sizeof( Data::Id ) );

		Data data( id, datagram );

		for( ; begin != end; ++begin )
			( *begin )->onDataReceive( sender.toString(), senderPort, data );
    }

} // UdpConnection::onReadReady


/*---------------------------------------------------------------------------*/


QHostAddress
UdpConnection::createHostAddress( const QString& _address ) const
{
	return	_address == Resources::LocalHost
		?	QHostAddress( QHostAddress::LocalHost )
		:	QHostAddress( _address );

} // UdpConnection::createHostAddress


/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/
