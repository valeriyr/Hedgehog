
#ifndef __LM_ACTIONS_HPP__
#define __LM_ACTIONS_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct Actions
{
	enum Enum : qint32
	{
			Move				= 0
		,	Train
		,	GenerateResources
		,	Attack
		,	Build
		,	Repair
		,	CollectResource
	};
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ACTIONS_HPP__
