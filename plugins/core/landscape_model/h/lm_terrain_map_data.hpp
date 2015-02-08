
#ifndef __LM_TERRAIN_MAP_ITEMS_HPP__
#define __LM_TERRAIN_MAP_ITEMS_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct TerrainMapItem
{
	enum Enum : qint32
	{
			NotAvailable	= 1
		,	Ground			= 2
		,	Water			= 4
	};

	typedef qint32 MaskType;

	static const MaskType ms_any = NotAvailable | Ground | Water;
};

/*---------------------------------------------------------------------------*/

struct Emplacement
{
	enum Enum : qint32
	{
			Ground		 = 1
		,	Air			 = 2
	};

	static QString toString( const Enum _emplacement )
	{
		switch ( _emplacement )
		{
		case Ground:
			return "Ground";
		case Air:
			return "Air";
		}

		return "Unknown";
	}
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

	void markAsEngaged( const Emplacement::Enum _emplacement, const bool _isEngaged )
	{
		switch( _emplacement )
		{
		case Emplacement::Air:
			m_engagedWithAir = _isEngaged;
			break;
		case Emplacement::Ground:
			m_engagedWithGround = _isEngaged;
			break;
		}
	}

	bool canBePlaced( const Emplacement::Enum _emplacement ) const
	{
		switch( _emplacement )
		{
		case Emplacement::Air:
			return m_engagedWithAir;
			break;
		case Emplacement::Ground:
			return m_engagedWithGround;
			break;
		}

		return false;
	}

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