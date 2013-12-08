
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_minimap_view.hpp"

#include "landscape_viewer/sources/widgets/lv_minimap_widget.hpp"
#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"
#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


MinimapView::MinimapView( const IEnvironment& _environment, const ViewsMediator& _viewsMediator )
	:	m_environment( _environment )
	,	m_viewsMediator( _viewsMediator )
	,	m_minimapWidget( new MinimapWidget( _environment ) )
	,	m_viewTitle( Resources::Views::MinimapViewTitle )
{
	QObject::connect(
			m_minimapWidget.get()
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) )
		,	&m_viewsMediator
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) ) );

	QObject::connect(
			&m_viewsMediator
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	m_minimapWidget.get()
		,	SLOT( onChangeVisibilityRectPosition( const float, const float ) ) );

	QObject::connect(
			&m_viewsMediator
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	m_minimapWidget.get()
		,	SLOT( onChangeVisibilityRectSize( const float, const float ) ) );

	QObject::connect(
			&m_viewsMediator
		,	SIGNAL( landscapeWasChanged() )
		,	m_minimapWidget.get()
		,	SLOT( onUpdateView() ) );

	QObject::connect(
			&m_viewsMediator
		,	SIGNAL( updateTimerFired() )
		,	m_minimapWidget.get()
		,	SLOT( onUpdateTimerFired() ) );

} // MinimapView::MinimapView


/*---------------------------------------------------------------------------*/


MinimapView::~MinimapView()
{
	QObject::disconnect(
			m_minimapWidget.get()
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) )
		,	&m_viewsMediator
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) ) );

	QObject::disconnect(
			&m_viewsMediator
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	m_minimapWidget.get()
		,	SLOT( onChangeVisibilityRectPosition( const float, const float ) ) );

	QObject::disconnect(
			&m_viewsMediator
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	m_minimapWidget.get()
		,	SLOT( onChangeVisibilityRectSize( const float, const float ) ) );

	QObject::disconnect(
			&m_viewsMediator
		,	SIGNAL( landscapeWasChanged() )
		,	m_minimapWidget.get()
		,	SLOT( onUpdateView() ) );

	QObject::disconnect(
			&m_viewsMediator
		,	SIGNAL( updateTimerFired() )
		,	m_minimapWidget.get()
		,	SLOT( onUpdateTimerFired() ) );

} // MinimapView::~MinimapView


/*---------------------------------------------------------------------------*/


const QString&
MinimapView::getViewTitle() const
{
	return m_viewTitle;

} // MinimapView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
MinimapView::getViewWidget()
{
	return m_minimapWidget.get();

} // MinimapView::getViewWidget


/*---------------------------------------------------------------------------*/


void
MinimapView::viewWasClosed()
{
	m_minimapWidget.reset();

} // MinimapView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
MinimapView::landscapeWasOpened()
{
	m_minimapWidget->landscapeWasOpened();

} // MinimapView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
MinimapView::landscapeWasClosed()
{
	m_minimapWidget->landscapeWasClosed();

} // MinimapView::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
