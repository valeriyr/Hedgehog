
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/dialogs/lv_multiplayer_dialog.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/environment/lv_environment.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"
#include "landscape_viewer/sources/utilities/lv_utilities.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/h/lm_events.hpp"
#include "landscape_model/h/lm_resources.hpp"
#include "landscape_model/h/lm_victory_condition.hpp"

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
	,	m_victoryCondition( new QComboBox() )
	,	m_landscapesList( new QListWidget() )
	,	m_connectToIp( new QLineEdit() )
	,	m_connectToPort( new QLineEdit() )
	,	m_createButton( new QPushButton( Resources::Views::CreateButtonName ) )
	,	m_connectButton( new QPushButton( Resources::Views::ConnectButtonName ) )
	,	m_startButton( new QPushButton( Resources::Views::StartButtonName ) )
	,	m_cancelButton( new QPushButton( Resources::Views::CancelButtonName ) )
	,	m_playersData()
	,	m_nonePlayerTypes()
	,	m_hasPlayerTypes()
{
	m_nonePlayerTypes.push_back( Core::LandscapeModel::PlayerType::toString( Core::LandscapeModel::PlayerType::Blocked ) );
	m_nonePlayerTypes.push_back( Core::LandscapeModel::PlayerType::toString( Core::LandscapeModel::PlayerType::Open ) );
	m_nonePlayerTypes.push_back( Core::LandscapeModel::PlayerType::toString( Core::LandscapeModel::PlayerType::AI ) );

	m_hasPlayerTypes = m_nonePlayerTypes;
	m_hasPlayerTypes.push_back( Core::LandscapeModel::PlayerType::toString( Core::LandscapeModel::PlayerType::Player ) );

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
	m_environment.lockModel()->getLandscapeModel()->setupMultiPlayerGame();

	updateWidgetsStates();

} // MultiplayerDialog::onCreateButtonPressed


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onConnectButtonPressed( bool /*_checked*/ )
{
	m_environment.lockModel()->getLandscapeModel()->connectToMultiPlayerGame(
		Framework::Core::NetworkManager::ConnectionInfo(
				m_connectToIp->text()
			,	m_connectToPort->text().toUInt() ) );

	updateWidgetsStates();

} // MultiplayerDialog::onCreateButtonPressed


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onStartButtonPressed( bool /*_checked*/ )
{
	m_environment.getLandscapeViewer()->startSimulation();
	close();

} // MultiplayerDialog::onStartButtonPressed


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onCancelButtonPressed( bool _checked )
{
	m_environment.getLandscapeViewer()->closeLandscape();

	updateWidgetsStates();

	if ( m_landscapesList->currentItem() )
		currentLandscapeWasChanged( m_landscapesList->currentItem()->text() );

} // MultiplayerDialog::onCancelButtonPressed


void
MultiplayerDialog::onPortChanged()
{
	updateWidgetsStates();

} // MultiplayerDialog::onPortChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onIpChanged()
{
	updateWidgetsStates();

} // MultiplayerDialog::onIpChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onPlayerColorChanged()
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	PlayersDataCollectionIterator
			begin = m_playersData.begin()
		,	end = m_playersData.end();

	for ( ; begin != end; ++begin )
	{
		boost::intrusive_ptr< Core::LandscapeModel::IPlayer > player = locker->getLandscapeModel()->getPlayer( begin->first );
		m_environment.getGraphicsInfo()->setStartPointColor( player->getStartPointId(), Utilities::colorFromString( begin->second.m_color.currentText() ) );
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
		m_environment.lockModel()->getLandscapeModel()->pushCommand(
			Core::LandscapeModel::Command( Core::LandscapeModel::CommandId::ChangePlayerRace )
				.pushArgument( playerData->m_id )
				.pushArgument( playerData->m_race.currentText() ) );
	}

} // MultiplayerDialog::onPlayerRaceChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onPlayerTypeChanged()
{
	PlayerData* playerData = getPlayerDataByType( sender() );

	if ( playerData )
	{
		m_environment.lockModel()->getLandscapeModel()->pushCommand(
			Core::LandscapeModel::Command( Core::LandscapeModel::CommandId::ChangePlayerType )
				.pushArgument( playerData->m_id )
				.pushArgument( Core::LandscapeModel::PlayerType::fromString( playerData->m_type.currentText() ) ) );
	}

} // MultiplayerDialog::onPlayerTypeChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onPlayerNameChanged( const Framework::Core::EventManager::Event& _event )
{
	const Core::LandscapeModel::IPlayer::Id id
		= _event.getAttribute( Core::LandscapeModel::Events::PlayerNameChanged::ms_playerIdAttribute ).toInt();
	const Core::LandscapeModel::StartPoint::Id startPointid
		= _event.getAttribute( Core::LandscapeModel::Events::PlayerNameChanged::ms_startPointIdAttribute ).toInt();
	const QString name
		= _event.getAttribute( Core::LandscapeModel::Events::PlayerNameChanged::ms_playerNameAttribute).toString();

	PlayersDataCollectionIterator iterator = m_playersData.find( id );
	assert( iterator != m_playersData.end() );

	QString palyerLabelText
		= QString( Resources::Views::PlayerByStartPointLabelFormat )
			.arg( startPointid )
			.arg( name );

	iterator->second.m_player.setText( palyerLabelText );

} // MultiplayerDialog::onPlayerNameChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onSimulationStarted( const Framework::Core::EventManager::Event& _event )
{
	close();

} // MultiplayerDialog::onSimulationStarted


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onPlayerRaceChanged( const Framework::Core::EventManager::Event& _event )
{
	const Core::LandscapeModel::IPlayer::Id id
		= _event.getAttribute( Core::LandscapeModel::Events::PlayerRaceChanged::ms_playerIdAttribute ).toInt();
	const QString race
		= _event.getAttribute( Core::LandscapeModel::Events::PlayerRaceChanged::ms_playerRaceAttribute).toString();

	PlayersDataCollectionIterator iterator = m_playersData.find( id );
	assert( iterator != m_playersData.end() );

	QObject::disconnect( &iterator->second.m_race, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerRaceChanged() ) );

	iterator->second.m_race.setCurrentText( race );

	QObject::connect( &iterator->second.m_race, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerRaceChanged() ) );

} // MultiplayerDialog::onPlayerRaceChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::onPlayerTypeChanged( const Framework::Core::EventManager::Event& _event )
{
	const Core::LandscapeModel::IPlayer::Id id
		= _event.getAttribute( Core::LandscapeModel::Events::PlayerTypeChanged::ms_playerIdAttribute ).toInt();
	const Core::LandscapeModel::PlayerType::Enum type = static_cast< Core::LandscapeModel::PlayerType::Enum >(
		_event.getAttribute( Core::LandscapeModel::Events::PlayerTypeChanged::ms_playerTypeAttribute ).toInt() );

	PlayersDataCollectionIterator iterator = m_playersData.find( id );
	assert( iterator != m_playersData.end() );

	QObject::disconnect( &iterator->second.m_type, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerTypeChanged() ) );

	iterator->second.m_type.clear();
	iterator->second.m_type.addItems( type == Core::LandscapeModel::PlayerType::Player ? m_hasPlayerTypes : m_nonePlayerTypes );

	iterator->second.m_type.setCurrentText( Core::LandscapeModel::PlayerType::toString( type ) );

	updateWidgetsStates();

	QObject::connect( &iterator->second.m_type, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerTypeChanged() ) );

} // MultiplayerDialog::onPlayerTypeChanged


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::createWidgets()
{
	QVBoxLayout* mainLayout = new QVBoxLayout();

	QHBoxLayout* contentLayout = new QHBoxLayout();

	// Right block

	QVBoxLayout* rightBlockLayout = new QVBoxLayout();

	rightBlockLayout->addWidget( m_landscapesList );
	addLine( rightBlockLayout );

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

	QLabel* victoryConditionLabel = new QLabel( Resources::Views::VictoryCondition );
	victoryConditionLabel->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );

	QHBoxLayout* victoryConditionLayout = new QHBoxLayout();
	victoryConditionLayout->addWidget( victoryConditionLabel );
	victoryConditionLayout->addWidget( m_victoryCondition );

	leftBlockLayout->addLayout( mapPreviewLayout );
	addLine( leftBlockLayout );
	leftBlockLayout->addLayout( victoryConditionLayout );
	addLine( leftBlockLayout );
	leftBlockLayout->addLayout( m_playersLayout );

	// Buttons

	QHBoxLayout* buttonsLayout = new QHBoxLayout();

	buttonsLayout->addWidget( m_createButton );
	buttonsLayout->addWidget( m_connectButton );
	buttonsLayout->addWidget( m_startButton );
	buttonsLayout->addWidget( m_cancelButton );

	// Finish setup

	contentLayout->addLayout( leftBlockLayout );
	contentLayout->addLayout( rightBlockLayout );

	mainLayout->addLayout( contentLayout );
	addLine( mainLayout );
	mainLayout->addLayout( buttonsLayout );

	setLayout( mainLayout );

} // MultiplayerDialog::createWidgets


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::initWidgets()
{
	setMinimumHeight( IMapPreviewGenerator::ms_fixedWidgetSize.height() * 2.5f );

	m_mapPreview->setFixedSize( IMapPreviewGenerator::ms_fixedWidgetSize );

	for(	Core::LandscapeModel::VictoryCondition::Enum begin = Core::LandscapeModel::VictoryCondition::Begin
		;	begin != Core::LandscapeModel::VictoryCondition::Size
		;	begin = static_cast< Core::LandscapeModel::VictoryCondition::Enum >( begin + 1 ) )
	{
		m_victoryCondition->addItem( Core::LandscapeModel::VictoryCondition::toString( begin ) );
	}

	m_connectToIp->setText( m_environment.getString( Core::LandscapeModel::Resources::Properties::Ip ) );
	m_connectToPort->setText( QString::number( Core::LandscapeModel::Resources::Properties::DefaultPortValue ) );

	updateLandscapesList();

	if ( m_landscapesList->currentItem() )
		currentLandscapeWasChanged( m_landscapesList->currentItem()->text() );

	updateWidgetsStates();

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
	QObject::connect( m_cancelButton, SIGNAL( clicked( bool ) ), this, SLOT( onCancelButtonPressed( bool ) ) );
	QObject::connect( m_connectToPort, SIGNAL( textChanged( const QString& ) ), this, SLOT( onPortChanged() ) );
	QObject::connect( m_connectToIp, SIGNAL( textChanged( const QString& ) ), this, SLOT( onIpChanged() ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::PlayerRaceChanged::ms_type
							,	boost::bind( &MultiplayerDialog::onPlayerRaceChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::PlayerTypeChanged::ms_type
							,	boost::bind( &MultiplayerDialog::onPlayerTypeChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::PlayerNameChanged::ms_type
							,	boost::bind( &MultiplayerDialog::onPlayerNameChanged, this, _1 ) );

	m_subscriber.subscribe(		Framework::Core::MultithreadingManager::Resources::MainThreadName
							,	Plugins::Core::LandscapeModel::Events::SimulationStarted::ms_type
							,	boost::bind( &MultiplayerDialog::onSimulationStarted, this, _1 ) );

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
	QObject::disconnect( m_cancelButton, SIGNAL( clicked( bool ) ), this, SLOT( onCancelButtonPressed( bool ) ) );
	QObject::disconnect( m_connectToPort, SIGNAL( textChanged( const QString& ) ), this, SLOT( onPortChanged() ) );
	QObject::disconnect( m_connectToIp, SIGNAL( textChanged( const QString& ) ), this, SLOT( onIpChanged() ) );

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
	updateWidgetsStates();

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
MultiplayerDialog::updateWidgetsStates()
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	boost::intrusive_ptr< Core::LandscapeModel::IPlayer >
		player = locker->getLandscapeModel()->getMyPlayer();

	bool isConfigurated = locker->getLandscapeModel()->isConfigurated();

	bool connectButtonEnabled
		=	!isConfigurated
		&&	!(m_connectToIp->text() == m_environment.getString( Core::LandscapeModel::Resources::Properties::Ip )
		&&	m_connectToPort->text() == m_environment.getString( Core::LandscapeModel::Resources::Properties::Port ) );

	bool startButtonEnabled
		=	isConfigurated
		&&	locker->getLandscapeModel()->twoOrMoreActivatedPlayers();

	bool createButtonEnabled
		=	!isConfigurated
		&&	locker->getLandscapeModel()->getFirstFreePlayer();

	m_landscapesList->setEnabled( !isConfigurated );

	m_connectToIp->setEnabled( !isConfigurated );
	m_connectToPort->setEnabled( !isConfigurated );

	m_createButton->setEnabled( createButtonEnabled );
	m_connectButton->setEnabled( connectButtonEnabled );

	m_startButton->setEnabled( startButtonEnabled );
	m_cancelButton->setEnabled( isConfigurated );

	PlayersDataCollectionIterator
			begin = m_playersData.begin()
		,	end = m_playersData.end();

	for ( ; begin != end; ++begin )
	{
		begin->second.m_type.setEnabled( isConfigurated && player && player->getUniqueId() != begin->first );
		begin->second.m_race.setEnabled( isConfigurated );
		begin->second.m_color.setEnabled( isConfigurated );
	}

} // MultiplayerDialog::updateWidgetsStates


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::addLine( QLayout* _layout )
{
	QFrame* line = new QFrame();
	line->setFrameShape( QFrame::HLine );
	line->setFrameShadow( QFrame::Sunken );
	_layout->addWidget( line );

} // MultiplayerDialog::addLine


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

	QStringList races;

	Core::LandscapeModel::IStaticData::RacesCollectionIterator
			beginRaces = reces.begin()
		,	endRaces = reces.end();

	for ( ; beginRaces != endRaces; ++beginRaces )
		races.push_back( beginRaces->first );

	// List

	Core::LandscapeModel::ILandscapeModel::PlayersCollection players;
	locker->getLandscapeModel()->fetchPlayers( players );

	Core::LandscapeModel::ILandscapeModel::PlayersCollectionIterator
			begin = players.begin()
		,	end = players.end();

	for ( ; begin != end; ++begin )
	{
		QHBoxLayout* playerLayout = new QHBoxLayout();

		QString palyerLabelText
			= QString( Resources::Views::PlayerByStartPointLabelFormat )
				.arg( ( *begin )->getStartPointId() )
				.arg( ( *begin )->getName() );

		QLabel* playerLabel = new QLabel( palyerLabelText );

		playerLayout->addWidget( playerLabel );

		QComboBox* playerComboBox = new QComboBox();
		playerComboBox->addItems( m_nonePlayerTypes );

		playerComboBox->setCurrentText( Core::LandscapeModel::PlayerType::toString( ( *begin )->getType() ) );

		QObject::connect( playerComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerTypeChanged() ) );

		playerLayout->addWidget( playerComboBox );
		playerLayout->addWidget( new QLabel( Resources::Views::RaceLabel ) );

		QComboBox* raceComboBox = new QComboBox();
		raceComboBox->addItems( races );

		raceComboBox->setCurrentText( ( *begin )->getRace() );

		QObject::connect( raceComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerRaceChanged() ) );

		playerLayout->addWidget( raceComboBox );
		playerLayout->addWidget( new QLabel( Resources::Views::ColorLabel ) );

		QComboBox* colorsComboBox = new QComboBox();

		playerLayout->addWidget( colorsComboBox );

		m_playersLayout->addLayout( playerLayout );

		m_playersData.insert(
			std::make_pair(
					( *begin )->getUniqueId()
				,	PlayerData( *playerLabel, *playerComboBox, *raceComboBox, *colorsComboBox, ( *begin )->getUniqueId() ) ) );
	}

	updatePlayersColors();

} // MultiplayerDialog::buildPlayersList


/*---------------------------------------------------------------------------*/


void
MultiplayerDialog::updatePlayersColors()
{
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

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
		boost::intrusive_ptr< Core::LandscapeModel::IPlayer > player = locker->getLandscapeModel()->getPlayer( begin->first );

		QObject::disconnect( &begin->second.m_color, SIGNAL( currentIndexChanged( int ) ), this, SLOT( onPlayerColorChanged() ) );

		begin->second.m_color.clear();

		const QColor color( m_environment.getGraphicsInfo()->getStartPointColor( player->getStartPointId() ) );

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
