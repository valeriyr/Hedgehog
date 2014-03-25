
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_train_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_iplayer.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/ih/components/lm_itrain_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


TrainAction::TrainAction(
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
} // TrainAction::TrainAction


/*---------------------------------------------------------------------------*/


TrainAction::~TrainAction()
{
} // TrainAction::~TrainAction


/*---------------------------------------------------------------------------*/


void
TrainAction::processAction( const unsigned int _deltaTime )
{
	boost::intrusive_ptr< ITrainComponent > trainComponent
		= m_object.getComponent< ITrainComponent >( ComponentId::Train );
	ITrainComponent::Data& trainData = trainComponent->getTrainData();

	if ( m_object.getState() == ObjectState::Dying )
	{
		trainData.clear();
		return;
	}

	int creatingTime
		= trainComponent->getStaticData().m_trainObjects.find( trainData.m_trainQueue.front() )->second->m_creationTime;
	int creatingDelta = ( static_cast< float >( _deltaTime ) / creatingTime ) * 100;

	trainData.m_trainProgress += creatingDelta;

	if ( trainData.m_trainProgress >= 100 )
	{
		boost::intrusive_ptr< ILocateComponent > locateComponent
			= m_object.getComponent< ILocateComponent >( ComponentId::Locate );

		m_landscapeModel.createObject( m_landscape.getNearestLocation( m_object, trainData.m_trainQueue.front() ), trainData.m_trainQueue.front() );

		trainData.m_trainProgress = 0;
		trainData.m_trainQueue.pop_front();
	}

	Framework::Core::EventManager::Event trainQueueChangedEvent( Events::TrainQueueChanged::ms_type );
	trainQueueChangedEvent.pushAttribute( Events::TrainQueueChanged::ms_trainerIdAttribute, m_object.getUniqueId() );
	
	m_environment.riseEvent( trainQueueChangedEvent );

} // TrainAction::processAction


/*---------------------------------------------------------------------------*/


void
TrainAction::unprocessAction( const unsigned int _deltaTime )
{
} // TrainAction::unprocessAction


/*---------------------------------------------------------------------------*/


bool
TrainAction::hasFinished() const
{
	ITrainComponent::Data& trainData
		= m_object.getComponent< ITrainComponent >( ComponentId::Train )->getTrainData();
	return trainData.m_trainQueue.empty();

} // TrainAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
TrainAction::getType() const
{
	return Actions::Train;

} // TrainAction::getType


/*---------------------------------------------------------------------------*/


void
TrainAction::updateWithData( const QVariant& _data )
{
} // TrainAction::updateWithData


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
