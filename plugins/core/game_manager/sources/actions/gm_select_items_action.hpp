
#ifndef __GM_SELECT_ITEMS_ACTION_HPP__
#define __GM_SELECT_ITEMS_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "game_manager/sources/actions/gm_base_action.hpp"

#include "landscape_model/h/lm_point.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace GameManager {

/*---------------------------------------------------------------------------*/

class SelectAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SelectAction(
			const IEnvironment& _environment
		,	const LandscapeModel::Point& _from
		,	const LandscapeModel::Point& _to );

	virtual ~SelectAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void doAction();

	/*virtual*/ void undoAction();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const LandscapeModel::Point m_from;

	const LandscapeModel::Point m_to;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace GameManager
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_SELECT_ITEMS_ACTION_HPP__
