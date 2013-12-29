
#ifndef __AM_ANIMATION_MANAGER_HPP__
#define __AM_ANIMATION_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "animation_manager/ih/am_ianimation_manager.hpp"

#include "animation_manager/h/am_animation_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct IAnimationsCache;

/*---------------------------------------------------------------------------*/

class AnimationManager
	:	public Tools::Core::BaseWrapper< IAnimationManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AnimationManager( const IEnvironment& _environment, const IAnimationsCache& _animationCache );

	virtual ~AnimationManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void playAnimation( IAnimateObject& _animateObject, const QString& _animationName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void stopAnimation( const IAnimateObject& _animateObject );

	/*virtual*/ void stopAllAnimations();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct AnimationData
	{
		AnimationData( const AnimationInfo& _animationInfo )
			:	m_animationInfo( _animationInfo )
			,	m_frameIndex( 0 )
		{}

		const AnimationInfo& m_animationInfo;

		unsigned int m_frameIndex;
	};

/*---------------------------------------------------------------------------*/

	typedef
		std::map< IAnimateObject*, AnimationData >
		AnimationsDataCollection;
	typedef
		AnimationsDataCollection::iterator
		AnimationsDataCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const IAnimationsCache& m_animationCache;

	AnimationsDataCollection m_animationsDataCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_ANIMATION_MANAGER_HPP__
