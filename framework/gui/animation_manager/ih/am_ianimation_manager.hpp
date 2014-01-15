
#ifndef __AM_IANIMATION_MANAGER_HPP__
#define __AM_IANIMATION_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_ANIMATION_MANAGER = 0;

/*---------------------------------------------------------------------------*/

struct IAnimateObject;
struct AnimationInfo;

/*---------------------------------------------------------------------------*/

struct IAnimationManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void playAnimation( IAnimateObject& _animateObject, const QString& _animationName ) = 0;

	virtual void playAnimation(
			IAnimateObject& _animateObject
		,	const QString& _animationName
		,	const qint64 _delay ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void stopAnimation( IAnimateObject& _animateObject ) = 0;

	virtual void stopAllAnimations() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_IANIMATION_MANAGER_HPP__
