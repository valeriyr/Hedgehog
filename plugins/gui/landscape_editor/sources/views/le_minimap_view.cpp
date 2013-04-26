
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_minimap_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"
#include "landscape_editor/sources/minimap_widget/le_minimap_widget.hpp"

#include "landscape_editor/sources/views_mediator/le_views_mediator.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


MinimapView::MinimapView(
		const IEnvironment& _environment
	,	boost::shared_ptr< ViewsMediator > _viewsMediator
	)
	:	m_minimapWidget( new MinimapWidget( _environment ) )
	,	m_viewsMediator( _viewsMediator )
	,	m_viewTitle( Resources::Views::MinimapViewTitle )
{
	QObject::connect(
			m_minimapWidget.get()
		,	SIGNAL( visibleAreaRectWasChanged( const float, const float ) )
		,	m_viewsMediator.get()
		,	SLOT( onVisibleRectOnMinimapWasChanged( const float, const float ) ) );

	QObject::connect(
			m_viewsMediator.get()
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	m_minimapWidget.get()
		,	SLOT( onLandscapeViewWasResized( const float, const float ) ) );

	QObject::connect(
			m_viewsMediator.get()
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	m_minimapWidget.get()
		,	SLOT( onVisibleRectOfLandscapeViewWasChanged( const float, const float ) ) );

	QObject::connect(
			m_viewsMediator.get()
		,	SIGNAL( landscapeWasChanged() )
		,	m_minimapWidget.get()
		,	SLOT( onLandscapeWasChanged() ) );

} // MinimapView::MinimapView


/*---------------------------------------------------------------------------*/


MinimapView::~MinimapView()
{
	QObject::disconnect(
			m_minimapWidget.get()
		,	SIGNAL( visibleAreaRectWasChanged( const float, const float ) )
		,	m_viewsMediator.get()
		,	SLOT( onVisibleRectOnMinimapWasChanged( const float, const float ) ) );

	QObject::disconnect(
			m_viewsMediator.get()
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	m_minimapWidget.get()
		,	SLOT( onLandscapeSceneLoaded( const float, const float ) ) );

	QObject::disconnect(
			m_viewsMediator.get()
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	m_minimapWidget.get()
		,	SLOT( onVisibleRectOfLandscapeViewWasChanged( const float, const float ) ) );

	QObject::disconnect(
			m_viewsMediator.get()
		,	SIGNAL( landscapeWasChanged() )
		,	m_minimapWidget.get()
		,	SLOT( onLandscapeWasChanged() ) );

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
	m_minimapWidget->setDefaultLandscape();

} // MinimapView::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
