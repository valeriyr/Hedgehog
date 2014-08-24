
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/views/lv_settings_view.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "sound_manager/h/sm_resources.hpp"
#include "landscape_model/h/lm_resources.hpp"

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
	,	m_playSound( new QCheckBox( Resources::Views::PlaySoundCheckboxName ) )
	,	m_skinId( new QComboBox() )
	,	m_viewTitle( Resources::Views::SettingsViewTitle )
	,	m_ip( new QLineEdit() )
	,	m_port( new QLineEdit() )
	,	m_connectionTimeOut( new QLineEdit() )
{
	m_port->setInputMask( "0000" );

	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->setAlignment( Qt::AlignTop );

	QHBoxLayout* networkLayout = new QHBoxLayout();

	QLabel* ipLabel = new QLabel( Resources::Views::IpLabel );
	ipLabel->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );

	QLabel* portLabel = new QLabel( Resources::Views::PortLabel );
	portLabel->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );

	networkLayout->addWidget( ipLabel );
	networkLayout->addWidget( m_ip );

	networkLayout->addWidget( portLabel );
	networkLayout->addWidget( m_port );

	QHBoxLayout* skinIdLayout = new QHBoxLayout();

	m_skinId->addItem( "summer" );
	m_skinId->addItem( "winter" );
	m_skinId->addItem( "wasteland" );

	m_skinId->setCurrentText( m_environment.getString( Resources::Properties::SkinId ) );

	QLabel* skinIdLabel = new QLabel( Resources::Views::SkinIdLabel );
	skinIdLabel->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );

	skinIdLayout->addWidget( skinIdLabel );
	skinIdLayout->addWidget( m_skinId );

	QHBoxLayout* connectionTimeOutLayout = new QHBoxLayout();

	QLabel* connectionTimeOutLabel = new QLabel( Resources::Views::ConnectionTimeOutLabel );
	connectionTimeOutLabel->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );

	connectionTimeOutLayout->addWidget( connectionTimeOutLabel );
	connectionTimeOutLayout->addWidget( m_connectionTimeOut );

	mainLayout->addLayout( skinIdLayout );
	mainLayout->addWidget( m_tarrainMapVisibility );
	mainLayout->addWidget( m_updateMinimap );
	mainLayout->addWidget( m_playSound );
	mainLayout->addLayout( networkLayout );
	mainLayout->addLayout( connectionTimeOutLayout );

	m_mainWidget->setLayout( mainLayout );

	m_tarrainMapVisibility->setChecked( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) );
	m_updateMinimap->setChecked( m_environment.getBool( Resources::Properties::UpdateMinimap ) );
	m_playSound->setChecked( m_environment.getBool( Framework::Core::SoundManager::Resources::Properties::PlaySound ) );
	m_ip->setText( m_environment.getString( Core::LandscapeModel::Resources::Properties::Ip ) );
	m_port->setText( QString::number( m_environment.getUInt( Core::LandscapeModel::Resources::Properties::Port ) ) );
	m_connectionTimeOut->setText( QString::number( m_environment.getUInt( Core::LandscapeModel::Resources::Properties::ConnectionTimeOut ) ) );

	QObject::connect( m_tarrainMapVisibility, SIGNAL( clicked(bool) ), this, SLOT( onTarrainMapVisibilityChanged(bool) ) );
	QObject::connect( m_updateMinimap, SIGNAL( clicked(bool) ), this, SLOT( onUpdateMinimapChanged(bool) ) );
	QObject::connect( m_playSound, SIGNAL( clicked(bool) ), this, SLOT( onPlaySoundChanged(bool) ) );
	QObject::connect( m_skinId, SIGNAL( currentIndexChanged(const QString&) ), this, SLOT( onSkinIdChanged(const QString&) ) );
	QObject::connect( m_ip, SIGNAL( textChanged(const QString&) ), this, SLOT( onIpChanged(const QString&) ) );
	QObject::connect( m_port, SIGNAL( textChanged(const QString&) ), this, SLOT( onPortChanged(const QString&) ) );
	QObject::connect( m_connectionTimeOut, SIGNAL( textChanged(const QString&) ), this, SLOT( onConnectionTimeOutChanged(const QString&) ) );

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
	QObject::disconnect( m_connectionTimeOut, SIGNAL( textChanged(const QString&) ), this, SLOT( onConnectionTimeOutChanged(const QString&) ) );
	QObject::disconnect( m_tarrainMapVisibility, SIGNAL( clicked(bool) ), this, SLOT( onTarrainMapVisibilityChanged(bool) ) );
	QObject::disconnect( m_updateMinimap, SIGNAL( clicked(bool) ), this, SLOT( onUpdateMinimapChanged(bool) ) );
	QObject::disconnect( m_playSound, SIGNAL( clicked(bool) ), this, SLOT( onPlaySoundChanged(bool) ) );
	QObject::disconnect( m_skinId, SIGNAL( currentIndexChanged(const QString&) ), this, SLOT( onSkinIdChanged(const QString&) ) );
	QObject::disconnect( m_ip, SIGNAL( textChanged(const QString&) ), this, SLOT( onIpChanged(const QString&) ) );
	QObject::disconnect( m_port, SIGNAL( textChanged(const QString&) ), this, SLOT( onPortChanged(const QString&) ) );

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


void
SettingsView::onPlaySoundChanged( bool _play )
{
	m_environment.setBool( Framework::Core::SoundManager::Resources::Properties::PlaySound, _play );

} // SettingsView::onPlaySoundChanged


/*---------------------------------------------------------------------------*/


void
SettingsView::onIpChanged( const QString& _ip )
{
	m_environment.setString( Core::LandscapeModel::Resources::Properties::Ip, _ip );

} // SettingsView::onIpChanged


/*---------------------------------------------------------------------------*/


void
SettingsView::onPortChanged( const QString& _port )
{
	m_environment.setUInt( Core::LandscapeModel::Resources::Properties::Port, _port.toUInt() );

} // SettingsView::onPortChanged


/*---------------------------------------------------------------------------*/


void
SettingsView::onConnectionTimeOutChanged( const QString& _timeOut )
{
	m_environment.setUInt( Core::LandscapeModel::Resources::Properties::ConnectionTimeOut, _timeOut.toUInt() );

} // SettingsView::onConnectionTimeOutChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
