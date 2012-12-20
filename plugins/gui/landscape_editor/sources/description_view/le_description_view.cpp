
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/description_view/le_description_view.hpp"

#include "landscape_editor/sources/internal_resources/le_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


DescriptionView::DescriptionView()
	:	m_descriptionView( new QTextEdit() )
	,	m_viewTitle( Resources::Views::DescriptionViewTitle )
{
	m_descriptionView->setReadOnly( true );

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
DescriptionView::getViewWidget() const
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

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
