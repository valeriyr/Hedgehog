
#ifndef __LV_MULTIPLAYER_DIALOG_HPP__
#define __LV_MULTIPLAYER_DIALOG_HPP__

#include "landscape_model/ih/lm_iplayer.hpp"

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class MultiplayerDialog
	:	public QDialog
{

/*---------------------------------------------------------------------------*/

	struct PlayerData
	{
		PlayerData(
				QLabel&	_player
			,	QComboBox& _type
			,	QComboBox& _race
			,	QComboBox& _color
			,	const Core::LandscapeModel::IPlayer::Id& _id
			)
			:	m_player( _player )
			,	m_type( _type )
			,	m_race( _race )
			,	m_color( _color )
			,	m_id( _id )
		{}

		QLabel&	m_player;
		QComboBox& m_type;
		QComboBox& m_race;
		QComboBox& m_color;

		const Core::LandscapeModel::IPlayer::Id m_id;
	};

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MultiplayerDialog( const IEnvironment& _environment );

	virtual ~MultiplayerDialog();

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onLandscapeSelected( QListWidgetItem* _newItem, QListWidgetItem* _oldItem );

	void onCreateButtonPressed( bool _checked );
	void onConnectButtonPressed( bool _checked );
	void onStartButtonPressed( bool _checked );
	void onCancelButtonPressed( bool _checked );

	void onPlayerColorChanged();
	void onPlayerRaceChanged();
	void onPlayerTypeChanged();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onPlayerRaceChanged( const Framework::Core::EventManager::Event& _event );
	void onPlayerTypeChanged( const Framework::Core::EventManager::Event& _event );
	void onPlayerNameChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void createWidgets();

	void initWidgets();

	void connectWidgets();
	void disconnectWidgets();

	void updateLandscapesList();
	void currentLandscapeWasChanged( const QString& _landscapeName );

	void updateMapPreview();
	void updatePlayersList();

	void clearLayout( QLayout* _layout );

	void buildPlayersList();
	void updatePlayersColors();

	PlayerData* getPlayerDataByRace( const QObject* _race );
	PlayerData* getPlayerDataByType( const QObject* _type );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

/*---------------------------------------------------------------------------*/

	QLabel*			m_mapPreview;
	QVBoxLayout*	m_playersLayout;

	QListWidget*	m_landscapesList;
	QLineEdit*		m_connectToIp;
	QLineEdit*		m_connectToPort;

	QPushButton*	m_createButton;
	QPushButton*	m_connectButton;
	QPushButton*	m_startButton;
	QPushButton*	m_cancelButton;

	QStringList		m_nonePlayerTypes;
	QStringList		m_hasPlayerTypes;

/*---------------------------------------------------------------------------*/

	typedef
		std::map< Core::LandscapeModel::IPlayer::Id, PlayerData >
		PlayersDataCollection;
	typedef
		PlayersDataCollection::iterator
		PlayersDataCollectionIterator;

	PlayersDataCollection m_playersData;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_MULTIPLAYER_DIALOG_HPP__
