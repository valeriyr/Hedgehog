
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_build_action.hpp"

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


BuildAction::BuildAction(
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
} // BuildAction::BuildAction


/*---------------------------------------------------------------------------*/


BuildAction::~BuildAction()
{
} // BuildAction::~BuildAction


/*---------------------------------------------------------------------------*/


void
BuildAction::processAction( const unsigned int _deltaTime )
{
	/*boost::intrusive_ptr< ITrainComponent > trainComponent
		= m_object.getComponent< ITrainComponent >( ComponentId::Train );
	ITrainComponent::TrainData& trainData = trainComponent->getTrainData();

	if ( m_object.getState() == ObjectState::Dying )
	{
		trainData.m_trainQueue.clear();
		return;
	}

	int creatingTime
		= trainComponent->getStaticData().m_buildObjects.find( trainData.m_trainQueue.front() )->second->m_creationTime;
	int creatingDelta = ( static_cast< float >( _deltaTime ) / creatingTime ) * 100;

	trainData.m_trainProgress += creatingDelta;

	if ( trainData.m_trainProgress > 100 )
	{
		boost::intrusive_ptr< ILocateComponent > locateComponent
			= m_object.getComponent< ILocateComponent >( ComponentId::Locate );

		m_landscapeModel.createObject( m_landscape.getNearestLocation( m_object, trainData.m_trainQueue.front() ), trainData.m_trainQueue.front() );

		trainData.m_trainProgress = 0;
		trainData.m_trainQueue.pop_front();
	}

	Framework::Core::EventManager::Event builderQueueChangedEvent( Events::BuilderQueueChanged::ms_type );
	builderQueueChangedEvent.pushAttribute( Events::BuilderQueueChanged::ms_builderIdAttribute, m_object.getUniqueId() );
	
	m_environment.riseEvent( builderQueueChangedEvent );*/

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
	/*ITrainComponent::TrainData& trainData
		= m_object.getComponent< ITrainComponent >( ComponentId::Train )->getTrainData();
	return trainData.m_trainQueue.empty();*/

	return true;

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
