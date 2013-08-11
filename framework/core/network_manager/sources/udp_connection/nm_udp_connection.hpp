
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

	UdpConnection( const ConnectionInfo& _connectionInfo, QObject* _parent = NULL );

	virtual ~UdpConnection();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void sendDataTo( const ConnectionInfo& _connectionInfo, const QByteArray& _data );

	/*virtual*/ void addConnectionListener( boost::intrusive_ptr< IConnectionListener > _listener );

	/*virtual*/ void removeConnectionListener( boost::intrusive_ptr< IConnectionListener > _listener );

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onReadReady();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::set< boost::intrusive_ptr< IConnectionListener > >
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
