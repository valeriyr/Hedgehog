
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"
#include "landscape_model/sources/path_finders/lm_jump_point_search.hpp"
#include "landscape_model/sources/path_finders/lm_astar_search.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/utils/lm_geometry.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	GameObject& _object
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
	,	GameObject& _object
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
	,	GameObject& _object
	,	boost::shared_ptr< GameObject > _movingTo
	,	const int _distance
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_movingToPoint()
	,	m_movingToObject( _movingTo )
	,	m_lastTargetObjectLocation( _movingTo->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name )->getMember< QPoint >( LocateComponent::Location ) )
	,	m_preprocessedPath()
	,	m_distance( _distance )
{
} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	GameObject& _object
	,	boost::shared_ptr< GameObject > _movingTo
	,	IPathFinder::PointsCollection& _path
	,	const int _distance
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_movingToPoint()
	,	m_movingToObject( _movingTo )
	,	m_lastTargetObjectLocation( _movingTo->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name )->getMember< QPoint >( LocateComponent::Location ) )
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
	Tools::Core::Object::Ptr moveComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( MoveComponent::Name );
	Tools::Core::Object::Ptr locateComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

	MoveComponent::clearData( *moveComponent );

	if ( m_movingToObject )
	{
		if ( m_movingToObject->getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
		{
			moveToLocation( m_lastTargetObjectLocation );
			m_preprocessedPath.clear();
			return true;
		}
		else
		{
			m_lastTargetObjectLocation
				= m_movingToObject->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name )
					->getMember< QPoint >( LocateComponent::Location );
		}
	}

	moveComponent->getMember< QPoint >( MoveComponent::MovingTo ) = m_movingToPoint;
	moveComponent->getMember< boost::shared_ptr< GameObject > >( MoveComponent::MovingToObject ) = m_movingToObject;

	if ( !m_preprocessedPath.empty() )
	{
		if ( m_landscapeModel.getLandscape()->canObjectBePlaced( moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).front(), m_object.getMember< QString >( ObjectNameKey ) ) )
		{
			moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ) = m_preprocessedPath;

			m_landscapeModel.getLandscape()->setEngaged(
					locateComponent->getMember< QPoint >( LocateComponent::Location )
				,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
				,	false );
			m_landscapeModel.getLandscape()->setEngaged(
					moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).front()
				,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
				,	true );
		}

		m_preprocessedPath.clear();
	}

	return true;

} // MoveAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
MoveAction::cancelProcessingInternal()
{
	Tools::Core::Object::Ptr moveComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( MoveComponent::Name );

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
	{
		MoveComponent::clearData( *moveComponent );
		return true;
	}

	if ( !moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).empty() )
	{
		QPoint inProgressPoint( moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).front() );

		moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).clear();
		moveToLocation( inProgressPoint );
		moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).push_back( inProgressPoint );

		return false;
	}
	else
	{
		MoveComponent::clearData( *moveComponent );
	}

	return true;

} // MoveAction::cancelProcessingInternal


/*---------------------------------------------------------------------------*/


void
MoveAction::processAction()
{
	// Common variables

	Tools::Core::Object::Ptr locateComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );
	Tools::Core::Object::Ptr moveComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( MoveComponent::Name );

	bool unitChangeState = false;
	bool unitMoved = false;

	// Check if object is dying

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		// Check target object

		if ( m_movingToObject && m_movingToObject->getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
		{
			moveToLocation( m_lastTargetObjectLocation );
		}

		// Check if goal reached

		bool goalReached = false;

		if ( moveComponent->getMember< boost::shared_ptr< GameObject > >( MoveComponent::MovingToObject ) )
		{
			Tools::Core::Object::Ptr targetLocateComponent
				= moveComponent->getMember< boost::shared_ptr< GameObject > >( MoveComponent::MovingToObject )->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

			if ( Geometry::checkDistance( locateComponent->getMember< QPoint >( LocateComponent::Location ), LocateComponent::getRect( *targetLocateComponent ), m_distance ) )
			{
				goalReached = true;
			}
		}
		else if ( Geometry::checkDistance( locateComponent->getMember< QPoint >( LocateComponent::Location ), moveComponent->getMember< QPoint >( MoveComponent::MovingTo ), m_distance ) )
		{
			goalReached = true;
		}

		if ( goalReached )
		{
			MoveComponent::leaveOnlyFirstPoint( *moveComponent );
		}

		// Check that our path is correct

		if ( moveComponent->getMember< boost::shared_ptr< GameObject > >( MoveComponent::MovingToObject ) )
		{
			Tools::Core::Object::Ptr targetLocateComponent
				= moveComponent->getMember< boost::shared_ptr< GameObject > >( MoveComponent::MovingToObject )->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

			if ( targetLocateComponent->getMember< QPoint >( LocateComponent::Location ) != m_lastTargetObjectLocation )
			{
				m_lastTargetObjectLocation = targetLocateComponent->getMember< QPoint >( LocateComponent::Location );
				MoveComponent::leaveOnlyFirstPoint( *moveComponent );
			}
		}

		// Calculate new path

		if ( moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).empty() )
		{
			QPoint newMovingTo = moveComponent->getMember< QPoint >( MoveComponent::MovingTo );
			boost::shared_ptr< GameObject > newMovingToObject = moveComponent->getMember< boost::shared_ptr< GameObject > >( MoveComponent::MovingToObject );
			IPathFinder::PointsCollection newPath;

			if ( newMovingToObject )
			{
				JumpPointSearch::pathToObject( newPath, *m_landscapeModel.getLandscape(), m_object, *newMovingToObject, m_distance );
			}
			else
			{
				AStarSearch::pathToPoint( newPath, *m_landscapeModel.getLandscape(), m_object, newMovingTo );
			}

			if ( newPath.empty() )
			{
				m_isInProcessing = false;
			}
			else
			{
				moveComponent->getMember< QPoint >( MoveComponent::MovingTo ) = newMovingTo;
				moveComponent->getMember< boost::shared_ptr< GameObject > >( MoveComponent::MovingToObject ) = newMovingToObject;
				moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ) = newPath;
				moveComponent->getMember< TickType >( MoveComponent::MovingProgress ) = 0;

				m_landscapeModel.getLandscape()->setEngaged(
						locateComponent->getMember< QPoint >( LocateComponent::Location )
					,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
					,	false );
				m_landscapeModel.getLandscape()->setEngaged(
						newPath.front()
					,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
					,	true );
			}
		}

		// Do moving

		if ( m_isInProcessing )
		{
			++moveComponent->getMember< TickType >( MoveComponent::MovingProgress );

			bool pathWasBlocked = false;

			if (	moveComponent->getMember< TickType >( MoveComponent::MovingProgress )
				==	moveComponent->getMember< TickType >( StaticDataTools::generateName( MoveComponent::StaticData::MovingSpeed ) ) )
			{
				moveComponent->getMember< TickType >( MoveComponent::MovingProgress ) = 0;

				QPoint location( QPoint( moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).front() ) );

				locateComponent->getMember< QPoint >( LocateComponent::Location ) = location;

				moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).pop_front();

				if ( !moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).empty() )
				{
					if ( m_landscapeModel.getLandscape()->canObjectBePlaced( moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).front(), m_object.getMember< QString >( ObjectNameKey ) ) )
					{
						m_landscapeModel.getLandscape()->setEngaged(
								location
							,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
							,	false );
						m_landscapeModel.getLandscape()->setEngaged(
								moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).front()
							,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
							,	true );
					}
					else
					{
						moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).clear();
						pathWasBlocked = true;
					}
				}
			}

			if ( !moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).empty() )
			{
				Direction::Enum currentDirection = locateComponent->getMember< Direction::Enum >( LocateComponent::Direction );

				QPoint currentLocation( locateComponent->getMember< QPoint >( LocateComponent::Location ) );
				QPoint nextLocation = moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).front();

				Direction::Enum nextDirection = Direction::getDirection( currentLocation, nextLocation );

				ObjectState::Enum currentState = m_object.getMember< ObjectState::Enum >( ObjectStateKey );
				ObjectState::Enum nextState = ObjectState::Moving;

				if ( currentDirection != nextDirection || currentState != nextState )
				{
					locateComponent->getMember< Direction::Enum >( LocateComponent::Direction ) = nextDirection;
					m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = nextState;

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

	if ( !m_isInProcessing && m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Moving )
	{
		MoveComponent::clearData( *moveComponent );
		m_object.getMember< ObjectState::Enum >( ObjectStateKey ) = ObjectState::Standing;
			
		unitChangeState = true;
	}

	// Send events

	if ( unitChangeState )
	{
		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::ObjectStateChanged::Type )
				.pushMember( Events::ObjectStateChanged::ObjectNameAttribute, m_object.getMember< QString >( ObjectNameKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectState, m_object.getMember< ObjectState::Enum >( ObjectStateKey ) )
				.pushMember( Events::ObjectStateChanged::ObjectDirection, locateComponent->getMember< Direction::Enum >( LocateComponent::Direction ) ) );
	}

	if ( unitMoved )
	{
		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::ObjectMoved::Type )
				.pushMember( Events::ObjectMoved::ObjectNameAttribute, m_object.getMember< QString >( ObjectNameKey ) )
				.pushMember( Events::ObjectMoved::ObjectIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) )
				.pushMember( Events::ObjectMoved::MovingFromAttribute, locateComponent->getMember< QPoint >( LocateComponent::Location ) )
				.pushMember(	Events::ObjectMoved::MovingToAttribute
							,		moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).empty()
								?	locateComponent->getMember< QPoint >( LocateComponent::Location )
								:	moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).front() )
				.pushMember(	Events::ObjectMoved::MovingProgressAttribute
							,		moveComponent->getMember< IPathFinder::PointsCollection >( MoveComponent::Path ).empty()
								?	moveComponent->getMember< TickType >( StaticDataTools::generateName( MoveComponent::StaticData::MovingSpeed ) )
								:	moveComponent->getMember< TickType >( MoveComponent::MovingProgress ) )
				.pushMember( Events::ObjectMoved::MovingSpeedAttribute, moveComponent->getMember< TickType >( StaticDataTools::generateName( MoveComponent::StaticData::MovingSpeed ) ) ) );
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

	Tools::Core::Object::Ptr moveComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( MoveComponent::Name );

	moveComponent->getMember< QPoint >( MoveComponent::MovingTo ) = m_movingToPoint;
	moveComponent->getMember< boost::shared_ptr< GameObject > >( MoveComponent::MovingToObject ).reset();

} // MoveAction::moveToLocation


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
