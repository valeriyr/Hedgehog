
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_build_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/sources/actions/lm_move_action.hpp"

#include "landscape_model/sources/geometry/lm_geometry.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BuildAction::BuildAction(
		const IEnvironment& _environment
	,	Object& _object
	,	IPlayer& _player
	,	ILandscape& _landscape
	,	ILandscapeModel& _landscapeModel
	,	boost::intrusive_ptr< IPathFinder > _pathFinder
	)
	:	BaseAction( _environment, _object )
	,	m_player( _player )
	,	m_landscape( _landscape )
	,	m_landscapeModel( _landscapeModel )
	,	m_pathFinder( _pathFinder )
	,	m_moveAction()
{
} // BuildAction::BuildAction


/*---------------------------------------------------------------------------*/


BuildAction::~BuildAction()
{
} // BuildAction::~BuildAction


/*---------------------------------------------------------------------------*/


void
BuildAction::processAction( const unsigned int _deltaTime )
{
	boost::intrusive_ptr< IBuildComponent > buildComponent
		= m_object.getComponent< IBuildComponent >( ComponentId::Build );
	IBuildComponent::BuildData& buildData = buildComponent->getBuildData();

	if ( m_object.getState() == ObjectState::Dying )
	{
		buildData.clear();
		return;
	}

	if ( buildData.m_buildQueue.empty() )
		return;

	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );

	QPoint nearestPoint = Geometry::getNearestPoint( locateComponent->getLocation(), buildData.m_buildQueue.front().second );

	if ( Geometry::getDistance( locateComponent->getLocation(), nearestPoint ) > 1.0f )
	{
		if ( !m_moveAction )
		{
			boost::intrusive_ptr< IMoveComponent > moveComponent
				= m_object.getComponent< IMoveComponent >( ComponentId::Move );
			moveComponent->getMovingData().m_movingTo = nearestPoint;

			m_moveAction.reset( new MoveAction( m_environment, m_object, m_landscape, m_pathFinder, 1 ) );
		}
	}

	if ( m_moveAction )
	{
		m_moveAction->processAction( _deltaTime );

		if ( m_moveAction->hasFinished() )
			m_moveAction.reset();
	}
	else
	{
		if ( buildData.m_buildProgress == 0 )
		{
			// remove builder from map
		}

		int buildingTime = buildComponent->getStaticData().m_buildDatas.find( buildData.m_buildQueue.front().first )->second->m_buildTime;
		int buildingDelta = ( static_cast< float >( _deltaTime ) / buildingTime ) * 100;

		buildData.m_buildProgress += buildingDelta;

		if ( buildData.m_buildProgress > 100 )
		{
			// add builder to map

			/*boost::intrusive_ptr< ILocateComponent > locateComponent
				= m_object.getComponent< ILocateComponent >( ComponentId::Locate );

			m_landscapeModel.createObject( m_landscape.getNearestLocation( m_object, trainData.m_trainQueue.front() ), trainData.m_trainQueue.front() );*/

			buildData.m_buildProgress = 0;
			buildData.m_buildQueue.pop_front();
		}

		Framework::Core::EventManager::Event buildQueueChangedEvent( Events::BuildQueueChanged::ms_type );
		buildQueueChangedEvent.pushAttribute( Events::BuildQueueChanged::ms_builderIdAttribute, m_object.getUniqueId() );
	
		m_environment.riseEvent( buildQueueChangedEvent );
	}

} // BuildAction::processAction


/*---------------------------------------------------------------------------*/


void
BuildAction::unprocessAction( const unsigned int _deltaTime )
{
} // BuildAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
BuildAction::hasFinished() const
{
	IBuildComponent::BuildData& buildData
		= m_object.getComponent< IBuildComponent >( ComponentId::Build )->getBuildData();
	return buildData.m_buildQueue.empty();

} // BuildAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
BuildAction::getType() const
{
	return Actions::Build;

} // BuildAction::getType


/*---------------------------------------------------------------------------*/


void
BuildAction::updateWithData( const QVariant& _data )
{
} // BuildAction::updateWithData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
