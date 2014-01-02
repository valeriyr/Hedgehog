
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


ActionPanelView::ActionPanelView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_subscriber( _environment.createSubscriber() )
	,	m_viewTitle( Resources::Views::ActionPanelViewTitle )
	,	m_mainWidget( new QListWidget() )
{
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

	boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
		= m_environment.getCurrentLandscape();

	if ( handle->getLandscape() )
	{
	}

} // ActionPanelView::onObjectsSelectionChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
