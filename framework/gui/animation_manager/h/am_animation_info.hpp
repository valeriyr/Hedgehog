
#ifndef __LV_ANIMATION_INFO_HPP__
#define __LV_ANIMATION_INFO_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct AnimationInfo
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

#endif // __LV_ANIMATION_INFO_HPP__
