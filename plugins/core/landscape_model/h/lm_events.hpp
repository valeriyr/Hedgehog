
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
	const char* const ms_objectLocationAttribute = "ObjectLocation";
	const char* const ms_objectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace ObjectMoved
{
	const char* const ms_type = "ObjectMoved";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectIdAttribute = "ObjectId";
	const char* const ms_movingFromAttribute = "MovingFrom";
	const char* const ms_movingToAttribute = "MovingTo";
	const char* const ms_movingProgressAttribute = "MovingProgress";
}

/*---------------------------------------------------------------------------*/

namespace ObjectStateChanged
{
	const char* const ms_type = "ObjectStateChanged";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectIdAttribute = "ObjectId";
	const char* const ms_objectState = "ObjectState";
	const char* const ms_objectDirection = "ObjectDirection";
}

/*---------------------------------------------------------------------------*/

namespace ObjectsSelectionChanged
{
	const char* const ms_type = "ObjectsSelectionChanged";
}

/*---------------------------------------------------------------------------*/

namespace SurfaceItemChanged
{
	const char* const ms_type = "SurfaceItemChanged";

	const char* const ms_surfaceItemIdAttribute = "SurfaceItemId";
	const char* const ms_surfaceItemLocationAttribute = "SurfaceItemLocation";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_EVENTS_HPP__
