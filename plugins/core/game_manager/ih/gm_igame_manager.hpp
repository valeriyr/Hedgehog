
#ifndef __GM_IGAME_MANAGER_HPP__
#define __GM_IGAME_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "network_manager/ih/nm_iconnection_listener.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct IUnit;
			struct Point;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_GAME_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IGameManager
	:	public Framework::Core::NetworkManager::IConnectionListener
{

/*---------------------------------------------------------------------------*/

	virtual void run() = 0;

	virtual void stop() = 0;

/*---------------------------------------------------------------------------*/

	virtual void pushMoveAction( const LandscapeModel::Point& _moveTo ) = 0;

	virtual void pushSelectAction(
			const LandscapeModel::Point& _from
		,	const LandscapeModel::Point& _to ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_IGAME_MANAGER_HPP__
