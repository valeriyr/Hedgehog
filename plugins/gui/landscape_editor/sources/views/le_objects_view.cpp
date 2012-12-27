
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_objects_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


ObjectsView::ObjectsView( const ILandscapeEditorController& _landscapeEditorController )
	:	m_landscapeEditorController( _landscapeEditorController )
	,	m_objectsView( new QTextEdit() )
	,	m_viewTitle( Resources::Views::ObjectsViewTitle )
{
	m_objectsView->setReadOnly( true );

} // ObjectsView::ObjectsView


/*---------------------------------------------------------------------------*/


ObjectsView::~ObjectsView()
{
} // ObjectsView::~ObjectsView


/*---------------------------------------------------------------------------*/


const QString&
ObjectsView::getViewTitle() const
{
	return m_viewTitle;

} // ObjectsView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
ObjectsView::getViewWidget()
{
	return m_objectsView.get();

} // ObjectsView::getViewWidget


/*---------------------------------------------------------------------------*/


void
ObjectsView::viewWasClosed()
{
	m_objectsView.reset();

} // ObjectsView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
ObjectsView::landscapeWasOpened()
{
} // ObjectsView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
ObjectsView::landscapeWasClosed()
{
} // ObjectsView::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
