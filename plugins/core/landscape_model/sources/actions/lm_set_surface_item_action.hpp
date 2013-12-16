
#ifndef __GM_SET_SURFACE_ITEM_ACTION_HPP__
#define __GM_SET_SURFACE_ITEM_ACTION_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/sources/actions/lm_base_action.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class SetSurfaceItemAction
	:	public BaseAction
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SetSurfaceItemAction(
			const IEnvironment& _environment
		,	ILandscapeModel& _landscapeModel
		,	const QPoint& _position
		,	const Core::LandscapeModel::ISurfaceItem::IdType& _id );

	virtual ~SetSurfaceItemAction();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void processAction( const unsigned int _deltaTime );

	/*virtual*/ void unprocessAction( const unsigned int _deltaTime );

	/*virtual*/ bool hasFinished() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QPoint m_position;

	const Core::LandscapeModel::ISurfaceItem::IdType m_id;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __GM_SET_SURFACE_ITEM_ACTION_HPP__
