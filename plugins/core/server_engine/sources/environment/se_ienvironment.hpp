
#ifndef __SE_IENVIRONMENT_HPP__
#define __SE_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace Core
	{
		namespace NetworkManager
		{
			struct IUdpConnection;
			struct ConnectionInfo;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void printMessage( const QString& _message ) const = 0;

	virtual Framework::Core::NetworkManager::IUdpConnection&
		getConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const = 0;

	virtual void closeConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __SE_IENVIRONMENT_HPP__
