
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
	const QString ms_type = "SimulationStarted";
}

/*---------------------------------------------------------------------------*/

namespace CurrentTickNumberChanged
{
	const QString ms_type = "CurrentTickNumberChanged";

	const QString ms_tickNumberAttribute = "TickNumber";
}

/*---------------------------------------------------------------------------*/

namespace VictoryConditionChanged
{
	const QString ms_type = "VictoryConditionChanged";

	const QString ms_conditionAttribute = "Condition";
}

/*---------------------------------------------------------------------------*/

namespace PlayerRaceChanged
{
	const QString ms_type = "PlayerRaceChanged";

	const QString ms_playerIdAttribute = "PlayerId";
	const QString ms_playerRaceAttribute = "PlayerRace";
}

/*---------------------------------------------------------------------------*/

namespace PlayerNameChanged
{
	const QString ms_type = "PlayerNameChanged";

	const QString ms_playerIdAttribute = "PlayerId";
	const QString ms_startPointIdAttribute = "StartPointId";
	const QString ms_playerNameAttribute = "PlayerName";
}

/*---------------------------------------------------------------------------*/

namespace PlayerTypeChanged
{
	const QString ms_type = "PlayerTypeChanged";

	const QString ms_playerIdAttribute = "PlayerId";
	const QString ms_playerTypeAttribute = "PlayerType";
}

/*---------------------------------------------------------------------------*/

namespace ObjectAdded
{
	const QString ms_type = "ObjectAdded";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectLocationAttribute = "ObjectLocation";
	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
	const QString ms_objectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace ObjectRemoved
{
	const QString ms_type = "ObjectRemoved";

	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace CreateObjectFailed
{
	const QString ms_type = "CreateObjectFailed";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectLocationAttribute = "ObjectLocation";
}

/*---------------------------------------------------------------------------*/

namespace ObjectMoved
{
	const QString ms_type = "ObjectMoved";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectIdAttribute = "ObjectId";
	const QString ms_movingFromAttribute = "MovingFrom";
	const QString ms_movingToAttribute = "MovingTo";
	const QString ms_movingProgressAttribute = "MovingProgress";
	const QString ms_movingSpeedAttribute = "MovingSpeed";
}

/*---------------------------------------------------------------------------*/

namespace ObjectStateChanged
{
	const QString ms_type = "ObjectStateChanged";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectIdAttribute = "ObjectId";
	const QString ms_objectState = "ObjectState";
	const QString ms_objectDirection = "ObjectDirection";
}

/*---------------------------------------------------------------------------*/

namespace ObjectHealthChanged
{
	const QString ms_type = "ObjectHealthChanged";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectIdAttribute = "ObjectId";
	const QString ms_objectHealth = "ObjectHealth";
}

/*---------------------------------------------------------------------------*/

namespace ObjectWasHit
{
	const QString ms_type = "ObjectWasHit";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectIdAttribute = "ObjectId";
	const QString ms_objectHealth = "ObjectHealth";
}

/*---------------------------------------------------------------------------*/

namespace ObjectReadyToAttack
{
	const QString ms_type = "ObjectReadyToAttack";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectIdAttribute = "ObjectId";
	const QString ms_objectDirection = "ObjectDirection";
}

/*---------------------------------------------------------------------------*/

namespace ObjectsSelectionChanged
{
	const QString ms_type = "ObjectsSelectionChanged";
}

/*---------------------------------------------------------------------------*/

namespace SurfaceItemChanged
{
	const QString ms_type = "SurfaceItemChanged";

	const QString ms_surfaceItemIdAttribute = "SurfaceItemId";
	const QString ms_surfaceItemLocationAttribute = "SurfaceItemLocation";
}

/*---------------------------------------------------------------------------*/

namespace ResourceValueChanged
{
	const QString ms_type = "ResourceValueChanged";
}

/*---------------------------------------------------------------------------*/

namespace TrainQueueChanged
{
	const QString ms_type = "TrainQueueChanged";

	const QString ms_trainerIdAttribute = "TrainerId";
}

/*---------------------------------------------------------------------------*/

namespace TrainProgressChanged
{
	const QString ms_type = "TrainProgressChanged";

	const QString ms_trainerIdAttribute = "TrainerId";
	const QString ms_trainerProgressAttribute = "TrainerProgress";
	const QString ms_creationTimeAttribute = "CreationTime";
}

/*---------------------------------------------------------------------------*/

namespace BuildQueueChanged
{
	const QString ms_type = "BuildQueueChanged";

	const QString ms_builderIdAttribute = "BuilderId";
}

/*---------------------------------------------------------------------------*/

namespace ObjectStartBuilding
{
	const QString ms_type = "ObjectStartBuilding";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectLocationAttribute = "ObjectLocation";
	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
	const QString ms_objectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace BuilderHasStartedBuild
{
	const QString ms_type = "BuilderHasStartedBuild";
	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace BuilderHasFinishedBuild
{
	const QString ms_type = "BuilderHasFinishedBuild";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectLocationAttribute = "ObjectLocation";
	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
	const QString ms_objectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace ResourceSourceValueChanged
{
	const QString ms_type = "ResourceSourceValueChanged";

	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
	const QString ms_sourceResourceNameAttribute = "SourceResourceNameAttribute";
	const QString ms_sourceResourceValueAttribute = "SourceResourceValueAttribute";
}

/*---------------------------------------------------------------------------*/

namespace HolderHasStartedCollect
{
	const QString ms_type = "HolderHasStartedCollect";
	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

namespace HolderHasStopCollect
{
	const QString ms_type = "HolderHasStopCollect";

	const QString ms_objectNameAttribute = "ObjectName";
	const QString ms_objectLocationAttribute = "ObjectLocation";
	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
	const QString ms_objectEmplacementAttribute = "ObjectEmplacement";
}

/*---------------------------------------------------------------------------*/

namespace HolderResourceCountChanged
{
	const QString ms_type = "HolderResourceCountChanged";

	const QString ms_objectUniqueIdAttribute = "ObjectUniqueId";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_EVENTS_HPP__
