
#ifndef __LM_TERRAIN_MAP_ITEMS_HPP__
#define __LM_TERRAIN_MAP_ITEMS_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct TerrainMapItem
{
	enum Enum
	{
			NotAvailable = 1
		,	Ground		 = 2
		,	Water		 = 4
	};

	typedef unsigned int MaskType;

	static const MaskType ms_any = NotAvailable | Ground | Water;
};

/*---------------------------------------------------------------------------*/

struct Emplacement
{
	enum Enum
	{
			Ground		 = 1
		,	Water		 = 2
		,	Air			 = 3
	};
};

/*---------------------------------------------------------------------------*/

struct TerrainMapData
{
	TerrainMapData()
		:	m_terrainMapItem( TerrainMapItem::Ground )
		,	m_engagedWithGround( false )
		,	m_engagedWithAir( false )
	{}

	TerrainMapData(
			const TerrainMapItem::Enum _terrainMapItem
		,	const bool _engagedWithGround
		,	const bool _engagedWithAir
		)
		:	m_terrainMapItem( _terrainMapItem )
		,	m_engagedWithGround( _engagedWithGround )
		,	m_engagedWithAir( _engagedWithAir )
	{}

	TerrainMapItem::Enum m_terrainMapItem;
	bool m_engagedWithGround;
	bool m_engagedWithAir;
};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_TERRAIN_MAP_ITEMS_HPP__