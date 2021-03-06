
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_object_info_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

ObjectInfoView::ObjectInfoView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::ObjectInfoViewTitle )
	,	m_mainWidget( new QTextEdit() )
	,	m_showingObjectId( Tools::Core::Generators::IGenerator::ms_wrongId )
{
	m_mainWidget->setReadOnly( true );

	setDescriptionForObject( Tools::Core::Generators::IGenerator::ms_wrongId );

} // ObjectInfoView::ObjectInfoView


/*---------------------------------------------------------------------------*/


ObjectInfoView::~ObjectInfoView()
{
} // ObjectInfoView::~ObjectInfoView


/*---------------------------------------------------------------------------*/


const QString&
ObjectInfoView::getViewTitle() const
{
	return m_viewTitle;

} // ObjectInfoView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
ObjectInfoView::getViewWidget()
{
	return m_mainWidget.get();

} // ObjectInfoView::getViewWidget


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::viewWasClosed()
{
	m_mainWidget.reset();

} // ObjectInfoView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::landscapeWasOpened()
{
	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectsSelectionChanged::Type
							,	boost::bind( &ObjectInfoView::onObjectsSelectionChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectStateChanged::Type
							,	boost::bind( &ObjectInfoView::onObjectStateChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectMoved::Type
							,	boost::bind( &ObjectInfoView::onObjectMoved, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectHealthChanged::Type
							,	boost::bind( &ObjectInfoView::onObjectHealthChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::HolderResourceCountChanged::Type
							,	boost::bind( &ObjectInfoView::onHolderResourceCountChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::BuilderHasStartedBuild::Type
							,	boost::bind( &ObjectInfoView::onBuilderHasStartedBuild, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::BuilderHasFinishedBuild::Type
							,	boost::bind( &ObjectInfoView::onBuilderHasFinishedBuild, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::HolderHasStartedCollect::Type
							,	boost::bind( &ObjectInfoView::onHolderHasStartedCollect, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::HolderHasStopCollect::Type
							,	boost::bind( &ObjectInfoView::onHolderHasStopCollect, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ResourceSourceValueChanged::Type
							,	boost::bind( &ObjectInfoView::onResourceSourceValueChanged, this, _1 ) );

} // ObjectInfoView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	setDescriptionForObject( Tools::Core::Generators::IGenerator::ms_wrongId );

} // ObjectInfoView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
		handle->getLandscapeModel()->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

		setDescriptionForObject(
				selectedObjectsCollection.empty()
			?	Tools::Core::Generators::IGenerator::ms_wrongId
			:	selectedObjectsCollection.front()->getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::ObjectUniqueIdKey ) );
	}

} // ObjectInfoView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onObjectStateChanged( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::ObjectStateChanged::ObjectIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onObjectStateChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onObjectMoved( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::ObjectMoved::ObjectIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onObjectMoved


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onObjectHealthChanged( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::ObjectHealthChanged::ObjectIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onObjectHealthChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onHolderResourceCountChanged( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::HolderResourceCountChanged::ObjectUniqueIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onHolderResourceCountChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onBuilderHasStartedBuild( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::BuilderHasStartedBuild::ObjectUniqueIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onBuilderHasStartedBuild


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onBuilderHasFinishedBuild( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::BuilderHasFinishedBuild::ObjectUniqueIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onBuilderHasFinishedBuild


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onHolderHasStartedCollect( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::HolderHasStartedCollect::ObjectUniqueIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onHolderHasStartedCollect


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onHolderHasStopCollect( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::HolderHasStopCollect::ObjectUniqueIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onHolderHasStopCollect


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onResourceSourceValueChanged( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::ResourceSourceValueChanged::ObjectUniqueIdAttribute );

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onResourceSourceValueChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::setDescriptionForObject( const Tools::Core::Generators::IGenerator::IdType& _objectId )
{
	m_showingObjectId = Tools::Core::Generators::IGenerator::ms_wrongId;

	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		boost::shared_ptr< Core::LandscapeModel::GameObject > object = handle->getLandscapeModel()->getLandscape()->getObject( _objectId );

		if ( object )
		{
			m_showingObjectId = object->getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::ObjectUniqueIdKey );

			Tools::Core::Object::Ptr locateComponent = object->getMemberObject( Core::LandscapeModel::LocateComponent::Name );
			Tools::Core::Object::Ptr healthComponent = object->getMemberObject( Core::LandscapeModel::HealthComponent::Name );
			Tools::Core::Object::Ptr moveComponent = object->getMemberObject( Core::LandscapeModel::MoveComponent::Name );
			Tools::Core::Object::Ptr attackComponent = object->getMemberObject( Core::LandscapeModel::AttackComponent::Name );
			Tools::Core::Object::Ptr resourceHolderComponent = object->getMemberObject( Core::LandscapeModel::ResourceHolderComponent::Name );
			Tools::Core::Object::Ptr resourceSourceComponent = object->getMemberObject( Core::LandscapeModel::ResourceSourceComponent::Name );
			Tools::Core::Object::Ptr resourceStorageComponent = object->getMemberObject( Core::LandscapeModel::ResourceStorageComponent::Name );
			Tools::Core::Object::Ptr playerComponent = object->getMemberObject( Core::LandscapeModel::PlayerComponent::Name );

			QString resourceHolderData;

			if ( resourceHolderComponent )
			{
				const Core::LandscapeModel::ResourceHolderComponent::StaticData::HoldStaticData& holderData
					= resourceHolderComponent->getMember< Core::LandscapeModel::ResourceHolderComponent::StaticData::HoldStaticData >(
						Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::ResourceHolderComponent::StaticData::HoldStaticDataKey ) );

				Core::LandscapeModel::ResourceHolderComponent::StaticData::HoldStaticData::HoldResourceDataCollectionIterator
						begin = holderData.m_holdResourceData.begin()
					,	end = holderData.m_holdResourceData.end()
					,	it = holderData.m_holdResourceData.begin();

				for ( ; it != end; ++it )
				{
					if ( it != begin )
					{
						resourceHolderData += ", ";
					}

					resourceHolderData
						+= QString( Resources::Views::ResourcesHoldFormat )
								.arg( it->first )
								.arg( resourceHolderComponent->getMember< Core::LandscapeModel::ResourcesData >( Core::LandscapeModel::ResourceHolderComponent::HeldResources ).getResourceValue( it->first ) )
								.arg( it->second.m_maxValue );
				}
			}
			else
			{
				resourceHolderData = Resources::Views::NoneString;
			}

			QString resourceStorageData;

			if ( resourceStorageComponent )
			{
				const Core::LandscapeModel::ResourceStorageComponent::StaticData::PossibleToStoreData& possibleToStoreData
					= resourceStorageComponent->getMember< Core::LandscapeModel::ResourceStorageComponent::StaticData::PossibleToStoreData >(
						Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::ResourceStorageComponent::StaticData::PossibleToStore ) );

				Core::LandscapeModel::ResourceStorageComponent::StaticData::PossibleToStoreData::PossibleToStoreDataCollectionIterator
						begin = possibleToStoreData.m_possibleToStoreData.begin()
					,	end = possibleToStoreData.m_possibleToStoreData.end()
					,	it = possibleToStoreData.m_possibleToStoreData.begin();

				for ( ; it != end; ++it )
				{
					if ( it != begin )
					{
						resourceStorageData += ", ";
					}

					resourceStorageData += *it;
				}
			}
			else
			{
				resourceStorageData = Resources::Views::NoneString;
			}

			const QString objectName = object->getMember< QString >( Core::LandscapeModel::ObjectNameKey );
			const Tools::Core::Generators::IGenerator::IdType objectId
				= object->getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::ObjectUniqueIdKey );
			const Core::LandscapeModel::ObjectState::Enum objectState
				= object->getMember< Core::LandscapeModel::ObjectState::Enum >( Core::LandscapeModel::ObjectStateKey );

			m_mainWidget->setHtml(
				QString( Resources::Views::ObjectInfoFormat )
					.arg( objectName )
					.arg( objectId )
					.arg( Core::LandscapeModel::ObjectState::toString( objectState ) )
					.arg( playerComponent ? QString::number( playerComponent->getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::PlayerComponent::PlayerId ) ) : Resources::Views::NoneString )
					.arg( healthComponent ? QString::number( healthComponent->getMember< qint32 >( Core::LandscapeModel::HealthComponent::Health ) ) : Resources::Views::NoneString )
					.arg( healthComponent ? QString::number( healthComponent->getMember< qint32 >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::HealthComponent::StaticData::MaxHealth ) ) ) : Resources::Views::NoneString )
					.arg( moveComponent ? QString::number( moveComponent->getMember< Core::LandscapeModel::TickType >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::MoveComponent::StaticData::MovingSpeed ) ) ) : Resources::Views::NoneString )
					.arg( locateComponent->getMember< QPoint >( Core::LandscapeModel::LocateComponent::Location ).x() )
					.arg( locateComponent->getMember< QPoint >( Core::LandscapeModel::LocateComponent::Location ).y() )
					.arg( locateComponent->getMember< QSize >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::LocateComponent::StaticData::Size ) ).width() )
					.arg( locateComponent->getMember< QSize >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::LocateComponent::StaticData::Size ) ).height() )
					.arg( Core::LandscapeModel::Emplacement::toString( locateComponent->getMember< Core::LandscapeModel::Emplacement::Enum >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::LocateComponent::StaticData::Emplacement ) ) ) )
					.arg(	attackComponent
						?	QString( Resources::Views::DamageInfoFormat )
								.arg( attackComponent->getMember< qint32 >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::AttackComponent::StaticData::MinDamage ) ) )
								.arg( attackComponent->getMember< qint32 >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::AttackComponent::StaticData::MaxDamage ) ) )
						:	Resources::Views::NoneString )
						.arg( attackComponent ? QString::number( attackComponent->getMember< qint32 >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::AttackComponent::StaticData::Distance ) ) ) : Resources::Views::NoneString )
					.arg(	resourceSourceComponent
						?	QString( Resources::Views::ResourcesSourceFormat )
								.arg( resourceSourceComponent->getMember< QString >( Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::ResourceSourceComponent::StaticData::ResourceType ) ) )
								.arg( resourceSourceComponent->getMember< qint32 >( Core::LandscapeModel::ResourceSourceComponent::ResourceValue ) )
						:	Resources::Views::NoneString )
					.arg( resourceHolderData )
					.arg( resourceStorageData ) );
		}
	}

	if ( m_showingObjectId == Tools::Core::Generators::IGenerator::ms_wrongId )
	{
		m_mainWidget->setHtml( Resources::Views::ObjectInfoDefaultText );
	}

} // ObjectInfoView::setDescriptionForObject


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
