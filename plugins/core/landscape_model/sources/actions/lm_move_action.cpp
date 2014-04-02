
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/ih/components/lm_ilocate_component.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	const QPoint& _movingTo
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_movingToPoint( _movingTo )
	,	m_movingToObject()
	,	m_lastTargetObjectLocation()
	,	m_preprocessedPath()
	,	m_distance( 0 )
{
} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	const QPoint& _movingTo
	,	IPathFinder::PointsCollection& _path
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_movingToPoint( _movingTo )
	,	m_movingToObject()
	,	m_lastTargetObjectLocation()
	,	m_preprocessedPath( _path )
	,	m_distance( 0 )
{
} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	boost::shared_ptr< Object > _movingTo
	,	const int _distance
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_movingToPoint()
	,	m_movingToObject( _movingTo )
	,	m_lastTargetObjectLocation( _movingTo->getComponent< ILocateComponent >( ComponentId::Locate )->getLocation() )
	,	m_preprocessedPath()
	,	m_distance( _distance )
{
} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	boost::shared_ptr< Object > _movingTo
	,	IPathFinder::PointsCollection& _path
	,	const int _distance
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_movingToPoint()
	,	m_movingToObject( _movingTo )
	,	m_lastTargetObjectLocation( _movingTo->getComponent< ILocateComponent >( ComponentId::Locate )->getLocation() )
	,	m_preprocessedPath( _path )
	,	m_distance( _distance )
{
} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::~MoveAction()
{
} // MoveAction::~MoveAction


/*---------------------------------------------------------------------------*/


bool
MoveAction::prepareToProcessingInternal()
{
	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );

	moveComponent->getMovingData().reset();

	if ( m_movingToObject )
	{
		if ( m_movingToObject->getState() == ObjectState::Dying )
		{
			moveToLocation( m_lastTargetObjectLocation );
			m_preprocessedPath.clear();
			return true;
		}
		else
		{
			m_lastTargetObjectLocation = m_movingToObject->getComponent< ILocateComponent >( ComponentId::Locate )->getLocation();
		}
	}

	moveComponent->getMovingData().m_movingTo = m_movingToPoint;
	moveComponent->getMovingData().m_movingToObject = m_movingToObject;

	if ( !m_preprocessedPath.empty() )
	{
		if ( m_landscapeModel.getLandscape()->canObjectBePlaced( moveComponent->getMovingData().m_path.front(), m_object.getName() ) )
		{
			moveComponent->getMovingData().m_path = m_preprocessedPath;

			m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, false );
			m_landscapeModel.getLandscape()->setEngaged( moveComponent->getMovingData().m_path.front(), locateComponent->getStaticData().m_emplacement, true );
		}

		m_preprocessedPath.clear();
	}

	return true;

} // MoveAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
MoveAction::cancelProcessingInternal()
{
	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );

	if ( m_object.getState() == ObjectState::Dying )
	{
		moveComponent->getMovingData().reset();
		return true;
	}

	if ( !moveComponent->getMovingData().m_path.empty() )
	{
		QPoint inProgressPoint( moveComponent->getMovingData().m_path.front() );

		moveComponent->getMovingData().m_path.clear();
		moveToLocation( inProgressPoint );
		moveComponent->getMovingData().m_path.push_back( inProgressPoint );

		return false;
	}
	else
	{
		moveComponent->getMovingData().reset();
	}

	return true;

} // MoveAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
MoveAction::processAction()
{
	// Common variables

	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );

	IMoveComponent::MovingData& movingData = moveComponent->getMovingData();

	bool unitChangeState = false;
	bool unitMoved = false;

	// Check if object is dying

	if ( m_object.getState() == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		// Check target object

		if ( m_movingToObject && m_movingToObject->getState() == ObjectState::Dying )
		{
			moveToLocation( m_lastTargetObjectLocation );
		}

		// Check if goal reached

		bool goalReached = false;

		if ( moveComponent->getMovingData().m_movingToObject )
		{
			boost::intrusive_ptr< ILocateComponent > targetLocateComponent
				= moveComponent->getMovingData().m_movingToObject->getComponent< ILocateComponent >( ComponentId::Locate );

			if ( Geometry::checkDistance( locateComponent->getLocation(), targetLocateComponent->getRect(), m_distance ) )
			{
				goalReached = true;
			}
		}
		else if ( Geometry::checkDistance( locateComponent->getLocation(), movingData.m_movingTo, m_distance ) )
		{
			goalReached = true;
		}

		if ( goalReached )
		{
			moveComponent->getMovingData().leaveOnlyFirstPoint();
		}

		// Check that our path is correct

		if ( moveComponent->getMovingData().m_movingToObject )
		{
			boost::intrusive_ptr< ILocateComponent > targetLocateComponent
				= moveComponent->getMovingData().m_movingToObject->getComponent< ILocateComponent >( ComponentId::Locate );

			if ( targetLocateComponent->getLocation() != m_lastTargetObjectLocation )
			{
				m_lastTargetObjectLocation = targetLocateComponent->getLocation();
				moveComponent->getMovingData().leaveOnlyFirstPoint();
			}
		}

		// Calculate new path

		if ( movingData.m_path.empty() )
		{
			IMoveComponent::MovingData newMovingData;
			newMovingData.m_movingTo = moveComponent->getMovingData().m_movingTo;
			newMovingData.m_movingToObject = moveComponent->getMovingData().m_movingToObject;

			if ( newMovingData.m_movingToObject )
			{
				JumpPointSearch::pathToObject( newMovingData.m_path, *m_landscapeModel.getLandscape(), m_object, *newMovingData.m_movingToObject, m_distance );
			}
			else
			{
				JumpPointSearch::pathToPoint( newMovingData.m_path, *m_landscapeModel.getLandscape(), m_object, newMovingData.m_movingTo );
			}

			if ( newMovingData.m_path.empty() )
			{
				m_isInProcessing = false;
			}
			else
			{
				movingData = newMovingData;

				m_landscapeModel.getLandscape()->setEngaged( locateComponent->getLocation(), locateComponent->getStaticData().m_emplacement, false );
				m_landscapeModel.getLandscape()->setEngaged( movingData.m_path.front(), locateComponent->getStaticData().m_emplacement, true );
			}
		}

		// Do moving

		if ( m_isInProcessing )
		{
			++movingData.m_movingProgress;

			bool pathWasBlocked = false;

			if ( movingData.m_movingProgress == moveComponent->getStaticData().m_movingSpeed )
			{
				movingData.m_movingProgress = 0;

				QPoint location( QPoint( movingData.m_path.front() ) );

				locateComponent->setLocation( location );

				movingData.m_path.pop_front();

				if ( !movingData.m_path.empty() )
				{
					if ( m_landscapeModel.getLandscape()->canObjectBePlaced( moveComponent->getMovingData().m_path.front(), m_object.getName() ) )
					{
						m_landscapeModel.getLandscape()->setEngaged( location, locateComponent->getStaticData().m_emplacement, false );
						m_landscapeModel.getLandscape()->setEngaged( moveComponent->getMovingData().m_path.front(), locateComponent->getStaticData().m_emplacement, true );
					}
					else
					{
						movingData.m_path.clear();
						pathWasBlocked = true;
					}
				}
			}

			if ( !movingData.m_path.empty() )
			{
				Direction::Enum currentDirection = locateComponent->getDirection();

				QPoint currentLocation( locateComponent->getLocation() );
				QPoint nextLocation = movingData.m_path.front();

				Direction::Enum nextDirection = Direction::getDirection( currentLocation, nextLocation );

				ObjectState::Enum currentState = m_object.getState();
				ObjectState::Enum nextState = ObjectState::Moving;

				if ( currentDirection != nextDirection || currentState != nextState )
				{
					locateComponent->setDirection( nextDirection );
					m_object.setState( nextState );

					unitChangeState = true;
				}
			}
			else if ( !pathWasBlocked )
			{
				m_isInProcessing = false;
			}

			unitMoved = true;
		}
	}

	// Finish moving

	if ( !m_isInProcessing && m_object.getState() == ObjectState::Moving )
	{
		movingData.reset();
		m_object.setState( ObjectState::Standing );
			
		unitChangeState = true;
	}

	// Send events

	if ( unitChangeState )
	{
		Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
		objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

		m_environment.riseEvent( objectStateChangedEvent );
	}

	if ( unitMoved )
	{
		Framework::Core::EventManager::Event objectMovedEvent( Events::ObjectMoved::ms_type );
		objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_objectNameAttribute, m_object.getName() );
		objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_objectIdAttribute, m_object.getUniqueId() );
		objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingFromAttribute, locateComponent->getLocation() );
		objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingToAttribute, movingData.m_path.empty() ? locateComponent->getLocation() : movingData.m_path.front() );
		objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingProgressAttribute, movingData.m_path.empty() ? moveComponent->getStaticData().m_movingSpeed : movingData.m_movingProgress );
		objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingSpeedAttribute, moveComponent->getStaticData().m_movingSpeed );

		m_environment.riseEvent( objectMovedEvent );
	}

} // MoveAction::processAction


/*---------------------------------------------------------------------------*/


const Actions::Enum
MoveAction::getType() const
{
	return Actions::Move;

} // MoveAction::getType


/*---------------------------------------------------------------------------*/


void
MoveAction::moveToLocation( const QPoint& _location )
{
	m_movingToPoint = _location;

	m_movingToObject.reset();
	m_lastTargetObjectLocation = QPoint();

	m_distance = 0;

	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );

	moveComponent->getMovingData().m_movingTo = m_movingToPoint;
	moveComponent->getMovingData().m_movingToObject.reset();

} // MoveAction::moveToLocation


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
