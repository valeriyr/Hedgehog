
#ifndef __AM_ANIMATION_INFO_HPP__
#define __AM_ANIMATION_INFO_HPP__

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

struct FrameInfo
{
	FrameInfo( const int _period, const QRect& _frame, const bool _mirrored = false )
		:	m_period( _period )
		,	m_frame( _frame )
		,	m_mirrored( _mirrored )
	{}

	const int m_period;
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
		)
		:	m_animationName( _animationName )
		,	m_atlasName( _atlasName )
		,	m_frames()
	{}

	void addFrame( const FrameInfo& _frame )
	{
		m_frames.push_back( _frame );
	}

	const QString m_animationName;
	const QString m_atlasName;

	FramesCollection m_frames;
};

/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __AM_ANIMATION_INFO_HPP__
