
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_move_items_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_iobject.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

#include "landscape_model/h/lm_events.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	boost::intrusive_ptr< IPathFinder > _pathFinder
	,	const QPoint& _to
	)
	:	BaseAction( _environment, _landscapeModel )
	,	m_pathFinder( _pathFinder )
	,	m_to( _to )
	,	m_movingData()
{
	boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

	if ( handle->getLandscape() )
	{
		ILandscape::ObjectsCollection selectedObjects;
		handle->getLandscape()->fetchSelectedObjects( selectedObjects );

		ILandscape::ObjectsCollectionIterator
				begin = selectedObjects.begin()
			,	end = selectedObjects.end();

		for ( ; begin != end; ++begin )
		{
			if ( ( *begin )->getType()->getMovingSpeed() != 0 )
			{
				MovingData movingData;
				m_pathFinder->findPath( movingData.m_path, *handle->getLandscape(), **begin, m_to );

				if ( !movingData.m_path.empty() )
				{
					m_movingData.insert( std::make_pair( ( *begin )->getUniqueId(), movingData ) );

					handle->getLandscape()->setEngagedWithGroungItem( ( *begin )->getPosition(), false );
					handle->getLandscape()->setEngagedWithGroungItem( movingData.m_path.front(), true );
				}
			}
		}
	}

} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::~MoveAction()
{
} // MoveAction::~MoveAction


/*---------------------------------------------------------------------------*/


void
MoveAction::processAction( const unsigned int _deltaTime )
{
	std::vector< Framework::Core::EventManager::Event > events;

	{
		boost::intrusive_ptr< ILandscapeHandle > handle( m_landscapeModel.getCurrentLandscape() );

		if ( handle->getLandscape() )
		{
			std::vector< IObject::IdType > objectsToDelete;

			MovingDataCollectionIterator
					begin = m_movingData.begin()
				,	end = m_movingData.end();

			for ( ; begin != end; ++begin )
			{
				boost::intrusive_ptr< IObject > object = handle->getLandscape()->getObject( begin->first );

				assert( begin->second.m_movingProgress < 1.0 );
				assert( !begin->second.m_path.empty() );

				float movingDelta = ( static_cast< float >( _deltaTime ) / object->getType()->getMovingSpeed() );
				begin->second.m_movingProgress += movingDelta;

				while ( begin->second.m_movingProgress >= 1.0 )
				{
					begin->second.m_movingProgress = begin->second.m_movingProgress - 1.0;

					QPoint position( QPoint( begin->second.m_path.front().x(), begin->second.m_path.front().y() ) );

					object->setPosition( position );

					begin->second.m_path.pop_front();

					if ( !begin->second.m_path.empty() )
					{
						if ( handle->getLandscape()->canObjectBePlaced( begin->second.m_path.front(), object->getType() ) )
						{
							handle->getLandscape()->setEngagedWithGroungItem( position, false );
							handle->getLandscape()->setEngagedWithGroungItem( begin->second.m_path.front(), true );
						}
						else
						{
							MovingData movingData;
							m_pathFinder->findPath( movingData.m_path, *handle->getLandscape(), *object, begin->second.m_path.back() );

							if ( !movingData.m_path.empty() )
							{
								begin->second = movingData;
								handle->getLandscape()->setEngagedWithGroungItem( position, false );
								handle->getLandscape()->setEngagedWithGroungItem( movingData.m_path.front(), true );
							}
							else
							{
								begin->second.m_path.clear();
							}
						}
					}

					if ( begin->second.m_path.empty() )
						break;
				}

				if ( begin->second.m_path.empty() )
				{
					object->setState( ObjectState::Standing );

					Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, object->getType()->getName() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, begin->first );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, object->getState() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, object->getDirection() );

					events.push_back( objectStateChangedEvent );

					objectsToDelete.push_back( begin->first );
					continue;
				}
				else
				{
					Direction::Enum currentDirection = object->getDirection();
					Direction::Enum nextDirection = Direction::Down;

					QPoint currentPosition( object->getPosition() );
					QPoint nextPosition = begin->second.m_path.front();

					if ( nextPosition.y() > currentPosition.y() )
						nextDirection = Direction::Down;
					else if ( nextPosition.y() < currentPosition.y() )
						nextDirection = Direction::Up;
					else if ( nextPosition.x() < currentPosition.x() )
						nextDirection = Direction::Right;
					else if ( nextPosition.x() > currentPosition.x() )
						nextDirection = Direction::Left;

					ObjectState::Enum currentState = object->getState();
					ObjectState::Enum nextState = ObjectState::Moving;

					if ( currentDirection != nextDirection || currentState != nextState )
					{
						object->setDirection( nextDirection );
						object->setState( nextState );

						Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
						objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, object->getType()->getName() );
						objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, begin->first );
						objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, object->getState() );
						objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, object->getDirection() );

						events.push_back( objectStateChangedEvent );
					}
				}

				Framework::Core::EventManager::Event objectMovedEvent( Events::ObjectMoved::ms_type );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_objectNameAttribute, object->getType()->getName() );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_objectIdAttribute, begin->first );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingFromAttribute, object->getPosition() );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingToAttribute, begin->second.m_path.front() );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingProgressAttribute, begin->second.m_movingProgress );

				events.push_back( objectMovedEvent );
			}

			std::vector< IObject::IdType >::const_iterator
					objectsToDeleteBegin = objectsToDelete.begin()
				,	objectsToDeleteEnd = objectsToDelete.end();

			for ( ; objectsToDeleteBegin != objectsToDeleteEnd; ++objectsToDeleteBegin )
				m_movingData.erase( *objectsToDeleteBegin );
		}
	}

	std::vector< Framework::Core::EventManager::Event >::const_iterator
			begin = events.begin()
		,	end = events.end();

	for ( ; begin != end; ++begin )
		m_environment.riseEvent( *begin );

} // MoveAction::processAction


/*---------------------------------------------------------------------------*/


void
MoveAction::unprocessAction( const unsigned int _deltaTime )
{
} // MoveAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
MoveAction::hasFinished() const
{
	return m_movingData.empty();

} // MoveAction::hasFinished


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
