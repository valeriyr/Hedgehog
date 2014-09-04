
#ifndef __LM_MULTI_PLAYER_MODE_HPP__
#define __LM_MULTI_PLAYER_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/game_modes/lm_igame_mode.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"

#include "network_manager/ih/nm_iconnection_listener.hpp"

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

	/*virtual*/ void processCommand( const Command& _command );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void onDataReceive(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Framework::Core::NetworkManager::Data& _data );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void sendCommand(
			const Framework::Core::NetworkManager::ConnectionInfo& _sendTo
		,	const Command& _command );

	void spreadCommand( const Command& _command );

	void processCommand(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Command& _command );

	void processConnectRequest(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Command& _command );

	void processConnectResponse(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Command& _command );

	void processPlayerConnected(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Command& _command );

	void spreadPlayerConnectedCommand(
			const IPlayer::Id& _playerId
		,	const QString& _playerName
		,	const QString& _playerAddress
		,	const unsigned int _playerPort );

	void registerMetatypes();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< IPlayer::Id, Framework::Core::NetworkManager::ConnectionInfo >
		ConnectionsInfosCollection;
	typedef
		ConnectionsInfosCollection::const_iterator
		ConnectionsInfosCollectionIterator;

/*---------------------------------------------------------------------------*/

	ILandscapeModel& m_landscapeModel;

	const IEnvironment& m_environment;

	const Framework::Core::NetworkManager::ConnectionInfo m_myConnectionInfo;

	boost::intrusive_ptr< Framework::Core::NetworkManager::IUdpConnection > m_myConnection;

	ConnectionsInfosCollection m_connections;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MULTI_PLAYER_MODE_HPP__
