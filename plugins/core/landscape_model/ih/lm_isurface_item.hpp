
#ifndef __LM_ISURFACE_ITEM_HPP__
#define __LM_ISURFACE_ITEM_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/h/lm_terrain_map_data.hpp"

#include "generators/gn_igenerator.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ISurfaceItem
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual Tools::Core::Generators::IGenerator::IdType getId() const = 0;

	virtual const TerrainMapItem::Enum getTerrainMapValue() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISURFACE_ITEM_HPP__
