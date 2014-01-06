
#ifndef __LM_SURFACE_ITEM_HPP__
#define __LM_SURFACE_ITEM_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

class SurfaceItem
	:	public Tools::Core::BaseWrapper< ISurfaceItem >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SurfaceItem(
			const ISurfaceItem::Id _id
		,	const TerrainMapItem::Enum _terrainMapItem );

	virtual ~SurfaceItem();

/*---------------------------------------------------------------------------*/

	/*virtual*/ ISurfaceItem::Id getId() const;

	/*virtual*/ const TerrainMapItem::Enum getTerrainMapValue() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ISurfaceItem::Id m_id;

	const TerrainMapItem::Enum m_terrainMapItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_SURFACE_ITEM_HPP__
