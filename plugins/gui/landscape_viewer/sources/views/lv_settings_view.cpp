
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
	,	m_updateMinimap( new QCheckBox( Resources::Views::UpdateMinimapCheckboxName ) )
	,	m_skinId( new QComboBox() )
	,	m_viewTitle( Resources::Views::SettingsViewTitle )
{
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->setAlignment( Qt::AlignTop );

	QHBoxLayout* skinIdLayout = new QHBoxLayout();

	m_skinId->addItem( "summer" );
	m_skinId->addItem( "winter" );
	m_skinId->addItem( "wasteland" );

	m_skinId->setCurrentText( m_environment.getString( Resources::Properties::SkinId ) );

	QLabel* skinIdLabel = new QLabel( Resources::Views::SkinIdLabel );
	skinIdLabel->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );

	skinIdLayout->addWidget( skinIdLabel );
	skinIdLayout->addWidget( m_skinId );

	mainLayout->addWidget( m_tarrainMapVisibility );
	mainLayout->addLayout( skinIdLayout );
	mainLayout->addWidget( m_updateMinimap );

	m_mainWidget->setLayout( mainLayout );

	m_tarrainMapVisibility->setChecked( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) );

	m_updateMinimap->setChecked( m_environment.getBool( Resources::Properties::UpdateMinimap ) );

	QObject::connect( m_tarrainMapVisibility, SIGNAL( clicked(bool) ), this, SLOT( onTarrainMapVisibilityChanged(bool) ) );
	QObject::connect( m_updateMinimap, SIGNAL( clicked(bool) ), this, SLOT( onUpdateMinimapChanged(bool) ) );
	QObject::connect( m_skinId, SIGNAL( currentIndexChanged(const QString&) ), this, SLOT( onSkinIdChanged(const QString&) ) );

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
	QObject::disconnect( m_tarrainMapVisibility, SIGNAL( clicked(bool) ), this, SLOT( onTarrainMapVisibilityChanged(bool) ) );
	QObject::disconnect( m_updateMinimap, SIGNAL( clicked(bool) ), this, SLOT( onUpdateMinimapChanged(bool) ) );
	QObject::disconnect( m_skinId, SIGNAL( currentIndexChanged(const QString&) ), this, SLOT( onSkinIdChanged(const QString&) ) );

	m_tarrainMapVisibility = NULL;
	m_skinId = NULL;

	m_mainWidget.reset();

} // SettingsView::viewWasClosed


/*---------------------------------------------------------------------------*/


void
SettingsView::onTarrainMapVisibilityChanged( bool _visibility )
{
	m_environment.setBool( Resources::Properties::TerrainMapVisibility, _visibility );

} // SettingsView::onTarrainMapVisibilityChanged


/*---------------------------------------------------------------------------*/


void
SettingsView::onSkinIdChanged( const QString& _skinId )
{
	m_environment.setString( Resources::Properties::SkinId, _skinId );

} // SettingsView::onSkinIdChanged


/*---------------------------------------------------------------------------*/


void
SettingsView::onUpdateMinimapChanged( bool _update )
{
	m_environment.setBool( Resources::Properties::UpdateMinimap, _update );

} // SettingsView::onUpdateMinimapChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
