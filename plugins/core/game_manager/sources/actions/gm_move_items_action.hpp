
#ifndef __GM_MOVE_ITEMS_ACTION_HPP__
#define __GM_MOVE_ITEMS_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "game_manager/sources/actions/gm_base_action.hpp"

#include "landscape_model/h/lm_point.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

class MoveAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MoveAction(
			const IEnvironment& _environment
		,	const LandscapeModel::Point& _to );

	virtual ~MoveAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void doAction();

	/*virtual*/ void undoAction();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const LandscapeModel::Point m_to;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_MOVE_ITEMS_ACTION_HPP__
