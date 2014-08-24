
#ifndef __LM_MULTI_PLAYER_MODE_HPP__
#define __LM_MULTI_PLAYER_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/game_modes/lm_igame_mode.hpp"

#include "landscape_model/h/lm_start_point.hpp"

#include"network_manager/h/nm_connection_info.hpp"
#include"network_manager/ih/nm_iconnection_listener.hpp"

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
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscapeModel;
struct IEnvironment;

/*---------------------------------------------------------------------------*/

class MultiPlayerMode
	:	public Tools::Core::BaseWrapper< IGameMode >
	,	public Framework::Core::NetworkManager::IConnectionListener
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MultiPlayerMode(
			ILandscapeModel& _landscapeModel
		,	const IEnvironment& _environment
		,	const Framework::Core::NetworkManager::ConnectionInfo& _myConnectionInfo
		,	const Framework::Core::NetworkManager::ConnectionInfo& _connectTo );

	virtual ~MultiPlayerMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processCommand();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void onDataReceive(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Framework::Core::NetworkManager::Data& _data );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< StartPoint::Id, boost::intrusive_ptr< Framework::Core::NetworkManager::ConnectionInfo > >
		ConnectionsInfosCollection;

/*---------------------------------------------------------------------------*/

	ILandscapeModel& m_landscapeModel;

	const IEnvironment& m_environment;

	const Framework::Core::NetworkManager::ConnectionInfo m_myConnectionInfo;

	boost::intrusive_ptr< Framework::Core::NetworkManager::IUdpConnection > m_connection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MULTI_PLAYER_MODE_HPP__
