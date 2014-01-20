
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


MoveAction::MoveAction(
		const IEnvironment& _environment
	,	Object& _object
	,	ILandscape& _landscape
	,	boost::intrusive_ptr< IPathFinder > _pathFinder
	,	const int _distance
	)
	:	BaseAction( _environment, _object )
	,	m_landscape( _landscape )
	,	m_pathFinder( _pathFinder )
	,	m_movingFinished( false )
	,	m_distance( _distance )
{
} // MoveAction::MoveAction


/*---------------------------------------------------------------------------*/


MoveAction::~MoveAction()
{
} // MoveAction::~MoveAction


/*---------------------------------------------------------------------------*/


void
MoveAction::processAction( const unsigned int _deltaTime )
{
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );

	IMoveComponent::MovingData& movingData = moveComponent->getMovingData();

	bool isInFinishPoint = false;

	if ( moveComponent->getMovingData().m_movingToObject )
	{
		if ( movingData.m_path.empty() )
		{
			boost::intrusive_ptr< ILocateComponent > targetLocateComponent
				= moveComponent->getMovingData().m_movingToObject->getComponent< ILocateComponent >( ComponentId::Locate );

			if ( isOnRightDistanceToObject( targetLocateComponent->getRect(), locateComponent->getLocation() ) )
			{
				isInFinishPoint = true;
			}
		}
	}
	else if ( locateComponent->getLocation() == moveComponent->getMovingData().m_movingTo )
	{
		isInFinishPoint = true;
	}

	if ( isInFinishPoint )
	{
		movingData.clear();
		m_movingFinished = true;
	}
	else
	{
		if ( movingData.m_path.empty() )
		{
			IMoveComponent::MovingData newMovingData;
			newMovingData.m_movingTo = moveComponent->getMovingData().m_movingTo;
			newMovingData.m_movingToObject = moveComponent->getMovingData().m_movingToObject;

			IPathFinder::PointsCollection targetPoints;
			fillPossibleTargetPoints( targetPoints, moveComponent->getMovingData() );

			m_pathFinder->findPath( newMovingData.m_path, m_landscape, *locateComponent, targetPoints );

			if ( newMovingData.m_path.empty() )
			{
				movingData.clear();
				m_movingFinished = true;
			}
			else
			{
				movingData = newMovingData;

				m_landscape.setEngagedWithGroungItem( locateComponent->getLocation(), false );
				m_landscape.setEngagedWithGroungItem( movingData.m_path.front(), true );
			}
		}

		bool unitChangeSatate = false;

		if ( !m_movingFinished )
		{
			float movingDelta = ( static_cast< float >( _deltaTime ) / moveComponent->getStaticData().m_movingSpeed );
			movingData.m_movingProgress += movingDelta;

			while ( movingData.m_movingProgress >= 1.0 )
			{
				movingData.m_movingProgress = movingData.m_movingProgress - 1.0;

				QPoint location( QPoint( movingData.m_path.front() ) );

				locateComponent->setLocation( location );

				movingData.m_path.pop_front();

				if ( !movingData.m_path.empty() )
				{
					if ( m_landscape.canObjectBePlaced( moveComponent->getMovingData().m_path.front(), locateComponent->getStaticData() ) )
					{
						m_landscape.setEngagedWithGroungItem( location, false );
						m_landscape.setEngagedWithGroungItem( moveComponent->getMovingData().m_path.front(), true );
					}
					else
					{
						IMoveComponent::MovingData newMovingData;
						newMovingData.m_movingTo = moveComponent->getMovingData().m_movingTo;
						newMovingData.m_movingToObject = moveComponent->getMovingData().m_movingToObject;

						IPathFinder::PointsCollection targetPoints;
						fillPossibleTargetPoints( targetPoints, moveComponent->getMovingData() );

						m_pathFinder->findPath( newMovingData.m_path, m_landscape, *locateComponent, targetPoints );
						
						if ( newMovingData.m_path.empty() )
						{
							movingData.clear();
							m_movingFinished = true;
							break;
						}
						else
						{
							movingData = newMovingData;

							m_landscape.setEngagedWithGroungItem( location, false );
							m_landscape.setEngagedWithGroungItem( movingData.m_path.front(), true );
						}
					}
				}

				if ( movingData.m_path.empty() )
					break;
			}

			if ( !movingData.m_path.empty() )
			{
				Direction::Enum currentDirection = locateComponent->getDirection();
				Direction::Enum nextDirection = Direction::South;

				QPoint currentLocation( locateComponent->getLocation() );
				QPoint nextLocation = movingData.m_path.front();

				if ( nextLocation.y() > currentLocation.y() && nextLocation.x() > currentLocation.x() )
					nextDirection = Direction::SouthEast;
				else if ( nextLocation.y() < currentLocation.y() && nextLocation.x() > currentLocation.x() )
					nextDirection = Direction::NorthEast;
				else if ( nextLocation.y() > currentLocation.y() && nextLocation.x() < currentLocation.x() )
					nextDirection = Direction::SouthWest;
				else if ( nextLocation.y() < currentLocation.y() && nextLocation.x() < currentLocation.x() )
					nextDirection = Direction::NorthWest;
				else if ( nextLocation.y() > currentLocation.y() )
					nextDirection = Direction::South;
				else if ( nextLocation.y() < currentLocation.y() )
					nextDirection = Direction::North;
				else if ( nextLocation.x() > currentLocation.x() )
					nextDirection = Direction::East;
				else if ( nextLocation.x() < currentLocation.x() )
					nextDirection = Direction::West;

				ObjectState::Enum currentState = m_object.getState();
				ObjectState::Enum nextState = ObjectState::Moving;

				if ( currentDirection != nextDirection || currentState != nextState )
				{
					locateComponent->setDirection( nextDirection );
					m_object.setState( nextState );

					unitChangeSatate = true;
				}
			}
			else if ( !m_movingFinished )
			{
				isInFinishPoint = false;

				if ( moveComponent->getMovingData().m_movingToObject )
				{
					if ( movingData.m_path.empty() )
					{
						boost::intrusive_ptr< ILocateComponent > targetLocateComponent
							= moveComponent->getMovingData().m_movingToObject->getComponent< ILocateComponent >( ComponentId::Locate );

						if ( isOnRightDistanceToObject( targetLocateComponent->getRect(), locateComponent->getLocation() ) )
						{
							isInFinishPoint = true;
						}
					}
				}
				else if ( locateComponent->getLocation() == moveComponent->getMovingData().m_movingTo )
				{
					isInFinishPoint = true;
				}

				if ( !isInFinishPoint )
				{
					IMoveComponent::MovingData newMovingData;
					newMovingData.m_movingTo = moveComponent->getMovingData().m_movingTo;
					newMovingData.m_movingToObject = moveComponent->getMovingData().m_movingToObject;

					IPathFinder::PointsCollection targetPoints;
					fillPossibleTargetPoints( targetPoints, moveComponent->getMovingData() );

					m_pathFinder->findPath( newMovingData.m_path, m_landscape, *locateComponent, targetPoints );

					if ( newMovingData.m_path.empty() )
					{
						movingData.clear();
						m_movingFinished = true;
					}
					else
					{
						movingData = newMovingData;

						m_landscape.setEngagedWithGroungItem( locateComponent->getLocation(), false );
						m_landscape.setEngagedWithGroungItem( movingData.m_path.front(), true );
					}
				}
			}

			Framework::Core::EventManager::Event objectMovedEvent( Events::ObjectMoved::ms_type );
			objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_objectNameAttribute, m_object.getName() );
			objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_objectIdAttribute, m_object.getUniqueId() );
			objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingFromAttribute, locateComponent->getLocation() );
			objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingToAttribute, movingData.m_path.empty() ? locateComponent->getLocation() : movingData.m_path.front() );
			objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingProgressAttribute, movingData.m_path.empty() ? 1.0f : movingData.m_movingProgress );

			m_environment.riseEvent( objectMovedEvent );
		}

		isInFinishPoint = false;

		if ( moveComponent->getMovingData().m_movingToObject )
		{
			if ( movingData.m_path.empty() )
			{
				boost::intrusive_ptr< ILocateComponent > targetLocateComponent
					= moveComponent->getMovingData().m_movingToObject->getComponent< ILocateComponent >( ComponentId::Locate );

				if ( isOnRightDistanceToObject( targetLocateComponent->getRect(), locateComponent->getLocation() ) )
				{
					isInFinishPoint = true;
				}
			}
		}
		else if ( locateComponent->getLocation() == moveComponent->getMovingData().m_movingTo )
		{
			isInFinishPoint = true;
		}

		if ( ( m_movingFinished || isInFinishPoint ) && m_object.getState() == ObjectState::Moving )
		{
			movingData.clear();
			m_object.setState( ObjectState::Standing );
			
			unitChangeSatate = true;
			m_movingFinished = true;
		}

		if ( unitChangeSatate )
		{
			Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

			m_environment.riseEvent( objectStateChangedEvent );
		}
	}

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
	return m_movingFinished;

} // MoveAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
MoveAction::getType() const
{
	return Actions::Move;

} // MoveAction::getType


/*---------------------------------------------------------------------------*/


void
MoveAction::updateWithData( const QVariant& _data )
{
} // MoveAction::updateWithData


/*---------------------------------------------------------------------------*/


void
MoveAction::fillPossibleTargetPoints(
		IPathFinder::PointsCollection& _points
	,	const IMoveComponent::MovingData& _movingData ) const
{
	if ( _movingData.m_movingToObject )
	{
		boost::intrusive_ptr< ILocateComponent > targetLocateComponent
			= _movingData.m_movingToObject->getComponent< ILocateComponent >( ComponentId::Locate );

		QRect targetRect = targetLocateComponent->getRect();

		for ( int x = targetRect.x() - m_distance; x < targetRect.x() + targetRect.width() + m_distance; ++x )
		{
			for ( int y = targetRect.y() - m_distance; y < targetRect.y() + targetRect.height() + m_distance; ++y )
			{
				QPoint location( x, y );
				if ( m_landscape.isLocationInLandscape( location ) )
					_points.push_back( location );
			}
		}
	}
	else
	{
		_points.push_back( _movingData.m_movingTo );
	}

} // MoveAction::fillPossibleTargetPoints


/*---------------------------------------------------------------------------*/


bool
MoveAction::isOnRightDistanceToObject( const QRect& _objectRect, const QPoint& _location ) const
{
	for ( int x = _objectRect.x(); x < _objectRect.x() + _objectRect.width(); ++x )
	{
		for ( int y = _objectRect.y(); y < _objectRect.y() + _objectRect.height(); ++y )
		{
			QPoint point = _location - QPoint( x , y );

			int lenght = point.manhattanLength();
			if ( point.manhattanLength() <= m_distance )
				return true;
		}
	}

	return false;

} // MoveAction::isOnRightDistanceToObject


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
