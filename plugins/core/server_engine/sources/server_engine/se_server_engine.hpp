
#ifndef __SE_SERVER_ENGINE_HPP__
#define __SE_SERVER_ENGINE_HPP__

/*---------------------------------------------------------------------------*/

#include "server_engine/sources/server_engine/se_iserver_engine.hpp"

#include "network_manager/h/nm_connection_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace Core
	{
		namespace NetworkManager
		{
			struct IUdpConnection;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class ServerEngine
	:	public Tools::Core::BaseWrapper< IServerEngine >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ServerEngine( const IEnvironment& _environment );

	virtual ~ServerEngine();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void onDataReceive(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const QByteArray& _data );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

	Framework::Core::NetworkManager::ConnectionInfo m_connectionInfo;

	Framework::Core::NetworkManager::IUdpConnection& m_connection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __SE_SERVER_ENGINE_HPP__
