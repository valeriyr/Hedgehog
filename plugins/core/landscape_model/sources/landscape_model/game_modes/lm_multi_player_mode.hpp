
#ifndef __LM_MULTI_PLAYER_MODE_HPP__
#define __LM_MULTI_PLAYER_MODE_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/landscape_model/game_modes/lm_igame_mode.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"
#include "network_manager/ih/nm_iconnection_listener.hpp"

#include "landscape_model/sources/landscape_model/game_modes/lm_commands_queue.hpp"

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
			const IEnvironment& _environment
		,	const Framework::Core::NetworkManager::ConnectionInfo& _myConnectionInfo
		,	const Framework::Core::NetworkManager::ConnectionInfo& _connectTo );

	virtual ~MultiPlayerMode();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processCommand( Command& _command );

	/*virtual*/ bool prepareToTick( const TickType& _tick );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const CommandsQueue& getCommands() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ IGameMode::Type::Enum getType() const;

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

	void processDisconnect(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Command& _command );

	void processPassCommands(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Command& _command );

	void processCommandsRequest(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const Command& _command );

	void spreadPlayerConnectedCommand(
			const Tools::Core::Generators::IGenerator::IdType& _playerId
		,	const QString& _playerName
		,	const QString& _playerAddress
		,	const unsigned int _playerPort );

	void fillPassCommandsCommand(
			const IPlayer& _player
		,	const TickType& _targetTick
		,	Command& _command );

	void registerMetatypes();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< Tools::Core::Generators::IGenerator::IdType, Framework::Core::NetworkManager::ConnectionInfo >
		ConnectionsInfosCollection;
	typedef
		ConnectionsInfosCollection::const_iterator
		ConnectionsInfosCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const Framework::Core::NetworkManager::ConnectionInfo m_myConnectionInfo;

	boost::intrusive_ptr< Framework::Core::NetworkManager::IUdpConnection > m_myConnection;

	ConnectionsInfosCollection m_connections;

	CommandsQueue m_commandsQueue;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_MULTI_PLAYER_MODE_HPP__
