
#include "animation_manager/sources/ph/am_ph.hpp"

#include "animation_manager/sources/animations_cache/am_animations_cache.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

AnimationsCache::AnimationsCache()
	:	m_animationsInfoCollection()
{
} // AnimationsCache::AnimationsCache


/*---------------------------------------------------------------------------*/


AnimationsCache::~AnimationsCache()
{
	assert( m_animationsInfoCollection.empty() && "All animations should be unregistered at this moment!" );

} // AnimationsCache::~AnimationsCache


/*---------------------------------------------------------------------------*/


void
AnimationsCache::regAnimation( const AnimationInfo& _animationInfo )
{
	assert( m_animationsInfoCollection.find( _animationInfo.m_animationName ) == m_animationsInfoCollection.end() );
	m_animationsInfoCollection.insert( std::make_pair( _animationInfo.m_animationName, _animationInfo ) );

} // AnimationsCache::regAnimation


/*---------------------------------------------------------------------------*/


void
AnimationsCache::unregAnimation( const AnimationInfo& _animationInfo )
{
	m_animationsInfoCollection.erase( _animationInfo.m_animationName );

} // AnimationsCache::unregAnimation


/*---------------------------------------------------------------------------*/


const AnimationInfo&
AnimationsCache::getAnimation( const QString& _animationName ) const
{
	AnimationsInfoCollectionIterator iterator = m_animationsInfoCollection.find( _animationName );

	assert( iterator != m_animationsInfoCollection.end() );

	return iterator->second;

} // AnimationsCache::getAnimation


/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/