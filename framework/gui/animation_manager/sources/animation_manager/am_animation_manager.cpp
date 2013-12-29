
#include "animation_manager/sources/ph/am_ph.hpp"

#include "animation_manager/sources/animation_manager/am_animation_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

AnimationManager::AnimationManager( const IEnvironment& _environment, const IAnimationsCache& _animationCache )
	:	m_environment( _environment )
	,	m_animationCache( _animationCache )
	,	m_animationsDataCollection()
{
} // AnimationManager::AnimationManager


/*---------------------------------------------------------------------------*/


AnimationManager::~AnimationManager()
{
	assert( m_animationsDataCollection.empty() && "All animations should be stopped at this moment!" );

} // AnimationManager::~AnimationManager


/*---------------------------------------------------------------------------*/


void
AnimationManager::playAnimation( IAnimateObject& _animateObject, const QString& _animationName )
{
} // AnimationManager::playAnimation


/*---------------------------------------------------------------------------*/


void
AnimationManager::stopAnimation( const IAnimateObject& _animateObject )
{
} // AnimationManager::stopAnimation


/*---------------------------------------------------------------------------*/


void
AnimationManager::stopAllAnimations()
{
} // AnimationManager::stopAllAnimations


/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
