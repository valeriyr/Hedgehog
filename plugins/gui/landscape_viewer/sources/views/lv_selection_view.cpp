
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_selection_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/object_graphics_info/lv_iobject_graphics_info.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_iobject_type.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"

//#include "lv_selection_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


SelectionView::SelectionView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::SelectionViewTitle )
	,	m_mainWidget( new QListWidget() )
{
	m_mainWidget->setViewMode( QListView::ViewMode::IconMode );

} // SelectionView::SelectionView


/*---------------------------------------------------------------------------*/


SelectionView::~SelectionView()
{
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
							,	Plugins::Core::LandscapeModel::Events::UnitsSelectionChanged::ms_type
							,	boost::bind( &SelectionView::onUnitsSelectionChanged, this, _1 ) );

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
SelectionView::onUnitsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	m_mainWidget->clear();

	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
		Plugins::Core::LandscapeModel::ILandscape::UnitsCollection selectedUnitsCollection;
		handle->getLandscape()->fetchSelectedUnits( selectedUnitsCollection );

		Plugins::Core::LandscapeModel::ILandscape::UnitsCollectionIterator
				selectedUnitsBegin = selectedUnitsCollection.begin()
			,	selectedUnitsEnd = selectedUnitsCollection.end();

		for ( ; selectedUnitsBegin != selectedUnitsEnd; ++selectedUnitsBegin )
		{
			boost::intrusive_ptr< IObjectGraphicsInfo >
				objectGraphicsInfo = m_environment.getObjectGraphicsInfo(	Resources::Landscape::SkinId
																		,	( *selectedUnitsBegin )->getType()->getName() );

			QListWidgetItem* listItem = new QListWidgetItem();

			listItem->setText( ( *selectedUnitsBegin )->getType()->getName() );
			listItem->setIcon( QIcon( m_environment.getPixmap( objectGraphicsInfo->getAtlasName(), objectGraphicsInfo->getFrameRect() ) ) );

			m_mainWidget->addItem( listItem );
		}
	}

} // SelectionView::onUnitsSelectionChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
