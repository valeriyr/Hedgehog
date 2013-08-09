
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

	/*virtual*/ IUdpConnection& getUdpConnection( const QString& _connectionId );

	/*virtual*/ void closeUdpConnection( const QString& _connectionId );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, boost::intrusive_ptr< IUdpConnection > >
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
