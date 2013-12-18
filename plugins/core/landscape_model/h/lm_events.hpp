
#ifndef __LM_EVENTS_HPP__
#define __LM_EVENTS_HPP__

#include "event_manager/h/em_event.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Events {

/*---------------------------------------------------------------------------*/

namespace LandscapeLoaded
{
	const char* const ms_type = "LandscapeLoaded";
}

/*---------------------------------------------------------------------------*/

namespace ObjectCreated
{
	const char* const ms_type = "ObjectCreated";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectPositionAttribute = "ObjectPosition";
	const char* const ms_objectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace UnitMoved
{
	const char* const ms_type = "UnitMoved";

	const char* const ms_unitIdAttribute = "UnitId";
	const char* const ms_movingFromAttribute = "MovingFrom";
	const char* const ms_movingToAttribute = "MovingTo";
	const char* const ms_movingProgressAttribute = "MovingProgress";
}

/*---------------------------------------------------------------------------*/

namespace UnitsSelectionChanged
{
	const char* const ms_type = "UnitsSelectionChanged";
}

/*---------------------------------------------------------------------------*/

namespace SurfaceItemChanged
{
	const char* const ms_type = "SurfaceItemChanged";

	const char* const ms_surfaceItemIdAttribute = "SurfaceItemId";
	const char* const ms_surfaceItemPositionAttribute = "SurfaceItemPosition";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_EVENTS_HPP__
