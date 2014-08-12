
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/dialogs/lv_multiplayer_dialog.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "network_manager/h/nm_resources.hpp"
#include "landscape_model/h/lm_resources.hpp"

#include "lv_multiplayer_dialog.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


MultiplayerDialog::MultiplayerDialog( const IEnvironment& _environment )
	:	QDialog()
	,	m_environment( _environment )
	,	m_mapPreview( new QLabel() )
	,	m_playersLayout( new QVBoxLayout() )
	,	m_landscapesList( new QListWidget() )
	,	m_connectToIp( new QLineEdit() )
	,	m_connectToPort( new QLineEdit() )
	,	m_createButton( new QPushButton( Resources::Views::CreateButtonName ) )
	,	m_connectButton( new QPushButton( Resources::Views::ConnectButtonName ) )
	,	m_startButton( new QPushButton( Resources::Views::StartButtonName ) )
{
	createWidgets();

	initWidgets();

	connectWidgets();

} // MultiplayerDialog::MultiplayerDialog


/*---------------------------------------------------------------------------*/


MultiplayerDialog::~MultiplayerDialog()
{
	disconnectWidgets();

} // MultiplayerDialog::~MultiplayerDialog


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onLandscapeSelected( QListWidgetItem* /*_oldItem*/, QListWidgetItem* _newItem )
{
	if ( _newItem )
		currentLandscapeWasChanged( _newItem->text() );

} // MultiplayerDialog::onLandscapeSelected


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::createWidgets()
{
	QVBoxLayout* mainLayout = new QVBoxLayout();

	QHBoxLayout* contentLayout = new QHBoxLayout();

	// Right block

	QVBoxLayout* rightBlockLayout = new QVBoxLayout();

	rightBlockLayout->addWidget( m_landscapesList );

	QHBoxLayout* networkLayout = new QHBoxLayout();

	QLabel* ipLabel = new QLabel( Resources::Views::IpLabel );
	ipLabel->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );

	QLabel* portLabel = new QLabel( Resources::Views::PortLabel );
	portLabel->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );

	networkLayout->addWidget( ipLabel );
	networkLayout->addWidget( m_connectToIp );

	networkLayout->addWidget( portLabel );
	networkLayout->addWidget( m_connectToPort );

	rightBlockLayout->addLayout( networkLayout );

	// Left block

	QVBoxLayout* leftBlockLayout = new QVBoxLayout();

	leftBlockLayout->addWidget( m_mapPreview );
	leftBlockLayout->addLayout( m_playersLayout );

	// Buttons

	QHBoxLayout* buttonsLayout = new QHBoxLayout();

	buttonsLayout->addWidget( m_createButton );
	buttonsLayout->addWidget( m_connectButton );
	buttonsLayout->addWidget( m_startButton );

	// Finish setup

	contentLayout->addLayout( leftBlockLayout );
	contentLayout->addLayout( rightBlockLayout );

	mainLayout->addLayout( contentLayout );
	mainLayout->addLayout( buttonsLayout );

	setLayout( mainLayout );

} // MultiplayerDialog::createWidgets


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::initWidgets()
{
	m_mapPreview->setFixedSize( 300, 200 );

	m_startButton->setEnabled( false );

	m_connectToIp->setText( Framework::Core::NetworkManager::Resources::LocalHost );
	m_connectToPort->setText( "0212" );

	updateLandscapesList();

	if ( m_landscapesList->currentItem() )
		currentLandscapeWasChanged( m_landscapesList->currentItem()->text() );

} // MultiplayerDialog::initWidgets


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::connectWidgets()
{
	QObject::connect(
			m_landscapesList
		,	SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) )
		,	this
		,	SLOT( onLandscapeSelected( QListWidgetItem*, QListWidgetItem* ) ) );

} // MultiplayerDialog::connectWidgets


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::disconnectWidgets()
{
	QObject::disconnect(
			m_landscapesList
		,	SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) )
		,	this
		,	SLOT( onLandscapeSelected( QListWidgetItem*, QListWidgetItem* ) ) );

} // MultiplayerDialog::disconnectWidgets


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::updateLandscapesList()
{
	QDir pluginsDirectory = QDir( m_environment.getLandscapesDirectory() );

	if ( !pluginsDirectory.exists() )
		return;

	QStringList filesFilter;
	filesFilter.push_back( Core::LandscapeModel::Resources::LandscapeFileFilter );

	QFileInfoList filesList = pluginsDirectory.entryInfoList( filesFilter );

	for ( int i = 0; i < filesList.size(); ++i )
	{
         QFileInfo fileInfo = filesList.at( i );
		 m_landscapesList->addItem( fileInfo.baseName() );
	}

} // MultiplayerDialog::updateLandscapesList


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::currentLandscapeWasChanged( const QString& _landscapeName )
{
} // MultiplayerDialog::currentLandscapeWasChanged


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
