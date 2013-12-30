
#ifndef __AM_ANIMATIONS_CACHE_HPP__
#define __AM_ANIMATIONS_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "animation_manager/ih/am_ianimations_cache.hpp"

#include "animation_manager/h/am_animation_info.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

class AnimationsCache
	:	public Tools::Core::BaseWrapper< IAnimationsCache >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	AnimationsCache();

	virtual ~AnimationsCache();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regAnimation( const AnimationInfo& _animationInfo );

	/*virtual*/ void unregAnimation( const QString& _animationName );

/*---------------------------------------------------------------------------*/

	/*virtual*/ const AnimationInfo& getAnimation( const QString& _animationName ) const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map< QString, AnimationInfo >
		AnimationsInfoCollection;
	typedef
		AnimationsInfoCollection::const_iterator
		AnimationsInfoCollectionIterator;

/*---------------------------------------------------------------------------*/

	AnimationsInfoCollection m_animationsInfoCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_ANIMATION_MANAGER_HPP__
