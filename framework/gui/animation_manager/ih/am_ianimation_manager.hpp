
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

/*---------------------------------------------------------------------------*/

struct IAnimationManager
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void startAnimation( const IAnimateObject& _animateObject ) = 0;

/*---------------------------------------------------------------------------*/

	virtual void stopAnimation( const IAnimateObject& _animateObject ) = 0;

	virtual void stopAllAnimations() = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_IANIMATION_MANAGER_HPP__
