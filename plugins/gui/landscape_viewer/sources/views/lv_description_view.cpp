
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_description_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


DescriptionView::DescriptionView( const ILandscapeEditorInternal& _landscapeEditor )
	:	m_landscapeEditor( _landscapeEditor )
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
			.arg( m_landscapeEditor.getLandscapeFilePath() )
			.arg( m_landscapeEditor.getEditableLandscape()->getWidth() )
			.arg( m_landscapeEditor.getEditableLandscape()->getHeight() )
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

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
