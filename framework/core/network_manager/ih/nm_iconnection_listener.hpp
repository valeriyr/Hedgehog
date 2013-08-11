
#ifndef __NM_ICONNECTION_LISTENER_HPP__
#define __NM_ICONNECTION_LISTENER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

struct IConnectionListener
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void onDataReceive(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const QByteArray& _data ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace NetworkManager
} // namespace Core
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __NM_ICONNECTION_LISTENER_HPP__
