
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_settings_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "lv_settings_view.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


SettingsView::SettingsView( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_mainWidget( new QWidget() )
	,	m_tarrainMapVisibility( new QCheckBox( Resources::Views::TarrainMapVisibilityCheckboxName ) )
	,	m_viewTitle( Resources::Views::SettingsViewTitle )
{
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->setAlignment( Qt::AlignTop );

	mainLayout->addWidget( m_tarrainMapVisibility );

	m_mainWidget->setLayout( mainLayout );

	m_tarrainMapVisibility->setChecked( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) );

	QObject::connect( m_tarrainMapVisibility, SIGNAL( clicked(bool) ), this, SLOT( onTarrainMapVisibilityChanged(bool) ) );

} // SettingsView::SettingsView


/*---------------------------------------------------------------------------*/


SettingsView::~SettingsView()
{
	QObject::disconnect( m_tarrainMapVisibility, SIGNAL( clicked(bool) ), this, SLOT( onTarrainMapVisibilityChanged(bool) ) );

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


void
SettingsView::onTarrainMapVisibilityChanged( bool _visibility )
{
	m_environment.setBool( Resources::Properties::TerrainMapVisibility, _visibility );

} // SettingsView::onTarrainMapVisibilityChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/