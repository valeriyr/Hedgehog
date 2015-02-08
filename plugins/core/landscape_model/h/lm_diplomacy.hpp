
#ifndef __LM_DIPLOMACY_HPP__
#define __LM_DIPLOMACY_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct Diplomacy
{
	enum Enum : qint32
	{
			Allied		= 0
		,	Enemy
		,	Neutral
	};
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_DIPLOMACY_HPP__
