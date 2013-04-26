
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_editor_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_editor/sources/landscape_scene/le_landscape_scene.hpp"
#include "landscape_editor/sources/landscape_view/le_landscape_view.hpp"

#include "landscape_editor/sources/views_mediator/le_views_mediator.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


EditorView::EditorView( const IEnvironment& _environment, boost::shared_ptr< ViewsMediator > _viewsMediator )
	:	m_landscapeScene( new LandscapeScene( _environment ) )
	,	m_landscapeWidget( new LandscapeView( m_landscapeScene.get() ) )
	,	m_viewsMediator( _viewsMediator )
	,	m_viewTitle( Resources::Views::EditorViewDefaultTitle )
{
	QObject::connect(
			m_viewsMediator.get()
		,	SIGNAL( visibleRectOnMinimapWasChanged( const float, const float ) )
		,	m_landscapeWidget.get()
		,	SLOT( onVisibleRectOnMinimapWasChanged( const float, const float ) ) );

	QObject::connect(
			m_landscapeWidget.get()
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	m_viewsMediator.get()
		,	SLOT( onVisibleRectOfLandscapeViewWasChanged( const float, const float ) ) );

	QObject::connect(
			m_landscapeWidget.get()
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	m_viewsMediator.get()
		,	SLOT( onLandscapeViewWasResized( const float, const float ) ) );

	QObject::connect(
			m_landscapeScene.get()
		,	SIGNAL( landscapeWasChanged() )
		,	m_viewsMediator.get()
		,	SLOT( onLandscapeWasChanged() ) );

} // EditorView::EditorView


/*---------------------------------------------------------------------------*/


EditorView::~EditorView()
{
	QObject::disconnect(
			m_viewsMediator.get()
		,	SIGNAL( visibleRectOnMinimapWasChanged( const float, const float ) )
		,	m_landscapeWidget.get()
		,	SLOT( onVisibleRectOnMinimapWasChanged( const float, const float ) ) );

	QObject::disconnect(
			m_landscapeWidget.get()
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	m_viewsMediator.get()
		,	SLOT( onVisibleRectOfLandscapeViewWasChanged( const float, const float ) ) );

	QObject::disconnect(
			m_landscapeScene.get()
		,	SIGNAL( landscapeWasChanged() )
		,	m_viewsMediator.get()
		,	SLOT( onLandscapeWasChanged() ) );

	QObject::disconnect(
			m_landscapeWidget.get()
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	m_viewsMediator.get()
		,	SLOT( onLandscapeViewWasResized( const float, const float ) ) );

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
	m_landscapeScene->setDefaultLandscape();

} // EditorView::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
