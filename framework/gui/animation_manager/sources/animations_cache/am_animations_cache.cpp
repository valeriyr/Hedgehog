
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
AnimationsCache::unregAnimation( const QString& _animationName )
{
	m_animationsInfoCollection.erase( _animationName );

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


bool
AnimationsCache::hasAnimation( const QString& _animationName ) const
{
	return m_animationsInfoCollection.find( _animationName ) != m_animationsInfoCollection.end();

} // AnimationsCache::hasAnimation


/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
