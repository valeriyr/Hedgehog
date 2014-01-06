
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_object_status_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


ObjectStatusView::ObjectStatusView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::ObjectStatusViewTitle )
	,	m_mainWidget( new QListWidget() )
{
	m_mainWidget->setViewMode( QListView::IconMode );

} // ObjectStatusView::ObjectStatusView


/*---------------------------------------------------------------------------*/


ObjectStatusView::~ObjectStatusView()
{
} // ObjectStatusView::~ObjectStatusView


/*---------------------------------------------------------------------------*/


const QString&
ObjectStatusView::getViewTitle() const
{
	return m_viewTitle;

} // ObjectStatusView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
ObjectStatusView::getViewWidget()
{
	return m_mainWidget.get();

} // ObjectStatusView::getViewWidget


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::viewWasClosed()
{
	m_mainWidget.reset();

} // ObjectStatusView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::landscapeWasOpened()
{
	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::ObjectsSelectionChanged::ms_type
							,	boost::bind( &ObjectStatusView::onObjectsSelectionChanged, this, _1 ) );

} // ObjectStatusView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::landscapeWasClosed()
{
	m_subscriber.unsubscribe();
	m_mainWidget->clear();

} // ObjectStatusView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectStatusView::onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event )
{
	m_mainWidget->clear();

	{
		boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
			= m_environment.getCurrentLandscape();

		if ( handle->getLandscape() )
		{
		}
	}

} // ObjectStatusView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
