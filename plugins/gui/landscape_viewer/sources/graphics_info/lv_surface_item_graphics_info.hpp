
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
			const Tools::Core::Generators::IGenerator::IdType& _id
		,	const QString& _atlasName
		,	const QRect _frameRect );

	virtual ~SurfaceItemGraphicsInfo();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Tools::Core::Generators::IGenerator::IdType getId() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getAtlasName() const;

	/*virtual*/ const QRect& getFrameRect() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const Tools::Core::Generators::IGenerator::IdType m_id;

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
