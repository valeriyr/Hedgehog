
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_editor_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_editor/sources/landscape_widget/le_landscape_widget.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


EditorView::EditorView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_editorMainWidget( new QScrollArea() )
	,	m_landscapeWidget( new LandscapeWidget( _environment ) )
	,	m_viewTitle( Resources::Views::EditorViewDefaultTitle )
{
	m_editorMainWidget->setWidget( m_landscapeWidget );

} // EditorView::EditorView


/*---------------------------------------------------------------------------*/


EditorView::~EditorView()
{
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
	return m_editorMainWidget.get();

} // EditorView::getViewWidget


/*---------------------------------------------------------------------------*/


void
EditorView::viewWasClosed()
{
	m_editorMainWidget.reset();

} // EditorView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
EditorView::landscapeWasOpened()
{
	m_landscapeWidget->landscapeWasOpened();

} // EditorView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
EditorView::landscapeWasClosed()
{
	m_landscapeWidget->setDefaultLandscape();
	m_editorMainWidget->update();

} // EditorView::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
