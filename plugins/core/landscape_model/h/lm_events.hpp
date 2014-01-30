
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

namespace ObjectAdded
{
	const char* const ms_type = "ObjectAdded";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectLocationAttribute = "ObjectLocation";
	const char* const ms_objectUniqueIdAttribute = "ObjectUniqueId";
	const char* const ms_objectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace ObjectRemoved
{
	const char* const ms_type = "ObjectRemoved";

	const char* const ms_objectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace CreateObjectFailed
{
	const char* const ms_type = "CreateObjectFailed";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectLocationAttribute = "ObjectLocation";
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

namespace ObjectDataChanged
{
	const char* const ms_type = "ObjectDataChanged";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectIdAttribute = "ObjectId";
	const char* const ms_objectHealth = "ObjectHealth";
}

/*---------------------------------------------------------------------------*/

namespace ObjectWasHit
{
	const char* const ms_type = "ObjectWasHit";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectIdAttribute = "ObjectId";
	const char* const ms_objectHealth = "ObjectHealth";
}

/*---------------------------------------------------------------------------*/

namespace ObjectReadyToAttack
{
	const char* const ms_type = "ObjectReadyToAttack";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectIdAttribute = "ObjectId";
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

namespace ResourceValueChanged
{
	const char* const ms_type = "ResourceValueChanged";
}

/*---------------------------------------------------------------------------*/

namespace TrainQueueChanged
{
	const char* const ms_type = "TrainQueueChanged";

	const char* const ms_trainerIdAttribute = "TrainerId";
}

/*---------------------------------------------------------------------------*/

namespace BuildQueueChanged
{
	const char* const ms_type = "BuildQueueChanged";

	const char* const ms_builderIdAttribute = "BuilderId";
}

/*---------------------------------------------------------------------------*/

namespace ObjectStartBuilding
{
	const char* const ms_type = "ObjectStartBuilding";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectLocationAttribute = "ObjectLocation";
	const char* const ms_objectUniqueIdAttribute = "ObjectUniqueId";
	const char* const ms_objectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace BuilderHasFinishedBuild
{
	const char* const ms_type = "BuilderHasFinishedBuild";

	const char* const ms_objectNameAttribute = "ObjectName";
	const char* const ms_objectLocationAttribute = "ObjectLocation";
	const char* const ms_objectUniqueIdAttribute = "ObjectUniqueId";
	const char* const ms_objectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_EVENTS_HPP__
