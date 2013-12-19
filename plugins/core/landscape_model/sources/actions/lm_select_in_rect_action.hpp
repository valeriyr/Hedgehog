
#ifndef __GM_SELECT_IN_RECT_ACTION_HPP__
#define __GM_SELECT_IN_RECT_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class SelectInRectAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SelectInRectAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	const QRect& _rect );

	virtual ~SelectInRectAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ void unprocessAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QRect m_rect;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_SELECT_IN_RECT_ACTION_HPP__
