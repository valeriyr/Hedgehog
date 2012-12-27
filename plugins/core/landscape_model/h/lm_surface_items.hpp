
#ifndef __LM_SURFACE_ITEMS_HPP__
#define __LM_SURFACE_ITEMS_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct SurfaceItems
{
	enum Enum
	{
			Grass	= 1
		,	Snow	= 2
		,	Sand	= 4
		,	Water	= 8

		,	Last
	};
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SURFACE_ITEMS_HPP__
