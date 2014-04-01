
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_object_info_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

#include "landscape_model/ih/components/lm_ihealth_component.hpp"
#include "landscape_model/ih/components/lm_imove_component.hpp"
#include "landscape_model/ih/components/lm_ilocate_component.hpp"
#include "landscape_model/ih/components/lm_iattack_component.hpp"
#include "landscape_model/ih/components/lm_iresource_holder_component.hpp"
#include "landscape_model/ih/components/lm_iresource_source_component.hpp"
#include "landscape_model/ih/components/lm_iresource_storage_component.hpp"

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
	,	m_showingObjectId( Core::LandscapeModel::Object::ms_wrongId )
{
	m_mainWidget->setReadOnly( true );

	setDescriptionForObject( Core::LandscapeModel::Object::ms_wrongId );

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
							,	Plugins::Core::LandscapeModel::Events::ObjectsSelectionChanged::ms_type
							,	boost::bind( &ObjectInfoView::onObjectsSelectionChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_type
							,	boost::bind( &ObjectInfoView::onObjectMoved, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectHealthChanged::ms_type
							,	boost::bind( &ObjectInfoView::onObjectDataChanged, this, _1 ) );

} // ObjectInfoView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	setDescriptionForObject( Core::LandscapeModel::Object::ms_wrongId );

} // ObjectInfoView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
		handle->getLandscapeModel()->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

		setDescriptionForObject(
				selectedObjectsCollection.empty()
			?	Core::LandscapeModel::Object::ms_wrongId
			:	selectedObjectsCollection.front()->getUniqueId() );
	}

} // ObjectInfoView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onObjectMoved( const Framework::Core::EventManager::Event& _event )
{
	const Plugins::Core::LandscapeModel::Object::Id objectId
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectMoved::ms_objectIdAttribute ).toInt();

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onObjectMoved


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::onObjectDataChanged( const Framework::Core::EventManager::Event& _event )
{
	const Plugins::Core::LandscapeModel::Object::Id objectId
		= _event.getAttribute( Plugins::Core::LandscapeModel::Events::ObjectHealthChanged::ms_objectIdAttribute ).toInt();

	if ( m_showingObjectId == objectId )
	{
		setDescriptionForObject( objectId );
	}

} // ObjectInfoView::onObjectDataChanged


/*---------------------------------------------------------------------------*/


void
ObjectInfoView::setDescriptionForObject( const Core::LandscapeModel::Object::Id& _objectId )
{
	m_showingObjectId = Core::LandscapeModel::Object::ms_wrongId;

	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		boost::shared_ptr< Core::LandscapeModel::Object > object = handle->getLandscapeModel()->getLandscape()->getObject( _objectId );

		if ( object )
		{
			m_showingObjectId = object->getUniqueId();

			boost::intrusive_ptr< Core::LandscapeModel::ILocateComponent > locateComponent
				= object->getComponent< Core::LandscapeModel::ILocateComponent >( Plugins::Core::LandscapeModel::ComponentId::Locate );
			boost::intrusive_ptr< Core::LandscapeModel::IHealthComponent > healthComponent
				= object->getComponent< Core::LandscapeModel::IHealthComponent >( Plugins::Core::LandscapeModel::ComponentId::Health );
			boost::intrusive_ptr< Core::LandscapeModel::IMoveComponent > moveComponent
				= object->getComponent< Core::LandscapeModel::IMoveComponent >( Plugins::Core::LandscapeModel::ComponentId::Move );
			boost::intrusive_ptr< Core::LandscapeModel::IAttackComponent > attackComponent
				= object->getComponent< Core::LandscapeModel::IAttackComponent >( Plugins::Core::LandscapeModel::ComponentId::Attack );
			boost::intrusive_ptr< Core::LandscapeModel::IResourceHolderComponent > resourceHolderComponent
				= object->getComponent< Core::LandscapeModel::IResourceHolderComponent >( Plugins::Core::LandscapeModel::ComponentId::ResourceHolder );
			boost::intrusive_ptr< Core::LandscapeModel::IResourceSourceComponent > resourceSourceComponent
				= object->getComponent< Core::LandscapeModel::IResourceSourceComponent >( Plugins::Core::LandscapeModel::ComponentId::ResourceSource );
			boost::intrusive_ptr< Core::LandscapeModel::IResourceStorageComponent > resourceStorageComponent
				= object->getComponent< Core::LandscapeModel::IResourceStorageComponent >( Plugins::Core::LandscapeModel::ComponentId::ResourceStorage );

			QString resourceHolderData;

			if ( resourceHolderComponent )
			{
				const Core::LandscapeModel::ResourcesData& maxResources
					= resourceHolderComponent->getStaticData().m_maxResourcesValue;

				Core::LandscapeModel::ResourcesData::ResourcesDataCollectionConstIterator
						begin = maxResources.m_data.begin()
					,	end = maxResources.m_data.end()
					,	it = maxResources.m_data.begin();

				for ( ; it != end; ++it )
				{
					if ( it != begin )
					{
						resourceHolderData += ", ";
					}

					resourceHolderData
						+= QString( Resources::Views::ResourcesHoldFormat )
								.arg( it->first )
								.arg( resourceHolderComponent->holdResources().getResourceValue( it->first ) )
								.arg( it->second );
				}
			}
			else
			{
				resourceHolderData = Resources::Views::NoneString;
			}

			QString resourceStorageData;

			if ( resourceStorageComponent )
			{
				Core::LandscapeModel::IResourceStorageComponent::StaticData::StoredResourcesCollectionIterator
						begin = resourceStorageComponent->getStaticData().m_storedResources.begin()
					,	end = resourceStorageComponent->getStaticData().m_storedResources.end()
					,	it = resourceStorageComponent->getStaticData().m_storedResources.begin();

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

			m_mainWidget->setHtml(
				QString( Resources::Views::ObjectInfoFormat )
					.arg( object->getName() )
					.arg( object->getUniqueId() )
					.arg( healthComponent ? QString::number( healthComponent->getHealth() ) : Resources::Views::NoneString )
					.arg( healthComponent ? QString::number( healthComponent->getStaticData().m_maximumHealth ) : Resources::Views::NoneString )
					.arg( moveComponent ? QString::number( moveComponent->getStaticData().m_movingSpeed ) : Resources::Views::NoneString )
					.arg( locateComponent->getLocation().x() )
					.arg( locateComponent->getLocation().y() )
					.arg( locateComponent->getStaticData().m_size.width() )
					.arg( locateComponent->getStaticData().m_size.height() )
					.arg( Core::LandscapeModel::Emplacement::toString( locateComponent->getStaticData().m_emplacement ) )
					.arg(	attackComponent
						?	QString( Resources::Views::DamageInfoFormat )
								.arg( attackComponent->getStaticData().m_minDamage )
								.arg( attackComponent->getStaticData().m_maxDamage )
						:	Resources::Views::NoneString )
						.arg( attackComponent ? QString::number( attackComponent->getStaticData().m_distance ) : Resources::Views::NoneString )
					.arg(	resourceSourceComponent
						?	QString( Resources::Views::ResourcesSourceFormat )
								.arg( resourceSourceComponent->getStaticData().m_resource )
								.arg( resourceSourceComponent->getResourceValue() )
						:	Resources::Views::NoneString )
					.arg( resourceHolderData )
					.arg( resourceStorageData ) );
		}
	}

	if ( m_showingObjectId == Core::LandscapeModel::Object::ms_wrongId )
	{
		m_mainWidget->setHtml( Resources::Views::ObjectInfoDefaultText );
	}

} // ObjectInfoView::setDescriptionForObject


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
