
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_editor_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/widgets/lv_landscape_editor_scene.hpp"
#include "landscape_viewer/sources/widgets/lv_landscape_editor_widget.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "lv_editor_view.moc"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


EditorView::EditorView( const IEnvironment& _environment )
	:	QObject()
	,	m_environment( _environment )
	,	m_landscapeScene( new LandscapeEditorScene( _environment ) )
	,	m_landscapeWidget( new LandscapeEditorWidget( m_landscapeScene.get() ) )
	,	m_viewTitle( Resources::Views::EditorViewDefaultTitle )
{
	QObject::connect(
			m_landscapeWidget.get()
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	this
		,	SLOT( onVisibleRectOfLandscapeViewWasChanged( const float, const float ) ) );

	QObject::connect(
			m_landscapeWidget.get()
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	this
		,	SLOT( onLandscapeViewWasResized( const float, const float ) ) );

	QObject::connect(
			m_landscapeScene.get()
		,	SIGNAL( landscapeWasChanged() )
		,	this
		,	SLOT( onLandscapeWasChanged() ) );

} // EditorView::EditorView


/*---------------------------------------------------------------------------*/


EditorView::~EditorView()
{
	QObject::disconnect(
			m_landscapeWidget.get()
		,	SIGNAL( visibleRectOfLandscapeViewWasChanged( const float, const float ) )
		,	this
		,	SLOT( onVisibleRectOfLandscapeViewWasChanged( const float, const float ) ) );

	QObject::disconnect(
			m_landscapeWidget.get()
		,	SIGNAL( landscapeViewWasResized( const float, const float ) )
		,	this
		,	SLOT( onLandscapeViewWasResized( const float, const float ) ) );

	QObject::disconnect(
			m_landscapeScene.get()
		,	SIGNAL( landscapeWasChanged() )
		,	this
		,	SLOT( onLandscapeWasChanged() ) );

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


void
EditorView::setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight )
{
	m_landscapeWidget->changeVisibleRect( _relVisibleWidth, _relVisibleHeight );

} // EditorView::setVisibilityRectPosition


/*---------------------------------------------------------------------------*/


void
EditorView::onLandscapeViewWasResized( const float _visibleWidth, const float _visibleHeight )
{
	// m_environment.setMinimapVisibilityRectSize( _visibleWidth, _visibleHeight );

} // EditorView::onLandscapeViewWasResized


/*---------------------------------------------------------------------------*/


void
EditorView::onVisibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight )
{
	// m_environment.setMinimapVisibilityRectPosition( _visibleWidth, _visibleHeight );

} // EditorView::onVisibleRectOfLandscapeViewWasChanged


/*---------------------------------------------------------------------------*/


void
EditorView::onLandscapeWasChanged()
{
	/*if ( m_environment.getGUILandscapeEditor()->getEditableLandscape() )
	{
		m_environment.showLandscapeOnMinimap(
			*m_environment.getGUILandscapeEditor()->getEditableLandscape() );
	}*/

} // EditorView::onLandscapeWasChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
