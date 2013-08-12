
#ifndef __SE_ISERVER_ENGINE_HPP__
#define __SE_ISERVER_ENGINE_HPP__

/*---------------------------------------------------------------------------*/

#include "network_manager/ih/nm_iconnection_listener.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace ServerEngine {

/*---------------------------------------------------------------------------*/

struct IServerEngine
	:	public Framework::Core::NetworkManager::IConnectionListener
{

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace ServerEngine
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __SE_ISERVER_ENGINE_HPP__
