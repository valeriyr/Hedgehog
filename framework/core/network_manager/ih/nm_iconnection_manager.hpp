
#ifndef __NM_ICONNECTION_MANAGER_HPP__
#define __NM_ICONNECTION_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_CONNECTION_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IUdpConnection;

/*---------------------------------------------------------------------------*/

struct IConnectionManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual IUdpConnection& getUdpConnection( const QString& _connectionId ) = 0;

	virtual void closeUdpConnection( const QString& _connectionId ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_ICONNECTION_MANAGER_HPP__
