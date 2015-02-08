
#ifndef __NM_CONNECTION_MANAGER_HPP__
#define __NM_CONNECTION_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "network_manager/ih/nm_iconnection_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

class ConnectionManager
	:	public Tools::Core::BaseWrapper< IConnectionManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ConnectionManager();

	virtual ~ConnectionManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< IUdpConnection >
		getUdpConnection( const ConnectionInfo& _connectionInfo, const quint32 _connectionTimeOut );

	/*virtual*/ void closeUdpConnection( const ConnectionInfo& _connectionInfo  );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< ConnectionInfo, boost::intrusive_ptr< IUdpConnection > >
		ConnectionsCollection;
	typedef
		ConnectionsCollection::iterator
		ConnectionsCollectionIterator;

/*---------------------------------------------------------------------------*/

	ConnectionsCollection m_connectionsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_CONNECTION_MANAGER_HPP__
