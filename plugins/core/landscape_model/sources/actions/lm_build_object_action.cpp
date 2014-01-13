
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_build_object_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


BuildObjectAction::BuildObjectAction(
		const IEnvironment& _environment
	,	Object& _object
	,	IPlayer& _player
	,	ILandscape& _landscape
	,	ILandscapeModel& _landscapeModel
	)
	:	BaseAction( _environment, _object )
	,	m_player( _player )
	,	m_landscape( _landscape )
	,	m_landscapeModel( _landscapeModel )
{
} // BuildObjectAction::BuildObjectAction


/*---------------------------------------------------------------------------*/


BuildObjectAction::~BuildObjectAction()
{
} // BuildObjectAction::~BuildObjectAction


/*---------------------------------------------------------------------------*/


void
BuildObjectAction::processAction( const unsigned int _deltaTime )
{
	boost::intrusive_ptr< IBuilderComponent > builderComponent
		= m_object.getComponent< IBuilderComponent >( ComponentId::Builder );
	IBuilderComponent::BuildData& buildData = builderComponent->getBuildData();

	int creatingTime
		= builderComponent->getStaticData().m_buildObjects.find( buildData.m_buildQueue.front() )->second->m_creationTime;
	int creatingDelta = ( static_cast< float >( _deltaTime ) / creatingTime ) * 100;

	buildData.m_buildProgress += creatingDelta;

	if ( buildData.m_buildProgress > 100 )
	{
		boost::intrusive_ptr< ILocateComponent > locateComponent
			= m_object.getComponent< ILocateComponent >( ComponentId::Locate );

		m_landscapeModel.createObject( m_landscape.getNearestLocation( m_object, buildData.m_buildQueue.front() ), buildData.m_buildQueue.front() );

		buildData.m_buildProgress = 0;
		buildData.m_buildQueue.pop_front();
	}

	Framework::Core::EventManager::Event builderQueueChangedEvent( Events::BuilderQueueChanged::ms_type );
	builderQueueChangedEvent.pushAttribute( Events::BuilderQueueChanged::ms_builderIdAttribute, m_object.getUniqueId() );
	
	m_environment.riseEvent( builderQueueChangedEvent );

} // BuildObjectAction::processAction


/*---------------------------------------------------------------------------*/


void
BuildObjectAction::unprocessAction( const unsigned int _deltaTime )
{
} // BuildObjectAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
BuildObjectAction::hasFinished() const
{
	IBuilderComponent::BuildData& buildData
		= m_object.getComponent< IBuilderComponent >( ComponentId::Builder )->getBuildData();
	return buildData.m_buildQueue.empty();

} // BuildObjectAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
BuildObjectAction::getType() const
{
	return Actions::Build;

} // BuildObjectAction::getType


/*---------------------------------------------------------------------------*/


void
BuildObjectAction::updateWithData( const QVariant& _data )
{
} // BuildObjectAction::updateWithData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
