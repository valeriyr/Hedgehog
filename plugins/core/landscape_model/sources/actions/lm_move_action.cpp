
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
	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );
	Tools::Core::Object::Ptr locateComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

	moveComponent->getMovingData().reset();

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

	moveComponent->getMovingData().m_movingTo = m_movingToPoint;
	moveComponent->getMovingData().m_movingToObject = m_movingToObject;

	if ( !m_preprocessedPath.empty() )
	{
		if ( m_landscapeModel.getLandscape()->canObjectBePlaced( moveComponent->getMovingData().m_path.front(), m_object.getMember< QString >( ObjectNameKey ) ) )
		{
			moveComponent->getMovingData().m_path = m_preprocessedPath;

			m_landscapeModel.getLandscape()->setEngaged(
					locateComponent->getMember< QPoint >( LocateComponent::Location )
				,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
				,	false );
			m_landscapeModel.getLandscape()->setEngaged(
					moveComponent->getMovingData().m_path.front()
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
	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
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

	Tools::Core::Object::Ptr locateComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );
	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );

	IMoveComponent::MovingData& movingData = moveComponent->getMovingData();

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

		if ( moveComponent->getMovingData().m_movingToObject )
		{
			Tools::Core::Object::Ptr targetLocateComponent
				= moveComponent->getMovingData().m_movingToObject->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

			if ( Geometry::checkDistance( locateComponent->getMember< QPoint >( LocateComponent::Location ), LocateComponent::getRect( *targetLocateComponent ), m_distance ) )
			{
				goalReached = true;
			}
		}
		else if ( Geometry::checkDistance( locateComponent->getMember< QPoint >( LocateComponent::Location ), movingData.m_movingTo, m_distance ) )
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
			Tools::Core::Object::Ptr targetLocateComponent
				= moveComponent->getMovingData().m_movingToObject->getMember< Tools::Core::Object::Ptr >( LocateComponent::Name );

			if ( targetLocateComponent->getMember< QPoint >( LocateComponent::Location ) != m_lastTargetObjectLocation )
			{
				m_lastTargetObjectLocation = targetLocateComponent->getMember< QPoint >( LocateComponent::Location );
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
				AStarSearch::pathToPoint( newMovingData.m_path, *m_landscapeModel.getLandscape(), m_object, newMovingData.m_movingTo );
			}

			if ( newMovingData.m_path.empty() )
			{
				m_isInProcessing = false;
			}
			else
			{
				movingData = newMovingData;

				m_landscapeModel.getLandscape()->setEngaged(
						locateComponent->getMember< QPoint >( LocateComponent::Location )
					,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
					,	false );
				m_landscapeModel.getLandscape()->setEngaged(
						movingData.m_path.front()
					,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
					,	true );
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

				locateComponent->getMember< QPoint >( LocateComponent::Location ) = location;

				movingData.m_path.pop_front();

				if ( !movingData.m_path.empty() )
				{
					if ( m_landscapeModel.getLandscape()->canObjectBePlaced( moveComponent->getMovingData().m_path.front(), m_object.getMember< QString >( ObjectNameKey ) ) )
					{
						m_landscapeModel.getLandscape()->setEngaged(
								location
							,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
							,	false );
						m_landscapeModel.getLandscape()->setEngaged(
								moveComponent->getMovingData().m_path.front()
							,	locateComponent->getMember< Emplacement::Enum >( StaticDataTools::generateName( LocateComponent::StaticData::Emplacement ) )
							,	true );
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
				Direction::Enum currentDirection = locateComponent->getMember< Direction::Enum >( LocateComponent::Direction );

				QPoint currentLocation( locateComponent->getMember< QPoint >( LocateComponent::Location ) );
				QPoint nextLocation = movingData.m_path.front();

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
		movingData.reset();
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
				.pushMember( Events::ObjectMoved::MovingToAttribute, movingData.m_path.empty() ? locateComponent->getMember< QPoint >( LocateComponent::Location ) : movingData.m_path.front() )
				.pushMember( Events::ObjectMoved::MovingProgressAttribute, movingData.m_path.empty() ? moveComponent->getStaticData().m_movingSpeed : movingData.m_movingProgress )
				.pushMember( Events::ObjectMoved::MovingSpeedAttribute, moveComponent->getStaticData().m_movingSpeed ) );
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
