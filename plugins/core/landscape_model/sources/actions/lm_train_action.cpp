
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_train_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"

#include "landscape_model/ih/components/lm_itrain_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iplayer_component.hpp"


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
	boost::intrusive_ptr< IPlayerComponent > playerComponent
		= m_object.getComponent< IPlayerComponent >( ComponentId::Player );

	trainComponent->getTrainData().reset();

	boost::intrusive_ptr< IPlayer > player = m_landscapeModel.getPlayer( playerComponent->getPlayerId() );

	if ( player )
	{
		ITrainComponent::StaticData::TrainDataCollectionIterator
			iterator = trainComponent->getStaticData().m_trainObjects.find( m_trainObjectName );

		if ( iterator != trainComponent->getStaticData().m_trainObjects.end() )
		{
			player->addResources( iterator->second->m_resourcesData );
		}
	}

	m_environment.riseEvent(
		Framework::Core::EventManager::Event( Events::TrainQueueChanged::ms_type )
			.pushAttribute( Events::TrainQueueChanged::ms_trainerIdAttribute, m_object.getUniqueId() ) );

	m_isInProcessing = false;

	return true;

} // TrainAction::cancelProcessing


/*---------------------------------------------------------------------------*/


void
TrainAction::processAction()
{
	boost::intrusive_ptr< ILocateComponent > locateComponent
		= m_object.getComponent< ILocateComponent >( ComponentId::Locate );
	boost::intrusive_ptr< ITrainComponent > trainComponent
		= m_object.getComponent< ITrainComponent >( ComponentId::Train );

	ITrainComponent::Data& trainData = trainComponent->getTrainData();

	if ( m_object.getState() == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		++trainData.m_trainProgress;

		TickType creationTime
			= trainComponent->getStaticData().m_trainObjects.find( trainData.m_trainingObjectName )->second->m_creationTime;

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::TrainProgressChanged::ms_type )
				.pushAttribute( Events::TrainProgressChanged::ms_trainerIdAttribute, m_object.getUniqueId() )
				.pushAttribute( Events::TrainProgressChanged::ms_trainerProgressAttribute, trainData.m_trainProgress )
				.pushAttribute( Events::TrainProgressChanged::ms_creationTimeAttribute, creationTime ) );

		if ( trainData.m_trainProgress == creationTime )
		{
			boost::intrusive_ptr< IPlayerComponent > playerComponent
				= m_object.getComponent< IPlayerComponent >( ComponentId::Player );

			m_landscapeModel.createObject(
					m_landscapeModel.getLandscape()->getNearestLocation( m_object, trainData.m_trainingObjectName )
				,	trainData.m_trainingObjectName
				,	playerComponent ? playerComponent->getPlayerId() : IPlayer::ms_wrondId );

			m_environment.riseEvent(
				Framework::Core::EventManager::Event( Events::TrainQueueChanged::ms_type )
					.pushAttribute( Events::TrainQueueChanged::ms_trainerIdAttribute, m_object.getUniqueId() ) );

			m_isInProcessing = false;
		}
	}

	if ( !m_isInProcessing )
	{
		trainData.reset();
	}

} // TrainAction::processAction


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
