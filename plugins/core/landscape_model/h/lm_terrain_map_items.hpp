
#ifndef __LM_TERRAIN_MAP_ITEMS_HPP__
#define __LM_TERRAIN_MAP_ITEMS_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/h/lm_surface_items.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct TerrainMapItems
{
	enum Enum
	{
			Water	= 1
		,	Ground	= 2
		,	Object	= 4
	};

	static Enum fromSurfaceItem( const SurfaceItems::Enum _surfaceItem )
	{
		switch ( _surfaceItem )
		{
		case SurfaceItems::Grass:
		case SurfaceItems::Snow:
			return Ground;

		case SurfaceItems::Water:
			return Water;

		default:
			assert( !"Wrong surface item to terrain map item converion!" );
			return Ground;
		}
	}
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_TERRAIN_MAP_ITEMS_HPP__
