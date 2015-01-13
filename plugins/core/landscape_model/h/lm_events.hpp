
#ifndef __LM_EVENTS_HPP__
#define __LM_EVENTS_HPP__

#include "event_manager/h/em_event.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Events {

/*---------------------------------------------------------------------------*/

namespace SimulationStarted
{
	const QString Type = "SimulationStarted";
}

/*---------------------------------------------------------------------------*/

namespace CurrentTickNumberChanged
{
	const QString Type = "CurrentTickNumberChanged";

	const QString TickNumberAttribute = "TickNumber";
}

/*---------------------------------------------------------------------------*/

namespace VictoryConditionChanged
{
	const QString Type = "VictoryConditionChanged";

	const QString ConditionAttribute = "Condition";
}

/*---------------------------------------------------------------------------*/

namespace PlayerRaceChanged
{
	const QString Type = "PlayerRaceChanged";

	const QString PlayerIdAttribute = "PlayerId";
	const QString PlayerRaceAttribute = "PlayerRace";
}

/*---------------------------------------------------------------------------*/

namespace PlayerNameChanged
{
	const QString Type = "PlayerNameChanged";

	const QString PlayerIdAttribute = "PlayerId";
	const QString StartPointIdAttribute = "StartPointId";
	const QString PlayerNameAttribute = "PlayerName";
}

/*---------------------------------------------------------------------------*/

namespace PlayerTypeChanged
{
	const QString Type = "PlayerTypeChanged";

	const QString PlayerIdAttribute = "PlayerId";
	const QString PlayerTypeAttribute = "PlayerType";
}

/*---------------------------------------------------------------------------*/

namespace ObjectAdded
{
	const QString Type = "ObjectAdded";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectLocationAttribute = "ObjectLocation";
	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
	const QString ObjectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace ObjectRemoved
{
	const QString Type = "ObjectRemoved";

	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace CreateObjectFailed
{
	const QString Type = "CreateObjectFailed";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectLocationAttribute = "ObjectLocation";
}

/*---------------------------------------------------------------------------*/

namespace ObjectMoved
{
	const QString Type = "ObjectMoved";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectIdAttribute = "ObjectId";
	const QString MovingFromAttribute = "MovingFrom";
	const QString MovingToAttribute = "MovingTo";
	const QString MovingProgressAttribute = "MovingProgress";
	const QString MovingSpeedAttribute = "MovingSpeed";
}

/*---------------------------------------------------------------------------*/

namespace ObjectStateChanged
{
	const QString Type = "ObjectStateChanged";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectIdAttribute = "ObjectId";
	const QString ObjectState = "ObjectState";
	const QString ObjectDirection = "ObjectDirection";
}

/*---------------------------------------------------------------------------*/

namespace ObjectHealthChanged
{
	const QString Type = "ObjectHealthChanged";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectIdAttribute = "ObjectId";
	const QString ObjectHealth = "ObjectHealth";
}

/*---------------------------------------------------------------------------*/

namespace ObjectWasHit
{
	const QString Type = "ObjectWasHit";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectIdAttribute = "ObjectId";
	const QString ObjectHealth = "ObjectHealth";
}

/*---------------------------------------------------------------------------*/

namespace ObjectReadyToAttack
{
	const QString Type = "ObjectReadyToAttack";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectIdAttribute = "ObjectId";
	const QString ObjectDirection = "ObjectDirection";
}

/*---------------------------------------------------------------------------*/

namespace ObjectsSelectionChanged
{
	const QString Type = "ObjectsSelectionChanged";
}

/*---------------------------------------------------------------------------*/

namespace SurfaceItemChanged
{
	const QString Type = "SurfaceItemChanged";

	const QString SurfaceItemIdAttribute = "SurfaceItemId";
	const QString SurfaceItemLocationAttribute = "SurfaceItemLocation";
}

/*---------------------------------------------------------------------------*/

namespace ResourceValueChanged
{
	const QString Type = "ResourceValueChanged";
}

/*---------------------------------------------------------------------------*/

namespace TrainQueueChanged
{
	const QString Type = "TrainQueueChanged";

	const QString TrainerIdAttribute = "TrainerId";
}

/*---------------------------------------------------------------------------*/

namespace TrainProgressChanged
{
	const QString Type = "TrainProgressChanged";

	const QString TrainerIdAttribute = "TrainerId";
	const QString TrainerProgressAttribute = "TrainerProgress";
	const QString CreationTimeAttribute = "CreationTime";
}

/*---------------------------------------------------------------------------*/

namespace BuildQueueChanged
{
	const QString Type = "BuildQueueChanged";

	const QString BuilderIdAttribute = "BuilderId";
}

/*---------------------------------------------------------------------------*/

namespace ObjectStartBuilding
{
	const QString Type = "ObjectStartBuilding";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectLocationAttribute = "ObjectLocation";
	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
	const QString ObjectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace BuilderHasStartedBuild
{
	const QString Type = "BuilderHasStartedBuild";
	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace BuilderHasFinishedBuild
{
	const QString Type = "BuilderHasFinishedBuild";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectLocationAttribute = "ObjectLocation";
	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
	const QString ObjectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace ResourceSourceValueChanged
{
	const QString Type = "ResourceSourceValueChanged";

	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
	const QString SourceResourceNameAttribute = "SourceResourceNameAttribute";
	const QString SourceResourceValueAttribute = "SourceResourceValueAttribute";
}

/*---------------------------------------------------------------------------*/

namespace HolderHasStartedCollect
{
	const QString Type = "HolderHasStartedCollect";
	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace HolderHasStopCollect
{
	const QString Type = "HolderHasStopCollect";

	const QString ObjectNameAttribute = "ObjectName";
	const QString ObjectLocationAttribute = "ObjectLocation";
	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
	const QString ObjectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace HolderResourceCountChanged
{
	const QString Type = "HolderResourceCountChanged";

	const QString ObjectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_EVENTS_HPP__
