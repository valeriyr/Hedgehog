
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/dialogs/lv_multiplayer_dialog.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_model/h/lm_resources.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/h/lm_events.hpp"

#include "network_manager/h/nm_resources.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"

#include "lv_multiplayer_dialog.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


MultiplayerDialog::MultiplayerDialog( const IEnvironment& _environment )
	:	QDialog()
	,	m_environment( _environment )
	,	m_subscriber( m_environment.createSubscriber() )
	,	m_mapPreview( new QLabel() )
	,	m_playersLayout( new QVBoxLayout() )
	,	m_landscapesList( new QListWidget() )
	,	m_connectToIp( new QLineEdit() )
	,	m_connectToPort( new QLineEdit() )
	,	m_createButton( new QPushButton( Resources::Views::CreateButtonName ) )
	,	m_connectButton( new QPushButton( Resources::Views::ConnectButtonName ) )
	,	m_startButton( new QPushButton( Resources::Views::StartButtonName ) )
	,	m_playersData()
{
	createWidgets();

	initWidgets();

	connectWidgets();

} // MultiplayerDialog::MultiplayerDialog


/*---------------------------------------------------------------------------*/


MultiplayerDialog::~MultiplayerDialog()
{
	m_subscriber.unsubscribe();

	disconnectWidgets();

} // MultiplayerDialog::~MultiplayerDialog


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onLandscapeSelected( QListWidgetItem* _newItem, QListWidgetItem* /*_oldItem*/ )
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
	leftBlockLayout->setAlignment( Qt::AlignTop );

	QHBoxLayout* mapPreviewLayout = new QHBoxLayout();
	mapPreviewLayout->addWidget( m_mapPreview );

	leftBlockLayout->addLayout( mapPreviewLayout );
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
	setMinimumHeight( IMapPreviewGenerator::ms_fixedWidgetSize.height() * 2.5f );

	m_mapPreview->setFixedSize( IMapPreviewGenerator::ms_fixedWidgetSize );

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

	if ( filesList.empty() )
		return;

	for ( int i = 0; i < filesList.size(); ++i )
	{
         QFileInfo fileInfo = filesList.at( i );
		 m_landscapesList->addItem( fileInfo.fileName() );
	}

	m_landscapesList->setCurrentItem( m_landscapesList->item( 0 ) );

} // MultiplayerDialog::updateLandscapesList


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::currentLandscapeWasChanged( const QString& _landscapeName )
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	locker->getLandscapeModel()
		->initLandscape( m_environment.getLandscapesDirectory() + "/" + _landscapeName );

	updateMapPreview( *locker->getLandscapeModel()->getLandscape() );
	updatePlayersList( *locker->getLandscapeModel()->getLandscape() );

} // MultiplayerDialog::currentLandscapeWasChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::updateMapPreview( const Core::LandscapeModel::ILandscape& _landscape )
{
	QPixmap surface;
	m_environment.generateMapPreview(
			surface
		,	_landscape
		,	IMapPreviewGenerator::GenerateLayers::Surface | IMapPreviewGenerator::GenerateLayers::StartPoints );

	m_mapPreview->setPixmap( surface );

} // MultiplayerDialog::updateMapPreview


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::updatePlayersList( const Core::LandscapeModel::ILandscape& _landscape )
{
	clearLayout( m_playersLayout );

	m_playersData.clear();

	Plugins::Core::LandscapeModel::ILandscape::StartPointsIterator
		iterator = _landscape.getStartPointsIterator();

	while( iterator->isValid() )
	{
		m_playersData.insert( std::make_pair( iterator->current().m_id, PlayerData( "Orc", QColor( 255, 255, 0 ) ) ) );
		iterator->next();
	}

	Core::LandscapeModel::IStaticData::RacesCollection reces;
	m_environment.fetchRaces( reces );

	QStringList qraces;

	Core::LandscapeModel::IStaticData::RacesCollectionIterator
			beginRaces = reces.begin()
		,	endRaces = reces.end();

	for ( ; beginRaces != endRaces; ++beginRaces )
		qraces.push_back( beginRaces->first );

	QStringList qplayers;

	for (	Core::LandscapeModel::PlayerType::Enum type = Core::LandscapeModel::PlayerType::Begin
		;	type != Core::LandscapeModel::PlayerType::Size
		;	type = static_cast< Core::LandscapeModel::PlayerType::Enum >( type + 1 ) )
	{
		qplayers.push_back( Core::LandscapeModel::PlayerType::toString( type ) );
	}

	typedef std::vector< std::pair< QIcon, QColor > > ColorsCollection;
	typedef ColorsCollection::const_iterator ColorsCollectionIterator;

	ColorsCollection colors;

	IGraphicsInfoCache::PossiblePlayersColorIterator
		colorsIterator = m_environment.getGraphicsInfoCache()->getPossiblePlayersColors();

	while( colorsIterator->isValid() )
	{
		QPixmap pixmap( 32, 16 );
		pixmap.fill( colorsIterator->current() );

		colors.push_back( std::make_pair( QIcon( pixmap ), colorsIterator->current() ) );

		colorsIterator->next();
	}

	PlayersDataCollectionIterator
			playersBegin = m_playersData.begin()
		,	playersEnd = m_playersData.end();

	for ( ; playersBegin != playersEnd; ++playersBegin )
	{
		QHBoxLayout* playerLayout = new QHBoxLayout();

		playerLayout->addWidget( new QLabel( "User:" ) );

		QComboBox* playerComboBox = new QComboBox();
		playerComboBox->addItems( qplayers );

		playerLayout->addWidget( playerComboBox );

		playerLayout->addWidget( new QLabel( "Race:" ) );

		QComboBox* raceComboBox = new QComboBox();
		raceComboBox->addItems( qraces );

		playerLayout->addWidget( raceComboBox );

		playerLayout->addWidget( new QLabel( "Color:" ) );

		QComboBox* colorsComboBox = new QComboBox();

		ColorsCollectionIterator
				colorsBegin = colors.begin()
			,	colorsEnd = colors.end();

		for ( ; colorsBegin != colorsEnd; ++colorsBegin )
		{
			QString text;
			QTextStream stream( &text );

			stream << "( " << colorsBegin->second.red() << ", " << colorsBegin->second.green() << ", " << colorsBegin->second.blue() << " )";

			colorsComboBox->addItem( colorsBegin->first, text );
		}

		playerLayout->addWidget( colorsComboBox );

		m_playersLayout->addLayout( playerLayout );
	}

} // MultiplayerDialog::updatePlayersList


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::clearLayout( QLayout* _layout )
{
	while ( QLayoutItem* item = _layout->takeAt( 0 ) )
	{
		QWidget* widget;
		if ( widget = item->widget() )
			delete widget;

		if ( QLayout* childLayout = item->layout() )
			clearLayout( childLayout );

		delete item;
	}

} // MultiplayerDialog::clearLayout


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
