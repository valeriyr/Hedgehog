
#ifndef __LM_ISURFACE_ITEM_HPP__
#define __LM_ISURFACE_ITEM_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/h/lm_terrain_map_data.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItem
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef unsigned int Id;

	static const Id ms_invalidId = UINT_MAX;

/*---------------------------------------------------------------------------*/

	virtual Id getId() const = 0;

	virtual const TerrainMapItem::Enum getTerrainMapValue() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISURFACE_ITEM_HPP__
