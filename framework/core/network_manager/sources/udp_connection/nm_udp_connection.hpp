
#ifndef __NM_UDP_CONNECTION_HPP__
#define __NM_UDP_CONNECTION_HPP__

/*---------------------------------------------------------------------------*/

#include "network_manager/ih/nm_iudp_connection.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

class UdpConnection
	:	public Tools::Core::BaseWrapper< IUdpConnection >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	UdpConnection();

	virtual ~UdpConnection();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_UDP_CONNECTION_HPP__
