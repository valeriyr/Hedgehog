
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/editor_view/le_editor_view.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


EditorView::EditorView()
	:	m_editorView( new QTextEdit() )
	,	m_viewTitle( "'Landscape file name' should be here" )
{
	m_editorView->setReadOnly( true );

} // EditorView::EditorView


/*---------------------------------------------------------------------------*/


EditorView::~EditorView()
{
} // EditorView::~EditorView


/*---------------------------------------------------------------------------*/


const std::string&
EditorView::getViewTitle() const
{
	return m_viewTitle;

} // EditorView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
EditorView::getViewWidget() const
{
	return m_editorView.get();

} // EditorView::getViewWidget


/*---------------------------------------------------------------------------*/


void
EditorView::viewWasClosed()
{
	m_editorView.reset();

} // EditorView::viewWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
