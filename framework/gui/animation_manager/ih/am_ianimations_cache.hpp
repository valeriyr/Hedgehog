
#ifndef __AM_IANIMATIONS_CACHE_HPP__
#define __AM_IANIMATIONS_CACHE_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

	const quint32 IID_ANIMATIONS_CACHE = 1;

/*---------------------------------------------------------------------------*/

struct AnimationInfo;

/*---------------------------------------------------------------------------*/

struct IAnimationsCache
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void regAnimation( const AnimationInfo& _animationInfo ) = 0;

	virtual void unregAnimation( const QString& _animationName ) = 0;

/*---------------------------------------------------------------------------*/

	virtual const AnimationInfo& getAnimation( const QString& _animationName ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual bool hasAnimation( const QString& _animationName ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_IANIMATIONS_CACHE_HPP__
