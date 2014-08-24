
#ifndef __NM_IUDP_CONNECTION_HPP__
#define __NM_IUDP_CONNECTION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "network_manager/h/nm_connection_info.hpp"
#include "network_manager/h/nm_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

struct IConnectionListener;

/*---------------------------------------------------------------------------*/

struct IUdpConnection
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void sendDataTo( const ConnectionInfo& _to, const Data& _data ) = 0;

	virtual void addConnectionListener( IConnectionListener* _listener ) = 0;

	virtual void removeConnectionListener( IConnectionListener* _listener ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_IUDP_CONNECTION_HPP__
