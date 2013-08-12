
#ifndef __SE_ENVIRONMENT_HPP__
#define __SE_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "server_engine/sources/environment/se_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessage( const QString& _message ) const;

	/*virtual*/ Framework::Core::NetworkManager::IUdpConnection&
		getConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const;

	/*virtual*/ void closeConnection( const Framework::Core::NetworkManager::ConnectionInfo& _connectionInfo ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __SE_ENVIRONMENT_HPP__
