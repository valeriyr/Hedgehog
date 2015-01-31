
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
			Locate		= 1
		,	Train
		,	Actions
		,	Move
		,	Build
		,	Repair
		,	ResourcesGenerating
		,	ResourceHolder
		,	ResourceSource
		,	ResourceStorage
	};
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_COMPONENT_ID_HPP__
