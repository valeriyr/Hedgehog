
#ifndef __LV_ISURFACE_ITEM_GRAPHICS_INFO_HPP__
#define __LV_ISURFACE_ITEM_GRAPHICS_INFO_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct ISurfaceItemGraphicsInfo
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual const Tools::Core::Generators::IGenerator::IdType getId() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QString& getAtlasName() const = 0;

	virtual const QRect& getFrameRect() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ISURFACE_ITEM_GRAPHICS_INFO_HPP__
