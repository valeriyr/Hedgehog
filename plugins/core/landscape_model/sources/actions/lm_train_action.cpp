
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_train_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/ih/components/lm_itrain_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"

#include "landscape_model/ih/lm_imodel_locker.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


TrainAction::TrainAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	Object& _object
	,	const QString& _trainObjectName
	)
	:	BaseAction( _environment, _landscapeModel, _object )
	,	m_trainObjectName( _trainObjectName )
	,	m_trainingFinished( false )
{
} // TrainAction::TrainAction


/*---------------------------------------------------------------------------*/


TrainAction::~TrainAction()
{
} // TrainAction::~TrainAction


/*---------------------------------------------------------------------------*/


bool
TrainAction::prepareToProcessingInternal()
{
	boost::intrusive_ptr< ITrainComponent > trainComponent
		= m_object.getComponent< ITrainComponent >( ComponentId::Train );

	trainComponent->getTrainData().m_trainingObjectName = m_trainObjectName;

	return true;

} // TrainAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
TrainAction::cancelProcessing()
{
	boost::intrusive_ptr< ITrainComponent > trainComponent
		= m_object.getComponent< ITrainComponent >( ComponentId::Train );

	trainComponent->getTrainData().reset();
	m_trainingFinished = true;

	boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( m_object.getPlayerId() );

	if ( player )
	{
		ITrainComponent::StaticData::TrainDataCollectionIterator
			iterator = trainComponent->getStaticData().m_trainObjects.find( m_trainObjectName );

		if ( iterator != trainComponent->getStaticData().m_trainObjects.end() )
		{
			player->addResources( iterator->second->m_resourcesData );
		}
	}

	Framework::Core::EventManager::Event trainQueueChangedEvent( Events::TrainQueueChanged::ms_type );
	trainQueueChangedEvent.pushAttribute( Events::TrainQueueChanged::ms_trainerIdAttribute, m_object.getUniqueId() );

	m_environment.riseEvent( trainQueueChangedEvent );

	m_isInProcessing = false;

	return true;

} // TrainAction::cancelProcessing


/*---------------------------------------------------------------------------*/


void
TrainAction::processAction( const unsigned int _deltaTime )
{
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< ITrainComponent > trainComponent
		= m_object.getComponent< ITrainComponent >( ComponentId::Train );

	ITrainComponent::Data& trainData = trainComponent->getTrainData();

	if ( m_object.getState() == ObjectState::Dying )
	{
		m_trainingFinished = true;
	}
	else
	{
		int creatingTime
			= trainComponent->getStaticData().m_trainObjects.find( trainData.m_trainingObjectName )->second->m_creationTime;
		float creatingDelta = static_cast< float >( _deltaTime ) / creatingTime;

		trainData.m_trainProgress += creatingDelta;

		if ( trainData.m_trainProgress >= 1.0f )
		{
			m_landscapeModel.createObject(
					m_landscapeModel.getLandscape()->getNearestLocation( m_object, trainData.m_trainingObjectName )
				,	trainData.m_trainingObjectName );

			m_trainingFinished = true;
		}

		Framework::Core::EventManager::Event trainQueueChangedEvent( Events::TrainQueueChanged::ms_type );
		trainQueueChangedEvent.pushAttribute( Events::TrainQueueChanged::ms_trainerIdAttribute, m_object.getUniqueId() );
	
		m_environment.riseEvent( trainQueueChangedEvent );
	}

	if ( m_trainingFinished )
	{
		trainData.reset();
	}

} // TrainAction::processAction


/*---------------------------------------------------------------------------*/


bool
TrainAction::hasFinished() const
{
	return m_trainingFinished;

} // TrainAction::hasFinished


/*---------------------------------------------------------------------------*/


const Actions::Enum
TrainAction::getType() const
{
	return Actions::Train;

} // TrainAction::getType


/*---------------------------------------------------------------------------*/


const QString&
TrainAction::getTrainObjectName() const
{
	return m_trainObjectName;

} // TrainAction::getTrainObjectName


/*---------------------------------------------------------------------------*/

} // namespace LandscapeModel
} // namespace Core
} // namespace Plugins

/*---------------------------------------------------------------------------*/
