
#ifndef __AM_IANIMATE_OBJECT_HPP__
#define __AM_IANIMATE_OBJECT_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

struct IAnimateObject
{

/*---------------------------------------------------------------------------*/

	virtual void setSprite( const QPixmap& _sprite ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_IANIMATE_OBJECT_HPP__
