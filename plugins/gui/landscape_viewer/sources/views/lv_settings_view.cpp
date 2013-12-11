
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_settings_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


SettingsView::SettingsView()
	:	m_mainWidget( new QWidget() )
	,	m_tarrainMapVisibility( new QCheckBox( Resources::Views::TarrainMapVisibilityCheckboxName ) )
	,	m_viewTitle( Resources::Views::SettingsViewTitle )
{
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->setAlignment( Qt::AlignTop );

	mainLayout->addWidget( m_tarrainMapVisibility );

	m_mainWidget->setLayout( mainLayout );

} // SettingsView::SettingsView


/*---------------------------------------------------------------------------*/


SettingsView::~SettingsView()
{
} // SettingsView::~SettingsView


/*---------------------------------------------------------------------------*/


const QString&
SettingsView::getViewTitle() const
{
	return m_viewTitle;

} // SettingsView::getViewTitle


/*---------------------------------------------------------------------------*/


QWidget*
SettingsView::getViewWidget()
{
	return m_mainWidget.get();

} // SettingsView::getViewWidget


/*---------------------------------------------------------------------------*/


void
SettingsView::viewWasClosed()
{
	m_mainWidget.reset();

} // SettingsView::viewWasClosed


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
