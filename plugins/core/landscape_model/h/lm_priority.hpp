
#ifndef __LM_PRIORITY_HPP__
#define __LM_PRIORITY_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct Priority
{
	enum Enum : qint32
	{
			Idle	= 0
		,	Low
		,	Middle
		,	High
		,	Extreme
	};
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_PRIORITY_HPP__
