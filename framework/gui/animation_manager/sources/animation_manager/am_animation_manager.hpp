
#ifndef __AM_ANIMATION_MANAGER_HPP__
#define __AM_ANIMATION_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "animation_manager/ih/am_ianimation_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class AnimationManager
	:	public Tools::Core::BaseWrapper< IAnimationManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AnimationManager( const IEnvironment& _environment );

	virtual ~AnimationManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void startAnimation( const IAnimateObject& _animateObject );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void stopAnimation( const IAnimateObject& _animateObject );

	/*virtual*/ void stopAllAnimations();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_ANIMATION_MANAGER_HPP__
