
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_editor_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"
#include "landscape_editor/sources/landscape_scene/le_landscape_scene.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


EditorView::EditorView(
		const ILandscapeEditorController& _landscapeEditorController
	,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager )
	:	m_landscapeScene( new LandscapeScene( _landscapeEditorController, _imagesManager ) )
	,	m_landscapeWidget( new QGraphicsView( m_landscapeScene.get() ) )
	,	m_viewTitle( Resources::Views::EditorViewDefaultTitle )
{
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
