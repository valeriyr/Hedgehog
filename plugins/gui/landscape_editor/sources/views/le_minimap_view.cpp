
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_minimap_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_editor/sources/minimap_widget/le_minimap_widget.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


MinimapView::MinimapView(
		const ILandscapeEditorController& _landscapeEditorController
	,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager
	)
	:	m_landscapeEditorController( _landscapeEditorController )
	,	m_imagesManager( _imagesManager )
	,	m_minimapWidget( new MinimapWidget( _landscapeEditorController, _imagesManager ) )
	,	m_viewTitle( Resources::Views::MinimapViewTitle )
{
} // MinimapView::MinimapView


/*---------------------------------------------------------------------------*/


MinimapView::~MinimapView()
{
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
	m_minimapWidget->landscapeWasOpened();

} // MinimapView::landscapeWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/