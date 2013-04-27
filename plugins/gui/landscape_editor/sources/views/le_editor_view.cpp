
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_editor_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"
#include "landscape_editor/sources/landscape_scene/le_landscape_scene.hpp"
#include "landscape_editor/sources/landscape_view/le_landscape_view.hpp"
#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/landscape_editor/le_ilandscape_editor_internal.hpp"

#include "le_editor_view.moc"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


EditorView::EditorView( const IEnvironment& _environment )
	:	QObject()
	,	m_environment( _environment )
	,	m_landscapeScene( new LandscapeScene( _environment ) )
	,	m_landscapeWidget( new LandscapeView( m_landscapeScene.get() ) )
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
	m_environment.setMinimapVisibilityRectSize( _visibleWidth, _visibleHeight );

} // EditorView::onLandscapeViewWasResized


/*---------------------------------------------------------------------------*/


void
EditorView::onVisibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight )
{
	m_environment.setMinimapVisibilityRectPosition( _visibleWidth, _visibleHeight );

} // EditorView::onVisibleRectOfLandscapeViewWasChanged


/*---------------------------------------------------------------------------*/


void
EditorView::onLandscapeWasChanged()
{
	m_environment.showLandscapeOnMinimap(
		*m_environment.getGUILandscapeEditor()->getEditableLandscape() );

} // EditorView::onLandscapeWasChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
