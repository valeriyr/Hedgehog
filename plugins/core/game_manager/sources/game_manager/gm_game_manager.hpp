
#ifndef __GM_GAME_MANAGER_HPP__
#define __GM_GAME_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "game_manager/ih/gm_igame_manager.hpp"

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
namespace GameManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct IActionsQueue;

/*---------------------------------------------------------------------------*/

class GameManager
	:	public Tools::Core::BaseWrapper< IGameManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	GameManager(
			const IEnvironment& _environment
		,	boost::intrusive_ptr< IActionsQueue > _actionsQueue );

	virtual ~GameManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void run();

	/*virtual*/ void stop();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void pushMoveAction( const LandscapeModel::Point& _moveTo );

	/*virtual*/ void pushSelectAction(
			const LandscapeModel::Point& _from
		,	const LandscapeModel::Point& _to );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	/*virtual*/ void onDataReceive(
			const QString& _fromAddress
		,	const unsigned int _fromPort
		,	const QByteArray& _data );

/*---------------------------------------------------------------------------*/

	void runActionsProcessing();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::NetworkManager::ConnectionInfo m_connectionInfo;

	Framework::Core::NetworkManager::IUdpConnection& m_connection;

	boost::intrusive_ptr< IActionsQueue > m_actionsQueue;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_GAME_MANAGER_HPP__
