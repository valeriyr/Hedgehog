
#ifndef __GM_IGAME_MANAGER_HPP__
#define __GM_IGAME_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

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
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void run() = 0;

	virtual void stop() = 0;

/*---------------------------------------------------------------------------*/

	virtual void pushMoveAction(
			boost::intrusive_ptr< LandscapeModel::IUnit > _unit
		,	const LandscapeModel::Point& _moveTo ) = 0;

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
