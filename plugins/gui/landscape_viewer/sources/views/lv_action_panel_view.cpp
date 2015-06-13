
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_action_panel_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

#include "landscape_model/h/lm_game_object.hpp"
#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"

#include "lv_action_panel_view.moc"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


class TrainObjectItem
	:	public QListWidgetItem
{

public:

	TrainObjectItem(
			const Tools::Core::Generators::IGenerator::IdType& _parentObjectId
		,	const QString& _targetObjectName
		)
		:	m_parentObjectId( _parentObjectId )
		,	m_targetObjectName( _targetObjectName )
	{}

	const Tools::Core::Generators::IGenerator::IdType& getParentObjectId() const { return m_parentObjectId; }

	const QString& getTargetObjectName() const { return m_targetObjectName; }

private:

	const Tools::Core::Generators::IGenerator::IdType m_parentObjectId;

	const QString m_targetObjectName;
};

/*---------------------------------------------------------------------------*/


class BuildObjectItem
	:	public QListWidgetItem
{

public:

	BuildObjectItem(
			const Tools::Core::Generators::IGenerator::IdType& _builderId
		,	const QString& _targetObjectName
		)
		:	m_builderId( _builderId )
		,	m_targetObjectName( _targetObjectName )
	{}

	const Tools::Core::Generators::IGenerator::IdType& getBuilderId() const { return m_builderId; }

	const QString& getTargetObjectName() const { return m_targetObjectName; }

private:

	const Tools::Core::Generators::IGenerator::IdType m_builderId;

	const QString m_targetObjectName;
};

/*---------------------------------------------------------------------------*/


ActionPanelView::ActionPanelView( const IEnvironment& _environment, ViewsMediator& _viewsMediator )
	:	m_environment( _environment )
	,	m_viewsMediator( _viewsMediator )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::ActionPanelViewTitle )
	,	m_mainWidget( new QListWidget() )
	,	m_showingObjectId( Tools::Core::Generators::IGenerator::ms_wrongId )
{
	m_mainWidget->setViewMode( QListView::IconMode );

	QObject::connect(
			m_mainWidget.get()
		,	SIGNAL( itemClicked( QListWidgetItem* ) )
		,	this
		,	SLOT( onItemClicked( QListWidgetItem* ) ) );

} // ActionPanelView::ActionPanelView


/*---------------------------------------------------------------------------*/


ActionPanelView::~ActionPanelView()
{
	QObject::disconnect(
			m_mainWidget.get()
		,	SIGNAL( itemClicked( QListWidgetItem* ) )
		,	this
		,	SLOT( onItemClicked( QListWidgetItem* ) ) );

} // ActionPanelView::~ActionPanelView


/*---------------------------------------------------------------------------*/


const QString&
ActionPanelView::getViewTitle() const
{
	return m_viewTitle;

} // ActionPanelView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
ActionPanelView::getViewWidget()
{
	return m_mainWidget.get();

} // ActionPanelView::getViewWidget


/*---------------------------------------------------------------------------*/


void
ActionPanelView::viewWasClosed()
{
	m_mainWidget.reset();

} // ActionPanelView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
ActionPanelView::landscapeWasOpened()
{
	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectsSelectionChanged::Type
							,	boost::bind( &ActionPanelView::onObjectsSelectionChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Core::LandscapeModel::Events::ObjectStateChanged::Type
							,	boost::bind( &ActionPanelView::onObjectStateChanged, this, _1 ) );

} // ActionPanelView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ActionPanelView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	updateView( Tools::Core::Generators::IGenerator::ms_wrongId );

} // ActionPanelView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ActionPanelView::onItemClicked( QListWidgetItem* _item )
{
	TrainObjectItem* trainListItem = dynamic_cast< TrainObjectItem* >( _item );

	if ( trainListItem )
	{
		m_environment.lockModel()->getLandscapeModel()->pushCommand(
			Core::LandscapeModel::Command( Core::LandscapeModel::CommandId::TrainObject )
				.pushArgument( trainListItem->getParentObjectId() )
				.pushArgument( trainListItem->getTargetObjectName() ) );
		return;
	}

	BuildObjectItem* buildListItem = dynamic_cast< BuildObjectItem* >( _item );

	if ( buildListItem )
	{
		m_viewsMediator.buildObjectButtonPressed( buildListItem->getBuilderId(), buildListItem->getTargetObjectName() );
		return;
	}

} // ActionPanelView::onItemClicked


/*---------------------------------------------------------------------------*/


void
ActionPanelView::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
		handle->getLandscapeModel()->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

		if ( selectedObjectsCollection.empty() )
		{
			updateView( Tools::Core::Generators::IGenerator::ms_wrongId );
		}
		else
		{
			updateView( selectedObjectsCollection.front()->getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::ObjectUniqueIdKey ) );
		}
	}

} // ActionPanelView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/


void
ActionPanelView::onObjectStateChanged( const Framework::Core::EventManager::Event& _event )
{
	const Tools::Core::Generators::IGenerator::IdType objectId
		= _event.getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::Events::ObjectStateChanged::ObjectIdAttribute );

	if ( m_showingObjectId == objectId )
		updateView( objectId );

} // ActionPanelView::onObjectStateChanged


/*---------------------------------------------------------------------------*/


void
ActionPanelView::updateView( const Tools::Core::Generators::IGenerator::IdType& _objectId )
{
	m_mainWidget->clear();

	m_showingObjectId = _objectId;

	if ( _objectId == Tools::Core::Generators::IGenerator::ms_wrongId )
		return;

	Tools::Core::Object::Ptr trainComponent;
	Tools::Core::Object::Ptr buildComponent;

	Tools::Core::Generators::IGenerator::IdType parentObjectId = Tools::Core::Generators::IGenerator::ms_wrongId;

	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		boost::shared_ptr< Core::LandscapeModel::GameObject > object
			= handle->getLandscapeModel()->getLandscape()->getObject( _objectId );

		const Tools::Core::Generators::IGenerator::IdType objectId
			= object->getMember< Tools::Core::Generators::IGenerator::IdType >( Core::LandscapeModel::ObjectUniqueIdKey );
		const Core::LandscapeModel::ObjectState::Enum objectState
			= object->getMember< Core::LandscapeModel::ObjectState::Enum >( Core::LandscapeModel::ObjectStateKey );

		if (	objectState == Core::LandscapeModel::ObjectState::Dying
			||	objectState == Core::LandscapeModel::ObjectState::UnderConstruction
			||	!handle->getLandscapeModel()->isMyObject( object ) )
			return;

		trainComponent = object->getMember< Tools::Core::Object::Ptr >( Core::LandscapeModel::TrainComponent::Name );
		buildComponent = object->getMember< Tools::Core::Object::Ptr >( Core::LandscapeModel::BuildComponent::Name );

		parentObjectId = objectId;
	}

	if ( trainComponent )
	{
		Core::LandscapeModel::TrainComponent::StaticData::Data::TrainDataCollectionIterator
				begin = trainComponent->getMember< Core::LandscapeModel::TrainComponent::StaticData::Data::Ptr >(
					Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::TrainComponent::StaticData::DataKey ) )->m_trainObjects.begin()
			,	end = trainComponent->getMember< Core::LandscapeModel::TrainComponent::StaticData::Data::Ptr >(
					Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::TrainComponent::StaticData::DataKey ) )->m_trainObjects.end();

		for ( ; begin != end; ++begin )
		{
			TrainObjectItem* listItem = new TrainObjectItem( parentObjectId, begin->first );

			listItem->setText( QString( Resources::Views::CreateObjectLabelFormat ).arg( begin->first ) );
			listItem->setIcon( QIcon( m_environment.getPixmap( begin->first ) ) );

			m_mainWidget->addItem( listItem );
		}
	}
	else if ( buildComponent )
	{
		Core::LandscapeModel::BuildComponent::StaticData::Data::BuildDataCollectionIterator
				begin = buildComponent->getMember< Core::LandscapeModel::BuildComponent::StaticData::Data::Ptr >(
					Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::BuildComponent::StaticData::DataKey ) )->m_buildDatas.begin()
			,	end = buildComponent->getMember< Core::LandscapeModel::BuildComponent::StaticData::Data::Ptr >(
					Core::LandscapeModel::StaticDataTools::generateName( Core::LandscapeModel::BuildComponent::StaticData::DataKey ) )->m_buildDatas.end();

		for ( ; begin != end; ++begin )
		{
			BuildObjectItem* listItem = new BuildObjectItem( parentObjectId, begin->first );

			listItem->setText( QString( Resources::Views::CreateObjectLabelFormat ).arg( begin->first ) );
			listItem->setIcon( QIcon( m_environment.getPixmap( begin->first ) ) );

			m_mainWidget->addItem( listItem );
		}
	}

} // ActionPanelView::updateView


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
