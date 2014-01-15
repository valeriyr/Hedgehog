
#ifndef __LM_OBJECT_STATES_HPP__
#define __LM_OBJECT_STATES_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ObjectState
{
	enum Enum
	{
			Standing		= 0
		,	Moving
		,	Attacking
		,	Building
		,	Dying
	};
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_OBJECT_STATES_HPP__
