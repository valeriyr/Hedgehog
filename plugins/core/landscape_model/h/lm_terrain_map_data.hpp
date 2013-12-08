
#ifndef __LM_TERRAIN_MAP_ITEMS_HPP__
#define __LM_TERRAIN_MAP_ITEMS_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct TerrainMapItems
{
	enum Enum
	{
			NotAvailable = 1
		,	Ground		 = 2
		,	Water		 = 4

		,	Any			 = NotAvailable | Ground | Water
	};
};

/*---------------------------------------------------------------------------*/

struct TerrainMapData
{
	TerrainMapData()
		:	m_terrainMapItem( TerrainMapItems::Ground )
		,	m_engagedWithGround( false )
		,	m_engagedWithAir( false )
	{}

	TerrainMapData(
			const TerrainMapItems::Enum _terrainMapItem
		,	const bool _engagedWithGround
		,	const bool _engagedWithAir
		)
		:	m_terrainMapItem( _terrainMapItem )
		,	m_engagedWithGround( _engagedWithGround )
		,	m_engagedWithAir( _engagedWithAir )
	{}

	TerrainMapItems::Enum m_terrainMapItem;
	bool m_engagedWithGround;
	bool m_engagedWithAir;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_TERRAIN_MAP_ITEMS_HPP__