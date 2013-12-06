
#ifndef __LM_EVENTS_HPP__
#define __LM_EVENTS_HPP__

#include "event_manager/h/em_event.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {
namespace Events {

/*---------------------------------------------------------------------------*/

namespace UnitMoved
{
	const char* const ms_type = "UnitMoved";

	const char* const ms_unitIdAttribute = "UnitId";
	const char* const ms_movingToAttribute = "MovingTo";
	const char* const ms_movingProgressAttribute = "MovingProgress";
};

/*---------------------------------------------------------------------------*/

namespace UnitSelected
{
	const char* const ms_type = "UnitSelected";

	const char* const ms_unitIdAttribute = "UnitId";
}

/*---------------------------------------------------------------------------*/

} // namespace Events
} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_EVENTS_HPP__
