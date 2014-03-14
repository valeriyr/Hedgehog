
#ifndef __AM_ANIMATION_MANAGER_HPP__
#define __AM_ANIMATION_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "animation_manager/ih/am_ianimation_manager.hpp"

#include "animation_manager/h/am_animation_info.hpp"

#include "multithreading_manager/h/mm_task_handle.hpp"

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

	/*virtual*/ void playAnimation(
			IAnimateObject& _animateObject
		,	const QString& _animationName
		,	const qint64 _delay );

	/*virtual*/ void playAnimationOnce( IAnimateObject& _animateObject, const QString& _animationName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void stopAnimation( IAnimateObject& _animateObject );

	/*virtual*/ void stopAllAnimations();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void animationsProcessingTask();

	void playAnimation(
			IAnimateObject& _animateObject
		,	const QString& _animationName
		,	const qint64 _delay
		,	const bool _onceAnimation );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct AnimationData
	{
		AnimationData( const AnimationInfo& _animationInfo )
			:	m_animationInfo( _animationInfo )
			,	m_frameIndex( 0 )
			,	m_lastFrameSwitchTime( 0 )
			,	m_finishTime( 0 )
			,	m_delay( 0 )
			,	m_onceAnimation( false )
		{}

		const AnimationInfo& m_animationInfo;

		unsigned int m_frameIndex;

		qint64 m_lastFrameSwitchTime;

		qint64 m_finishTime;

		qint64 m_delay;

		bool m_onceAnimation;
	};

/*---------------------------------------------------------------------------*/

	typedef
		std::map< IAnimateObject*, boost::shared_ptr< AnimationData > >
		AnimationsDataCollection;
	typedef
		AnimationsDataCollection::iterator
		AnimationsDataCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	const IAnimationsCache& m_animationCache;

	AnimationsDataCollection m_animationsDataCollection;

	Core::MultithreadingManager::TaskHandle m_animationsProcessingTaskHandle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_ANIMATION_MANAGER_HPP__
