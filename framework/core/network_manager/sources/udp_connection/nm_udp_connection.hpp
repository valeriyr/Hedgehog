
#ifndef __NM_UDP_CONNECTION_HPP__
#define __NM_UDP_CONNECTION_HPP__

/*---------------------------------------------------------------------------*/

#include "network_manager/ih/nm_iudp_connection.hpp"

#include "network_manager/h/nm_connection_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

struct ConnectionInfo;

/*---------------------------------------------------------------------------*/

class UdpConnection
	:	public QObject
	,	public Tools::Core::BaseWrapper< IUdpConnection >
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	UdpConnection(
			const ConnectionInfo& _connectionInfo
		,	const unsigned int _connectionTimeOut
		,	QObject* _parent = NULL );

	virtual ~UdpConnection();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void sendDataTo( const ConnectionInfo& _to, const Data& _data );

	/*virtual*/ void addConnectionListener( IConnectionListener* _listener );

	/*virtual*/ void removeConnectionListener( IConnectionListener* _listener );

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onReadReady();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QHostAddress createHostAddress( const QString& _address ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::set< IConnectionListener* >
		ListenersCollection;
	typedef
		ListenersCollection::iterator
		ListenersCollectionIterator;

/*---------------------------------------------------------------------------*/

	ConnectionInfo m_connectionInfo;

	QUdpSocket* m_udpSocket;

	ListenersCollection m_listenersCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_UDP_CONNECTION_HPP__
