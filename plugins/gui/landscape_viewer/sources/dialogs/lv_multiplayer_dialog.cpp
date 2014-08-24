
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/dialogs/lv_multiplayer_dialog.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_environment.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"
#include "landscape_viewer/sources/utilities/lv_utilities.hpp"

#include "landscape_model/h/lm_resources.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/h/lm_events.hpp"

#include "network_manager/h/nm_connection_info.hpp"
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
	disconnectWidgets();

	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	if ( !locker->getLandscapeModel()->isSimulationRunning() )
		locker->getLandscapeModel()->resetModel();

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
MultiplayerDialog::onCreateButtonPressed( bool /*_checked*/ )
{
	m_environment.lockModel()->getLandscapeModel()->setupMultiPlayerGame(
		Framework::Core::NetworkManager::ConnectionInfo(
				m_environment.getString( Resources::Properties::Ip )
			,	m_environment.getUInt( Resources::Properties::Port ) ) );

} // MultiplayerDialog::onCreateButtonPressed


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onConnectButtonPressed( bool /*_checked*/ )
{
	m_environment.lockModel()->getLandscapeModel()->connectToMultiPlayerGame(
		Framework::Core::NetworkManager::ConnectionInfo(
				m_connectToIp->text()
			,	m_connectToPort->text().toUInt() ) );

} // MultiplayerDialog::onCreateButtonPressed


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onStartButtonPressed( bool /*_checked*/ )
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	if ( !locker->getLandscapeModel()->isConfigurated() )
		locker->getLandscapeModel()->setupSinglePlayerGame();

	m_environment.getLandscapeViewer()->startSimulation();
	close();

} // MultiplayerDialog::onCreateButtonPressed


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onPlayerColorChanged()
{
	PlayersDataCollectionIterator
			begin = m_playersData.begin()
		,	end = m_playersData.end();

	for ( ; begin != end; ++begin )
	{
		m_environment.getGraphicsInfo()->setStartPointColor( begin->first, Utilities::colorFromString( begin->second.m_color.currentText() ) );
	}

	updatePlayersColors();
	updateMapPreview();

} // MultiplayerDialog::onPlayerColorChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onPlayerRaceChanged()
{
	PlayerData* playerData = getPlayerDataByRace( sender() );

	if ( playerData )
	{
		m_environment.lockModel()->getLandscapeModel()->setStartPointRace( playerData->m_id, playerData->m_race.currentText() );
	}

} // MultiplayerDialog::onPlayerRaceChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onPlayerTypeChanged()
{
	PlayerData* playerData = getPlayerDataByRace( sender() );

	if ( playerData )
	{
		m_environment.lockModel()->getLandscapeModel()
			->setStartPointType(
					playerData->m_id
				,	Core::LandscapeModel::PlayerType::fromString( playerData->m_type.currentText() ) );
	}

} // MultiplayerDialog::onPlayerTypeChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onStartPointRaceChanged( const Framework::Core::EventManager::Event& _event )
{
	const Core::LandscapeModel::StartPoint::Id id
		= _event.getAttribute( Core::LandscapeModel::Events::StartPointRaceChanged::ms_startPointIdAttribute ).toInt();
	const QString race
		= _event.getAttribute( Core::LandscapeModel::Events::StartPointRaceChanged::ms_startPointRaceAttribute ).toString();

	PlayersDataCollectionIterator iterator = m_playersData.find( id );
	assert( iterator != m_playersData.end() );

	QObject::disconnect( &iterator->second.m_race, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerRaceChanged() ) );

	iterator->second.m_race.setCurrentText( race );

	QObject::connect( &iterator->second.m_race, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerRaceChanged() ) );

} // MultiplayerDialog::onStartPointRaceChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onStartPointTypeChanged( const Framework::Core::EventManager::Event& _event )
{
	const Core::LandscapeModel::StartPoint::Id id
		= _event.getAttribute( Core::LandscapeModel::Events::StartPointTypeChanged::ms_startPointIdAttribute ).toInt();
	const Core::LandscapeModel::PlayerType::Enum type = static_cast< Core::LandscapeModel::PlayerType::Enum >(
		_event.getAttribute( Core::LandscapeModel::Events::StartPointTypeChanged::ms_startPointTypeAttribute ).toInt() );

	PlayersDataCollectionIterator iterator = m_playersData.find( id );
	assert( iterator != m_playersData.end() );

	QObject::disconnect( &iterator->second.m_type, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerTypeChanged() ) );

	iterator->second.m_type.setCurrentText( Core::LandscapeModel::PlayerType::toString( type ) );

	QObject::connect( &iterator->second.m_type, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerTypeChanged() ) );

} // MultiplayerDialog::onStartPointTypeChanged


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

	QObject::connect( m_createButton, SIGNAL( clicked( bool ) ), this, SLOT( onCreateButtonPressed( bool ) ) );
	QObject::connect( m_connectButton, SIGNAL( clicked( bool ) ), this, SLOT( onConnectButtonPressed( bool ) ) );
	QObject::connect( m_startButton, SIGNAL( clicked( bool ) ), this, SLOT( onStartButtonPressed( bool ) ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::StartPointRaceChanged::ms_type
							,	boost::bind( &MultiplayerDialog::onStartPointRaceChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::StartPointTypeChanged::ms_type
							,	boost::bind( &MultiplayerDialog::onStartPointTypeChanged, this, _1 ) );

} // MultiplayerDialog::connectWidgets


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::disconnectWidgets()
{
	m_subscriber.unsubscribe();

	QObject::disconnect(
			m_landscapesList
		,	SIGNAL( currentItemChanged( QListWidgetItem*, QListWidgetItem* ) )
		,	this
		,	SLOT( onLandscapeSelected( QListWidgetItem*, QListWidgetItem* ) ) );

	QObject::disconnect( m_createButton, SIGNAL( clicked( bool ) ), this, SLOT( onCreateButtonPressed( bool ) ) );
	QObject::disconnect( m_connectButton, SIGNAL( clicked( bool ) ), this, SLOT( onConnectButtonPressed( bool ) ) );
	QObject::disconnect( m_startButton, SIGNAL( clicked( bool ) ), this, SLOT( onStartButtonPressed( bool ) ) );

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
	m_environment.getLandscapeViewer()
		->initLandscape( m_environment.getLandscapesDirectory() + "/" + _landscapeName );

	updateMapPreview();
	updatePlayersList();

} // MultiplayerDialog::currentLandscapeWasChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::updateMapPreview()
{
	QPixmap surface;
	m_environment.generateMapPreview(
			surface
		,	IMapPreviewGenerator::GenerateLayers::Surface | IMapPreviewGenerator::GenerateLayers::StartPoints );

	m_mapPreview->setPixmap( surface );

} // MultiplayerDialog::updateMapPreview


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::updatePlayersList()
{
	clearLayout( m_playersLayout );

	m_playersData.clear();

	buildPlayersList();

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


void
MultiplayerDialog::buildPlayersList()
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	boost::intrusive_ptr< Core::LandscapeModel::ILandscape >
		landscape = locker->getLandscapeModel()->getLandscape();

	// Races

	Core::LandscapeModel::IStaticData::RacesCollection reces;
	m_environment.fetchRaces( reces );

	QStringList qraces;

	Core::LandscapeModel::IStaticData::RacesCollectionIterator
			beginRaces = reces.begin()
		,	endRaces = reces.end();

	for ( ; beginRaces != endRaces; ++beginRaces )
		qraces.push_back( beginRaces->first );

	// Players

	QStringList qplayers;

	for (	Core::LandscapeModel::PlayerType::Enum type = Core::LandscapeModel::PlayerType::Begin
		;	type != Core::LandscapeModel::PlayerType::Size
		;	type = static_cast< Core::LandscapeModel::PlayerType::Enum >( type + 1 ) )
	{
		qplayers.push_back( Core::LandscapeModel::PlayerType::toString( type ) );
	}

	// List

	Plugins::Core::LandscapeModel::ILandscape::StartPointsIterator
		iterator = landscape->getStartPointsIterator();

	while( iterator->isValid() )
	{
		QHBoxLayout* playerLayout = new QHBoxLayout();

		QString startPointFormat( "StartPoint %1:" );
		startPointFormat = startPointFormat.arg( iterator->current().m_id );

		playerLayout->addWidget( new QLabel( startPointFormat ) );

		QComboBox* playerComboBox = new QComboBox();
		playerComboBox->addItems( qplayers );

		playerComboBox->setCurrentText( Core::LandscapeModel::PlayerType::toString( Core::LandscapeModel::PlayerType::Player ) );

		QObject::connect( playerComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerTypeChanged() ) );

		playerLayout->addWidget( playerComboBox );
		playerLayout->addWidget( new QLabel( "Race:" ) );

		QComboBox* raceComboBox = new QComboBox();
		raceComboBox->addItems( qraces );

		QObject::connect( raceComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerRaceChanged() ) );

		playerLayout->addWidget( raceComboBox );
		playerLayout->addWidget( new QLabel( "Color:" ) );

		QComboBox* colorsComboBox = new QComboBox();

		playerLayout->addWidget( colorsComboBox );

		m_playersLayout->addLayout( playerLayout );

		m_playersData.insert(
			std::make_pair(
					iterator->current().m_id
				,	PlayerData( *playerComboBox, *raceComboBox, *colorsComboBox, iterator->current().m_id ) ) );

		iterator->next();
	}

	updatePlayersColors();

} // MultiplayerDialog::buildPlayersList


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::updatePlayersColors()
{
	typedef std::vector< std::pair< QIcon, QColor > > ColorsCollection;
	typedef ColorsCollection::const_iterator ColorsCollectionIterator;

	ColorsCollection colors;

	IGraphicsInfo::PossiblePlayersColorIterator
		colorsIterator = m_environment.getGraphicsInfo()->getPossiblePlayersColors();

	while( colorsIterator->isValid() )
	{
		QPixmap pixmap( 32, 16 );
		pixmap.fill( colorsIterator->current() );

		colors.push_back( std::make_pair( QIcon( pixmap ), colorsIterator->current() ) );

		colorsIterator->next();
	}

	PlayersDataCollectionIterator
			begin = m_playersData.begin()
		,	end = m_playersData.end();

	for ( ; begin != end; ++begin )
	{
		QObject::disconnect( &begin->second.m_color, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerColorChanged() ) );

		begin->second.m_color.clear();

		const QColor color( m_environment.getGraphicsInfo()->getStartPointColor( begin->first ) );

		ColorsCollectionIterator
				colorsBegin = colors.begin()
			,	colorsEnd = colors.end();

		for ( ; colorsBegin != colorsEnd; ++colorsBegin )
		{
			if (	color == colorsBegin->second
				||	!m_environment.getGraphicsInfo()->colorIsUsed( colorsBegin->second ) )
			{
				begin->second.m_color.addItem( colorsBegin->first, Utilities::colorToString( colorsBegin->second ) );
			}
		}

		begin->second.m_color.setCurrentText( Utilities::colorToString( color ) );

		QObject::connect( &begin->second.m_color, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerColorChanged() ) );
	}

} // MultiplayerDialog::updatePlayersColors


/*---------------------------------------------------------------------------*/


MultiplayerDialog::PlayerData*
MultiplayerDialog::getPlayerDataByRace( const QObject* _race )
{
	PlayersDataCollectionIterator
			begin = m_playersData.begin()
		,	end = m_playersData.end();

	for ( ; begin != end; ++begin )
	{
		if ( &begin->second.m_race == _race )
			return &begin->second;
	}

	return NULL;

} // MultiplayerDialog::getPlayerDataByRace


/*---------------------------------------------------------------------------*/


MultiplayerDialog::PlayerData*
MultiplayerDialog::getPlayerDataByType( const QObject* _type )
{
	PlayersDataCollectionIterator
			begin = m_playersData.begin()
		,	end = m_playersData.end();

	for ( ; begin != end; ++begin )
	{
		if ( &begin->second.m_type == _type )
			return &begin->second;
	}

	return NULL;

} // MultiplayerDialog::getPlayerDataByType


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
