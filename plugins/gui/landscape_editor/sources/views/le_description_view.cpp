
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/views/le_description_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"

#include "landscape_editor/sources/landscape_editor_controller/le_ilandscape_editor_controller.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


DescriptionView::DescriptionView( const ILandscapeEditorController& _landscapeEditorController )
	:	m_landscapeEditorController( _landscapeEditorController )
	,	m_descriptionView( new QTextEdit() )
	,	m_viewTitle( Resources::Views::DescriptionViewTitle )
{
	m_descriptionView->setReadOnly( true );

	setDefaultDescription();

} // DescriptionView::DescriptionView


/*---------------------------------------------------------------------------*/


DescriptionView::~DescriptionView()
{
} // DescriptionView::~DescriptionView


/*---------------------------------------------------------------------------*/


const QString&
DescriptionView::getViewTitle() const
{
	return m_viewTitle;

} // DescriptionView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
DescriptionView::getViewWidget()
{
	return m_descriptionView.get();

} // DescriptionView::getViewWidget


/*---------------------------------------------------------------------------*/


void
DescriptionView::viewWasClosed()
{
	m_descriptionView.reset();

} // DescriptionView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
DescriptionView::landscapeWasOpened()
{
	m_descriptionView->setHtml(
		QString( Resources::Views::LandscapeDescriptionFormat )
			.arg( m_landscapeEditorController.getLandscapeFilePath() )
			.arg( m_landscapeEditorController.getEditableLandscape()->getWidth() )
			.arg( m_landscapeEditorController.getEditableLandscape()->getHeight() )
		);

} // DescriptionView::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
DescriptionView::landscapeWasClosed()
{
	setDefaultDescription();

} // DescriptionView::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
DescriptionView::setDefaultDescription()
{
	m_descriptionView->setHtml( Resources::Views::LandscapeDescriptionDefaultText );

} // DescriptionView::setDefaultDescription


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
