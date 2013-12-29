
#include "animation_manager/sources/ph/am_ph.hpp"

#include "animation_manager/sources/animation_manager/am_animation_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

AnimationManager::AnimationManager( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // AnimationManager::AnimationManager


/*---------------------------------------------------------------------------*/


AnimationManager::~AnimationManager()
{
} // AnimationManager::~AnimationManager


/*---------------------------------------------------------------------------*/


void
AnimationManager::regAnimation( const AnimationInfo& _animationInfo )
{
} // AnimationManager::regAnimation


/*---------------------------------------------------------------------------*/


void
AnimationManager::unregAnimation( const AnimationInfo& _animationInfo )
{
} // AnimationManager::unregAnimation


/*---------------------------------------------------------------------------*/


void
AnimationManager::startAnimation( IAnimateObject& _animateObject, const QString& _animationName )
{
} // AnimationManager::startAnimation


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
