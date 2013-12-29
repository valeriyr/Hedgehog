
#ifndef __LV_IANIMATE_OBJECT_HPP__
#define __LV_IANIMATE_OBJECT_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IAnimateObject
{

/*---------------------------------------------------------------------------*/

	virtual const QString& getName() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void setSprite( const QPixmap& _sprite ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IANIMATE_OBJECT_HPP__
