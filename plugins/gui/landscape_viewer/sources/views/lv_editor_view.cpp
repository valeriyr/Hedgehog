
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_editor_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/widgets/lv_landscape_editor_scene.hpp"
#include "landscape_viewer/sources/widgets/lv_landscape_widget.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


EditorView::EditorView( const IEnvironment& _environment, const ViewsMediator& _viewsMediator )
	:	m_environment( _environment )
	,	m_viewsMediator( _viewsMediator )
	,	m_landscapeScene( new LandscapeEditorScene( _environment ) )
	,	m_landscapeWidget( new LandscapeWidget( m_landscapeScene.get() ) )
	,	m_viewTitle( Resources::Views::EditorViewDefaultTitle )
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
			m_landscapeWidget.get()
		,	SIGNAL( mousePossitionWasChanged( const QPointF& ) )
		,	m_landscapeScene.get()
		,	SLOT( onMousePossitionWasChanged( const QPointF& ) ) );

	QObject::connect(
			m_landscapeScene.get()
		,	SIGNAL( landscapeWasChanged() )
		,	&m_viewsMediator
		,	SIGNAL( landscapeWasChanged() ) );

	QObject::connect(
			&m_viewsMediator
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) )
		,	m_landscapeWidget.get()
		,	SLOT( onChangeVisibleRect( const float, const float ) ) );

	QObject::connect(
			&m_viewsMediator
		,	SIGNAL( currentSurfaceItemWasChanged( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& ) )
		,	m_landscapeScene.get()
		,	SLOT( onChangeSurfaceItem( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& ) ) );

} // EditorView::EditorView


/*---------------------------------------------------------------------------*/


EditorView::~EditorView()
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
			m_landscapeWidget.get()
		,	SIGNAL( mousePossitionWasChanged( const QPointF& ) )
		,	m_landscapeScene.get()
		,	SLOT( onMousePossitionWasChanged( const QPointF& ) ) );

	QObject::disconnect(
			m_landscapeScene.get()
		,	SIGNAL( landscapeWasChanged() )
		,	&m_viewsMediator
		,	SIGNAL( landscapeWasChanged() ) );

	QObject::disconnect(
			&m_viewsMediator
		,	SIGNAL( visibilityRectChangedPosition( const float, const float ) )
		,	m_landscapeWidget.get()
		,	SLOT( onChangeVisibleRect( const float, const float ) ) );

	QObject::disconnect(
			&m_viewsMediator
		,	SIGNAL( currentSurfaceItemWasChanged( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& ) )
		,	m_landscapeScene.get()
		,	SLOT( onChangeSurfaceItem( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& ) ) );

} // EditorView::~EditorView


/*---------------------------------------------------------------------------*/


const QString&
EditorView::getViewTitle() const
{
	return m_viewTitle;

} // EditorView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
EditorView::getViewWidget()
{
	return m_landscapeWidget.get();

} // EditorView::getViewWidget


/*---------------------------------------------------------------------------*/


void
EditorView::viewWasClosed()
{
	m_landscapeWidget.reset();
	m_landscapeScene.reset(); 

} // EditorView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
EditorView::landscapeWasOpened()
{
	m_landscapeScene->landscapeWasOpened();
	m_landscapeWidget->wasResized();

} // EditorView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
EditorView::landscapeWasClosed()
{
	m_landscapeScene->landscapeWasClosed();

} // EditorView::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
