
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
};

/*---------------------------------------------------------------------------*/

namespace UnitMoved
{
	const char* const ms_type = "UnitMoved";

	const char* const ms_unitIdAttribute = "UnitId";
	const char* const ms_movingToAttribute = "MovingTo";
	const char* const ms_movingProgressAttribute = "MovingProgress";
};

/*---------------------------------------------------------------------------*/

namespace UnitsSelectionChanged
{
	const char* const ms_type = "UnitsSelectionChanged";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_EVENTS_HPP__
