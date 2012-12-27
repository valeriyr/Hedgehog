
#ifndef __LM_ILANDSCAPE_HPP__
#define __LM_ILANDSCAPE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "landscape_model/ih/lm_ilandscape_object.hpp"

#include "landscape_model/h/lm_surface_items.hpp"
#include "landscape_model/h/lm_terrain_map_items.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/

struct ILandscape
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	typedef
		boost::intrusive_ptr< ILandscape >
		Ptr;

/*---------------------------------------------------------------------------*/

	virtual unsigned int getWidth() const = 0;

	virtual unsigned int getHeight() const = 0;

/*---------------------------------------------------------------------------*/

	virtual ILandscapeObject::Ptr
		getLadscapeObject( const unsigned int _width, const unsigned int _height ) const = 0;

	virtual SurfaceItems::Enum
		getSurfaceItem( const unsigned int _width, const unsigned int _height ) const = 0;

	virtual TerrainMapItems::Enum
		getTerrainMapItem( const unsigned int _width, const unsigned int _height ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LM_ILANDSCAPE_HPP__
