
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
	,	const QPoint& _to
	)
	:	BaseAction( _environment, _object )
	,	m_landscape( _landscape )
	,	m_pathFinder( _pathFinder )
	,	m_to( _to )
	,	m_movingFinished( false )
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

	if ( locateComponent->getLocation() == m_to )
	{
		moveComponent->getMovingData().clear();
		m_movingFinished = true;
	}
	else
	{
		if ( moveComponent->getMovingData().m_path.empty() )
		{
			moveComponent->getMovingData().clear();

			IMoveComponent::MovingData movingData;
			m_pathFinder->findPath( movingData.m_path, m_landscape, *locateComponent, m_to );

			if ( movingData.m_path.empty() )
			{
				m_movingFinished = true;
			}
			else
			{
				moveComponent->getMovingData() = movingData;

				m_landscape.setEngagedWithGroungItem( locateComponent->getLocation(), false );
				m_landscape.setEngagedWithGroungItem( moveComponent->getMovingData().m_path.front(), true );
			}
		}

		std::vector< Framework::Core::EventManager::Event > events;

		if ( !m_movingFinished )
		{
			float movingDelta = ( static_cast< float >( _deltaTime ) / moveComponent->getStaticData().m_movingSpeed );
			moveComponent->getMovingData().m_movingProgress += movingDelta;

			while ( moveComponent->getMovingData().m_movingProgress >= 1.0 )
			{
				moveComponent->getMovingData().m_movingProgress = moveComponent->getMovingData().m_movingProgress - 1.0;

				QPoint location( QPoint( moveComponent->getMovingData().m_path.front() ) );

				locateComponent->setLocation( location );

				moveComponent->getMovingData().m_path.pop_front();

				if ( !moveComponent->getMovingData().m_path.empty() )
				{
					if ( m_landscape.canObjectBePlaced( moveComponent->getMovingData().m_path.front(), locateComponent->getStaticData() ) )
					{
						m_landscape.setEngagedWithGroungItem( location, false );
						m_landscape.setEngagedWithGroungItem( moveComponent->getMovingData().m_path.front(), true );
					}
					else
					{
						IMoveComponent::MovingData movingData;
						m_pathFinder->findPath( movingData.m_path, m_landscape, *locateComponent, m_to );
						
						if ( movingData.m_path.empty() )
						{
							m_movingFinished = true;
							moveComponent->getMovingData().clear();
							break;
						}
						else
						{
							moveComponent->getMovingData() = movingData;

							m_landscape.setEngagedWithGroungItem( location, false );
							m_landscape.setEngagedWithGroungItem( movingData.m_path.front(), true );
						}
					}
				}

				if ( moveComponent->getMovingData().m_path.empty() )
					break;
			}

			if ( !moveComponent->getMovingData().m_path.empty() )
			{
				Direction::Enum currentDirection = locateComponent->getDirection();
				Direction::Enum nextDirection = Direction::Down;

				QPoint currentLocation( locateComponent->getLocation() );
				QPoint nextLocation = moveComponent->getMovingData().m_path.front();

				if ( nextLocation.y() > currentLocation.y() )
					nextDirection = Direction::Down;
				else if ( nextLocation.y() < currentLocation.y() )
					nextDirection = Direction::Up;
				else if ( nextLocation.x() < currentLocation.x() )
					nextDirection = Direction::Right;
				else if ( nextLocation.x() > currentLocation.x() )
					nextDirection = Direction::Left;

				ObjectState::Enum currentState = m_object.getState();
				ObjectState::Enum nextState = ObjectState::Moving;

				if ( currentDirection != nextDirection || currentState != nextState )
				{
					locateComponent->setDirection( nextDirection );
					m_object.setState( nextState );

					Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
					objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

					events.push_back( objectStateChangedEvent );
				}

				Framework::Core::EventManager::Event objectMovedEvent( Events::ObjectMoved::ms_type );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_objectNameAttribute, m_object.getName() );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_objectIdAttribute, m_object.getUniqueId() );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingFromAttribute, locateComponent->getLocation() );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingToAttribute, moveComponent->getMovingData().m_path.front() );
				objectMovedEvent.pushAttribute( Events::ObjectMoved::ms_movingProgressAttribute, moveComponent->getMovingData().m_movingProgress );

				events.push_back( objectMovedEvent );
			}
			else if ( !m_movingFinished && locateComponent->getLocation() != m_to )
			{
				moveComponent->getMovingData().clear();

				IMoveComponent::MovingData movingData;
				m_pathFinder->findPath( movingData.m_path, m_landscape, *locateComponent, m_to );

				if ( movingData.m_path.empty() )
				{
					m_movingFinished = true;
				}
				else
				{
					moveComponent->getMovingData() = movingData;

					m_landscape.setEngagedWithGroungItem( locateComponent->getLocation(), false );
					m_landscape.setEngagedWithGroungItem( moveComponent->getMovingData().m_path.front(), true );
				}
			}
		}

		if ( ( m_movingFinished || locateComponent->getLocation() == m_to ) && m_object.getState() == ObjectState::Moving )
		{
			m_object.setState( ObjectState::Standing );

			Framework::Core::EventManager::Event objectStateChangedEvent( Events::ObjectStateChanged::ms_type );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectNameAttribute, m_object.getName() );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectIdAttribute, m_object.getUniqueId() );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectState, m_object.getState() );
			objectStateChangedEvent.pushAttribute( Events::ObjectStateChanged::ms_objectDirection, locateComponent->getDirection() );

			events.push_back( objectStateChangedEvent );

			m_movingFinished = true;
		}

		std::vector< Framework::Core::EventManager::Event >::const_iterator
				begin = events.begin()
			,	end = events.end();

		for ( ; begin != end; ++begin )
			m_environment.riseEvent( *begin );
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
	m_to = _data.toPoint();

	boost::intrusive_ptr< IMoveComponent > moveComponent
		= m_object.getComponent< IMoveComponent >( ComponentId::Move );

	assert( !m_movingFinished );

	if ( !moveComponent->getMovingData().m_path.empty() )
	{
		QPoint inProgressPoint( moveComponent->getMovingData().m_path.front() );

		moveComponent->getMovingData().m_path.clear();

		moveComponent->getMovingData().m_path.push_back( inProgressPoint );
	}

} // MoveAction::updateWithData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
