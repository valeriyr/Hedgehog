
#include "animation_manager/sources/ph/am_ph.hpp"

#include "animation_manager/sources/animation_manager/am_animation_manager.hpp"

#include "animation_manager/sources/environment/am_ienvironment.hpp"

#include "animation_manager/ih/am_ianimations_cache.hpp"
#include "animation_manager/ih/am_ianimate_object.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"

#include "animation_manager/sources/resources/am_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace AnimationManager {

/*---------------------------------------------------------------------------*/

AnimationManager::AnimationManager( const IEnvironment& _environment, const IAnimationsCache& _animationCache )
	:	m_environment( _environment )
	,	m_animationCache( _animationCache )
	,	m_animationsDataCollection()
	//,	m_mutex()
{
	m_animationsProcessingTaskHandle
		= m_environment.pushPeriodicalTask(
				Core::MultithreadingManager::Resources::MainThreadName
			,	boost::bind( &AnimationManager::animationsProcessingTask, this ) );

} // AnimationManager::AnimationManager


/*---------------------------------------------------------------------------*/


AnimationManager::~AnimationManager()
{
	m_environment.removeTask( m_animationsProcessingTaskHandle );

	assert( m_animationsDataCollection.empty() && "All animations should be stopped at this moment!" );

} // AnimationManager::~AnimationManager


/*---------------------------------------------------------------------------*/


void
AnimationManager::playAnimation( IAnimateObject& _animateObject, const QString& _animationName )
{
	playAnimation( _animateObject, _animationName, 0, false );

} // AnimationManager::playAnimation


/*---------------------------------------------------------------------------*/


void
AnimationManager::playAnimation(
		IAnimateObject& _animateObject
	,	const QString& _animationName
	,	const qint64 _delay )
{
	playAnimation( _animateObject, _animationName, _delay, false );

} // AnimationManager::playAnimation


/*---------------------------------------------------------------------------*/


void
AnimationManager::playAnimationOnce( IAnimateObject& _animateObject, const QString& _animationName )
{
	playAnimation( _animateObject, _animationName, 0, true );

} // AnimationManager::playAnimationOnce


/*---------------------------------------------------------------------------*/


void
AnimationManager::stopAnimation( IAnimateObject& _animateObject )
{
	//QMutexLocker locker( &m_mutex );

	m_animationsDataCollection.erase( &_animateObject );

} // AnimationManager::stopAnimation


/*---------------------------------------------------------------------------*/


void
AnimationManager::stopAllAnimations()
{
	//QMutexLocker locker( &m_mutex );

	m_animationsDataCollection.clear();

} // AnimationManager::stopAllAnimations


/*---------------------------------------------------------------------------*/


void
AnimationManager::animationsProcessingTask()
{
	//QMutexLocker locker( &m_mutex );

	const qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

	std::vector< IAnimateObject* > objectToDelete;

	AnimationsDataCollectionIterator
			begin = m_animationsDataCollection.begin()
		,	end = m_animationsDataCollection.end();

	for ( ; begin != end; ++begin )
	{
		const AnimationInfo& animationInfo = begin->second->m_animationInfo;

		if (	( currentTime - begin->second->m_lastFrameSwitchTime
			>=	animationInfo.m_frames[ begin->second->m_frameIndex ].m_period )
			&&	( currentTime - begin->second->m_finishTime >= begin->second->m_delay - animationInfo.animationDuration() ) )
		{
			if ( begin->second->m_frameIndex >= animationInfo.m_frames.size() - 1 )
			{
				if ( begin->second->m_onceAnimation )
				{
					objectToDelete.push_back( begin->first );
					continue;
				}

				begin->second->m_frameIndex = 0;
				begin->second->m_finishTime = currentTime;
			}
			else
				++begin->second->m_frameIndex;

			begin->first->setSprite(
				m_environment.getPixmap(
						animationInfo.m_atlasName
					,	ImagesManager::IImagesManager::TransformationData(
								animationInfo.m_frames[ begin->second->m_frameIndex ].m_frame
							,	false
							,	animationInfo.m_frames[ begin->second->m_frameIndex ].m_mirrored ) ) );

			begin->second->m_lastFrameSwitchTime = currentTime;
		}
	}

	std::vector< IAnimateObject* >::const_iterator
			toDeleteBegin = objectToDelete.begin()
		,	toDeleteEnd = objectToDelete.end();

	for ( ; toDeleteBegin != toDeleteEnd; ++toDeleteBegin )
		m_animationsDataCollection.erase( *toDeleteBegin );

	qint64 time = QDateTime::currentDateTime().toMSecsSinceEpoch() - currentTime;

	if ( time > ( static_cast< float >( Resources::TimeLimit ) * 0.6f )  )
	{
		m_environment.printMessage(
				Tools::Core::IMessenger::MessegeLevel::Warning
			,	QString( Resources::TimeLimitWarning ).arg( time ).arg( Resources::TimeLimit )  );
	}

} // AnimationManager::animationsProcessingTask


/*---------------------------------------------------------------------------*/


void
AnimationManager::playAnimation(
		IAnimateObject& _animateObject
	,	const QString& _animationName
	,	const qint64 _delay
	,	const bool _onceAnimation )
{
	//QMutexLocker locker( &m_mutex );

	const AnimationInfo& animationInfo = m_animationCache.getAnimation( _animationName );

	boost::shared_ptr< AnimationData > animationData( new AnimationData( animationInfo ) );
	animationData->m_lastFrameSwitchTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
	animationData->m_delay = _delay;
	animationData->m_onceAnimation = _onceAnimation;

	AnimationsDataCollectionIterator iterator = m_animationsDataCollection.find( &_animateObject );

	if ( iterator == m_animationsDataCollection.end() )
	{
		m_animationsDataCollection.insert( std::make_pair( &_animateObject, animationData) );
	}
	else
	{
		iterator->second = animationData;
	}

	_animateObject.setSprite(
		m_environment.getPixmap(
				animationInfo.m_atlasName
			,	ImagesManager::IImagesManager::TransformationData(
						animationInfo.m_frames[ animationData->m_frameIndex ].m_frame
					,	false
					,	animationInfo.m_frames[ animationData->m_frameIndex ].m_mirrored ) ) );

} // AnimationManager::playAnimation


/*---------------------------------------------------------------------------*/

} // namespace AnimationManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
