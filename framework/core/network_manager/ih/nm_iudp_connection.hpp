
#ifndef __NM_IUDP_CONNECTION_HPP__
#define __NM_IUDP_CONNECTION_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "network_manager/h/nm_connection_info.hpp"

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

	virtual void sendDataTo( const ConnectionInfo& _to, const QByteArray& _data ) = 0;

	virtual void addConnectionListener( boost::intrusive_ptr< IConnectionListener > _listener ) = 0;

	virtual void removeConnectionListener( boost::intrusive_ptr< IConnectionListener > _listener ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_IUDP_CONNECTION_HPP__
