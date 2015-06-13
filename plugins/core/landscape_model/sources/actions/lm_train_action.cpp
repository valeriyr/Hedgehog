
#include "landscape_model/sources/ph/lm_ph.hpp"

#include "landscape_model/sources/actions/lm_train_action.hpp"

#include "landscape_model/sources/environment/lm_ienvironment.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_model.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace Core {
namespace LandscapeModel {

/*---------------------------------------------------------------------------*/


TrainAction::TrainAction(
		const IEnvironment& _environment
	,	ILandscapeModel& _landscapeModel
	,	GameObject& _object
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
	const ObjectState::Enum objectState = m_object.getMember< ObjectState::Enum >( ObjectStateKey );

	if ( objectState == ObjectState::Dying || objectState == ObjectState::UnderConstruction )
		return false;

	Tools::Core::Object::Ptr trainComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( TrainComponent::Name );

	trainComponent->getMember< TrainComponent::ProgressData >( TrainComponent::Progress ).m_trainingObjectName = m_trainObjectName;

	return true;

} // TrainAction::prepareToProcessingInternal


/*---------------------------------------------------------------------------*/


bool
TrainAction::cancelProcessing()
{
	Tools::Core::Object::Ptr trainComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( TrainComponent::Name );
	Tools::Core::Object::Ptr playerComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

	trainComponent->getMember< TrainComponent::ProgressData >( TrainComponent::Progress ).reset();

	boost::intrusive_ptr< IPlayer > player
		= m_landscapeModel.getPlayer( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) );

	if ( player )
	{
		TrainComponent::StaticData::Data::Ptr trainObjectStaticData
			= trainComponent->getMember< TrainComponent::StaticData::Data::Ptr >(
				StaticDataTools::generateName( TrainComponent::StaticData::DataKey ) );

		TrainComponent::StaticData::Data::TrainDataCollectionIterator
			iterator = trainObjectStaticData->m_trainObjects.find( m_trainObjectName );

		if ( iterator != trainObjectStaticData->m_trainObjects.end() )
		{
			player->addResources( iterator->second->m_resourcesData );
		}
	}

	m_environment.riseEvent(
		Framework::Core::EventManager::Event( Events::TrainQueueChanged::Type )
			.pushMember( Events::TrainQueueChanged::TrainerIdAttribute, m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey ) ) );

	m_isInProcessing = false;

	return true;

} // TrainAction::cancelProcessing


/*---------------------------------------------------------------------------*/


void
TrainAction::processAction()
{
	Tools::Core::Object::Ptr trainComponent
		= m_object.getMember< Tools::Core::Object::Ptr >( TrainComponent::Name );

	TrainComponent::ProgressData& progressData = trainComponent->getMember< TrainComponent::ProgressData >( TrainComponent::Progress );

	if ( m_object.getMember< ObjectState::Enum >( ObjectStateKey ) == ObjectState::Dying )
	{
		m_isInProcessing = false;
	}
	else
	{
		const Tools::Core::Generators::IGenerator::IdType objectId
			= m_object.getMember< Tools::Core::Generators::IGenerator::IdType >( ObjectUniqueIdKey );

		++progressData.m_trainProgress;

		TickType creationTime
			= trainComponent->getMember< TrainComponent::StaticData::Data::Ptr >( StaticDataTools::generateName( TrainComponent::StaticData::DataKey ) )
				->m_trainObjects.find( progressData.m_trainingObjectName )->second->m_creationTime;

		m_environment.riseEvent(
			Framework::Core::EventManager::Event( Events::TrainProgressChanged::Type )
				.pushMember( Events::TrainProgressChanged::TrainerIdAttribute, objectId )
				.pushMember( Events::TrainProgressChanged::TrainerProgressAttribute, progressData.m_trainProgress )
				.pushMember( Events::TrainProgressChanged::CreationTimeAttribute, creationTime ) );

		if ( progressData.m_trainProgress == creationTime )
		{
			Tools::Core::Object::Ptr playerComponent
				= m_object.getMember< Tools::Core::Object::Ptr >( PlayerComponent::Name );

			m_landscapeModel.processCommand(
					Command( CommandId::CreateObject )
						.pushArgument( playerComponent ? playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( PlayerComponent::PlayerId ) : Tools::Core::Generators::IGenerator::ms_wrongId )
						.pushArgument( progressData.m_trainingObjectName )
						.pushArgument( m_landscapeModel.getLandscape()->getNearestLocation( m_object, progressData.m_trainingObjectName ) ) );

			m_environment.riseEvent(
				Framework::Core::EventManager::Event( Events::TrainQueueChanged::Type )
					.pushMember( Events::TrainQueueChanged::TrainerIdAttribute, objectId ) );

			m_isInProcessing = false;
		}
	}

	if ( !m_isInProcessing )
	{
		progressData.reset();
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
