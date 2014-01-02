
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_action_panel_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_iobject.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


class CreateObjectItem
	:	public QListWidgetItem
{

public:

	CreateObjectItem(
			const Core::LandscapeModel::IObject::IdType& _parentObjectId
		,	const Core::LandscapeModel::IObjectType::ObjectToCreateData& _createObjectData
		)
		:	m_parentObjectId( _parentObjectId )
		,	m_createObjectData( _createObjectData )
	{}

	const Core::LandscapeModel::IObject::IdType& getParentObjectId() const { return m_parentObjectId; }

	const Core::LandscapeModel::IObjectType::ObjectToCreateData& getObjectToCreate() const { return m_createObjectData; }

private:

	const Core::LandscapeModel::IObject::IdType m_parentObjectId;

	const Core::LandscapeModel::IObjectType::ObjectToCreateData m_createObjectData;
};


/*---------------------------------------------------------------------------*/


ActionPanelView::ActionPanelView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::ActionPanelViewTitle )
	,	m_mainWidget( new QListWidget() )
{
	m_mainWidget->setViewMode( QListView::IconMode );

} // ActionPanelView::ActionPanelView


/*---------------------------------------------------------------------------*/


ActionPanelView::~ActionPanelView()
{
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
							,	Plugins::Core::LandscapeModel::Events::ObjectsSelectionChanged::ms_type
							,	boost::bind( &ActionPanelView::onObjectsSelectionChanged, this, _1 ) );

} // ActionPanelView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ActionPanelView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	m_mainWidget->clear();

} // ActionPanelView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ActionPanelView::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	m_mainWidget->clear();

	Plugins::Core::LandscapeModel::IObjectType::ObjectToCreateDataCollection objectToCreate;
	Core::LandscapeModel::IObject::IdType parentObjectId = Core::LandscapeModel::IObject::ms_wrongId;

	{
		boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
			= m_environment.getCurrentLandscape();

		if ( handle->getLandscape() )
		{
			Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
			handle->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

			if ( !selectedObjectsCollection.empty() )
			{
				selectedObjectsCollection.front()->getType()->fetchObjectsThatCanCreate( objectToCreate );
				parentObjectId = selectedObjectsCollection.front()->getUniqueId();
			}
		}
	}

	Plugins::Core::LandscapeModel::IObjectType::ObjectToCreateDataCollectionIterator
			begin = objectToCreate.begin()
		,	end = objectToCreate.end();

	for ( ; begin != end; ++begin )
	{
		CreateObjectItem* listItem = new CreateObjectItem( parentObjectId, *begin );

		listItem->setText( QString( Resources::Views::CreateObjectLabelFormat ).arg( begin->m_objectName ) );
		listItem->setIcon( QIcon( m_environment.getPixmap( begin->m_objectName ) ) );

		m_mainWidget->addItem( listItem );
	}

} // ActionPanelView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
