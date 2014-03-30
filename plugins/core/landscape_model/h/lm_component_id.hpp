
#ifndef __LM_COMPONENT_ID_HPP__
#define __LM_COMPONENT_ID_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ComponentId
{
	enum Enum
	{
			Health		= 1
		,	Locate
		,	Train
		,	Selection
		,	Actions
		,	Move
		,	Attack
		,	Build
		,	ResourcesGenerating
		,	ResourceHolder
		,	ResourceSource
	};
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COMPONENT_ID_HPP__
