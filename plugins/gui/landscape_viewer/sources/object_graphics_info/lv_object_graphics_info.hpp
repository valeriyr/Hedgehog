
#ifndef __LV_OBJECT_GRAPHICS_INFO_HPP__
#define __LV_OBJECT_GRAPHICS_INFO_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/object_graphics_info/lv_iobject_graphics_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class ObjectGraphicsInfo
	:	public Tools::Core::BaseWrapper< IObjectGraphicsInfo >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ObjectGraphicsInfo(
			const QString& _name
		,	const QString& _atlasName
		,	const QRect _frameRect );

	virtual ~ObjectGraphicsInfo();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getName() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getAtlasName() const;

	/*virtual*/ const QRect& getFrameRect() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const QString m_name;

	const QString m_atlasName;

	const QRect m_frameRect;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_OBJECT_GRAPHICS_INFO_HPP__
