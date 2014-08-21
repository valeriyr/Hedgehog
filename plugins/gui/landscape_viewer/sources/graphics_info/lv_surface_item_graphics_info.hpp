
#ifndef __LV_SURFACE_ITEM_GRAPHICS_INFO_HPP__
#define __LV_SURFACE_ITEM_GRAPHICS_INFO_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/graphics_info/lv_isurface_item_graphics_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class SurfaceItemGraphicsInfo
	:	public Tools::Core::BaseWrapper< ISurfaceItemGraphicsInfo >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SurfaceItemGraphicsInfo(
			const Core::LandscapeModel::ISurfaceItem::Id& _id
		,	const QString& _atlasName
		,	const QRect _frameRect );

	virtual ~SurfaceItemGraphicsInfo();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Core::LandscapeModel::ISurfaceItem::Id getId() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getAtlasName() const;

	/*virtual*/ const QRect& getFrameRect() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const Core::LandscapeModel::ISurfaceItem::Id m_id;

	const QString m_atlasName;

	const QRect m_frameRect;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_SURFACE_ITEM_GRAPHICS_INFO_HPP__
