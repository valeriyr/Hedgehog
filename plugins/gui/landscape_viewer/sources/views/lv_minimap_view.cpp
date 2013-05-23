
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_minimap_view.hpp"

#include "landscape_viewer/sources/widgets/lv_minimap_widget.hpp"
#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"
#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


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
MinimapView::landscapeWasOpened(
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscape > _landscape )
{
	m_minimapWidget->landscapeWasOpened( _landscape );

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
