
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_action_panel_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/h/lm_object.hpp"
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
			const Core::LandscapeModel::Object::UniqueId& _parentObjectId
		,	boost::shared_ptr< const Core::LandscapeModel::BuildObjectsData > _buildData
		)
		:	m_parentObjectId( _parentObjectId )
		,	m_buildData( _buildData )
	{}

	const Core::LandscapeModel::Object::UniqueId& getParentObjectId() const { return m_parentObjectId; }

	boost::shared_ptr< const Core::LandscapeModel::BuildObjectsData > getBuildObjectsData() const { return m_buildData; }

private:

	const Core::LandscapeModel::Object::UniqueId m_parentObjectId;

	boost::shared_ptr< const Core::LandscapeModel::BuildObjectsData > m_buildData;
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

	boost::intrusive_ptr< Core::LandscapeModel::IBuilderComponent > builderComponent;
	Core::LandscapeModel::Object::UniqueId parentObjectId = Core::LandscapeModel::Object::ms_wrongId;

	{
		boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
			= m_environment.getCurrentLandscape();

		if ( handle->getLandscape() )
		{
			Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
			handle->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

			if ( !selectedObjectsCollection.empty() )
			{
				builderComponent = selectedObjectsCollection.front()->getComponent< Core::LandscapeModel::IBuilderComponent >( Plugins::Core::LandscapeModel::ComponentId::Builder );
				parentObjectId = selectedObjectsCollection.front()->getUniqueId();
			}
		}
	}

	if ( builderComponent )
	{
		Core::LandscapeModel::BuilderComponentStaticData::BuildObjectsDataCollectionIterator
				begin = builderComponent->getStaticData().m_buildObjects.begin()
			,	end = builderComponent->getStaticData().m_buildObjects.end();

		for ( ; begin != end; ++begin )
		{
			CreateObjectItem* listItem = new CreateObjectItem( parentObjectId, *begin );

			listItem->setText( QString( Resources::Views::CreateObjectLabelFormat ).arg( ( *begin )->m_objectName ) );
			listItem->setIcon( QIcon( m_environment.getPixmap( ( *begin )->m_objectName ) ) );

			m_mainWidget->addItem( listItem );
		}
	}

} // ActionPanelView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
