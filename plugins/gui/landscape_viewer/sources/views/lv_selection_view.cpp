
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_selection_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/graphics_info_cache/lv_igraphics_info_cache.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"

#include "lv_selection_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


class SelectionViewItem
	:	public QListWidgetItem
{

public:

	SelectionViewItem( const Core::LandscapeModel::Object::Id& _id )
		:	m_id( _id )
	{}

	const Core::LandscapeModel::Object::Id& getUniqueId() const { return m_id; }

private:

	const Core::LandscapeModel::Object::Id m_id;
};


/*---------------------------------------------------------------------------*/

SelectionView::SelectionView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::SelectionViewTitle )
	,	m_mainWidget( new QListWidget() )
{
	m_mainWidget->setViewMode( QListView::IconMode );

	QObject::connect(
			m_mainWidget.get()
		,	SIGNAL( itemClicked( QListWidgetItem* ) )
		,	this
		,	SLOT( onItemClicked( QListWidgetItem* ) ) );

} // SelectionView::SelectionView


/*---------------------------------------------------------------------------*/


SelectionView::~SelectionView()
{
	QObject::disconnect(
			m_mainWidget.get()
		,	SIGNAL( itemClicked( QListWidgetItem* ) )
		,	this
		,	SLOT( onItemClicked( QListWidgetItem* ) ) );

} // SelectionView::~SelectionView


/*---------------------------------------------------------------------------*/


const QString&
SelectionView::getViewTitle() const
{
	return m_viewTitle;

} // SelectionView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
SelectionView::getViewWidget()
{
	return m_mainWidget.get();

} // SelectionView::getViewWidget


/*---------------------------------------------------------------------------*/


void
SelectionView::viewWasClosed()
{
	m_mainWidget.reset();

} // SelectionView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
SelectionView::landscapeWasOpened()
{
	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectsSelectionChanged::ms_type
							,	boost::bind( &SelectionView::onObjectsSelectionChanged, this, _1 ) );

} // SelectionView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
SelectionView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	m_mainWidget->clear();

} // SelectionView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
SelectionView::onItemClicked( QListWidgetItem* _item )
{
	SelectionViewItem* listItem = dynamic_cast< SelectionViewItem* >( _item );
	assert( listItem );

	m_environment.lockModel()->getLandscapeModel()->selectObject( listItem->getUniqueId() );

} // SelectionView::onItemClicked


/*---------------------------------------------------------------------------*/


void
SelectionView::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	m_mainWidget->clear();

	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker > handle
		= m_environment.lockModel();

	if ( handle->getLandscapeModel()->getLandscape() )
	{
		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollection selectedObjectsCollection;
		handle->getLandscapeModel()->getLandscape()->fetchSelectedObjects( selectedObjectsCollection );

		Plugins::Core::LandscapeModel::ILandscape::ObjectsCollectionIterator
				selectedObjectsBegin = selectedObjectsCollection.begin()
			,	selectedObjectsEnd = selectedObjectsCollection.end();

		for ( ; selectedObjectsBegin != selectedObjectsEnd; ++selectedObjectsBegin )
		{
			SelectionViewItem* listItem = new SelectionViewItem( ( *selectedObjectsBegin )->getUniqueId() );

			listItem->setText( ( *selectedObjectsBegin )->getName() );
			listItem->setIcon( QIcon( m_environment.getPixmap( ( *selectedObjectsBegin )->getName() ) ) );

			m_mainWidget->addItem( listItem );
		}
	}

} // SelectionView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
