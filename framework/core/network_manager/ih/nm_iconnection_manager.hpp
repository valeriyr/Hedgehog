
#ifndef __NM_ICONNECTION_MANAGER_HPP__
#define __NM_ICONNECTION_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "network_manager/h/nm_connection_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

	const quint32 IID_CONNECTION_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IUdpConnection;

/*---------------------------------------------------------------------------*/

struct IConnectionManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IUdpConnection >
		getUdpConnection( const ConnectionInfo& _connectionInfo, const quint32 _connectionTimeOut ) = 0;

	virtual void closeUdpConnection( const ConnectionInfo& _connectionInfo ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_ICONNECTION_MANAGER_HPP__
