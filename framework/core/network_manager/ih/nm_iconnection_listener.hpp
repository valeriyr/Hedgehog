
#ifndef __NM_ICONNECTION_LISTENER_HPP__
#define __NM_ICONNECTION_LISTENER_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace Core {
namespace NetworkManager {

/*---------------------------------------------------------------------------*/

struct IConnectionListener
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
