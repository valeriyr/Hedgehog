
#ifndef __AM_ANIMATION_INFO_HPP__
#define __AM_ANIMATION_INFO_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

struct FrameInfo
{
	FrameInfo( const qint64 _period, const QRect& _frame, const bool _mirrored = false )
		:	m_period( _period )
		,	m_frame( _frame )
		,	m_mirrored( _mirrored )
	{}

	const qint64 m_period;
	const QRect m_frame;
	const bool m_mirrored;
};

/*---------------------------------------------------------------------------*/

struct AnimationInfo
{
	typedef
		std::vector< FrameInfo >
		FramesCollection;
	typedef
		FramesCollection::const_iterator
		FramesCollectionIterator;

	AnimationInfo(
			const QString& _animationName
		,	const QString& _atlasName
		,	const FramesCollection& _frames
		)
		:	m_animationName( _animationName )
		,	m_atlasName( _atlasName )
		,	m_frames( _frames )
	{}

	const QString m_animationName;
	const QString m_atlasName;

	const FramesCollection m_frames;
};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_ANIMATION_INFO_HPP__
