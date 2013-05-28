
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_landscape_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"
#include "landscape_viewer/sources/widgets/lv_landscape_widget.hpp"
#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeView::LandscapeView( const IEnvironment& _environment, const ViewsMediator& _viewsMediator )
	:	m_environment( _environment )
	,	m_viewsMediator( _viewsMediator )
	,	m_viewTitle( Resources::Views::LandscapeViewTitle )
	,	m_landscapeScene( new LandscapeScene( _environment ) )
	,	m_landscapeWidget( new LandscapeWidget( m_landscapeScene.get() ) )
	,	m_timer()
{
	QObject::connect(
			m_landscapeWidget.get()
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	&m_viewsMediator
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) ) );

	QObject::connect(
			m_landscapeWidget.get()
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	&m_viewsMediator
		,	SIGNAL( landscapeViewWasResized( const float, const float ) ) );

	QObject::connect(
			&m_viewsMediator
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) )
		,	m_landscapeWidget.get()
		,	SLOT( onChangeVisibleRect( const float, const float ) ) );

	QObject::connect( &m_timer, SIGNAL( timeout() ), m_landscapeScene.get(), SLOT( onUpdateTimerFired() ) );

} // LandscapeView::LandscapeView


/*---------------------------------------------------------------------------*/


LandscapeView::~LandscapeView()
{
	QObject::disconnect(
			m_landscapeWidget.get()
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	&m_viewsMediator
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) ) );

	QObject::disconnect(
			m_landscapeWidget.get()
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	&m_viewsMediator
		,	SIGNAL( landscapeViewWasResized( const float, const float ) ) );

	QObject::disconnect(
			&m_viewsMediator
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) )
		,	m_landscapeWidget.get()
		,	SLOT( onChangeVisibleRect( const float, const float ) ) );

	QObject::disconnect( &m_timer, SIGNAL( timeout() ), m_landscapeScene.get(), SLOT( onUpdateTimerFired() ) );

} // LandscapeView::~LandscapeView


/*---------------------------------------------------------------------------*/


const QString&
LandscapeView::getViewTitle() const
{
	return m_viewTitle;

} // LandscapeView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
LandscapeView::getViewWidget()
{
	return m_landscapeWidget.get();

} // LandscapeView::getViewWidget


/*---------------------------------------------------------------------------*/


void
LandscapeView::viewWasClosed()
{
	m_landscapeWidget.reset();
	m_landscapeScene.reset();

} // LandscapeView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
LandscapeView::landscapeWasOpened(
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscape > _landscape )
{
	m_landscapeScene->landscapeWasOpened( _landscape );
	m_landscapeWidget->wasResized();

	m_timer.start( ms_updatePeriod );

} // LandscapeView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeView::landscapeWasClosed()
{
	m_timer.stop();

	m_landscapeScene->landscapeWasClosed();

} // LandscapeView::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
