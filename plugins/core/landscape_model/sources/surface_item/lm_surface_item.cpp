
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/surface_item/lm_surface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


SurfaceItem::SurfaceItem(
		const ISurfaceItem::Id _id
	,	const TerrainMapItem::Enum _terrainMapItem
	)
	:	m_id( _id )
	,	m_terrainMapItem( _terrainMapItem )
{
} // SurfaceItem::SurfaceItem


/*---------------------------------------------------------------------------*/


SurfaceItem::~SurfaceItem()
{
} // SurfaceItem::~SurfaceItem


/*---------------------------------------------------------------------------*/


ISurfaceItem::Id
SurfaceItem::getId() const
{
	return m_id;

} // SurfaceItem::getId


/*---------------------------------------------------------------------------*/


const TerrainMapItem::Enum
SurfaceItem::getTerrainMapValue() const
{
	return m_terrainMapItem;

} // SurfaceItem::getTerrainMapValue


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
