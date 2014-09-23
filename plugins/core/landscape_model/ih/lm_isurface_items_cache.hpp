
#ifndef __LM_ISURFACE_ITEMS_CACHE_HPP__
#define __LM_ISURFACE_ITEMS_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_SURFACE_ITEMS_CACHE = 1;

/*---------------------------------------------------------------------------*/

struct ISurfaceItemsCache
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void regSurfaceItem(
			const Tools::Core::Generators::IGenerator::IdType _id
		,	const TerrainMapItem::Enum _terrainMapItem ) = 0;

	virtual boost::intrusive_ptr< ISurfaceItem >
		getSurfaceItem( const Tools::Core::Generators::IGenerator::IdType _id ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ISurfaceItem > getDefaultSurfaceItem() const = 0;

	virtual void setDefaultSurfaceItem( const Tools::Core::Generators::IGenerator::IdType _id ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ISURFACE_ITEMS_CACHE_HPP__
