
#ifndef __LV_MULTIPLAYER_DIALOG_HPP__
#define __LV_MULTIPLAYER_DIALOG_HPP__

#include "landscape_model/h/lm_start_point.hpp"

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

	void onPlayerColorChanged();

/*---------------------------------------------------------------------------*/

private:

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

/*---------------------------------------------------------------------------*/

	struct PlayerData
	{
		PlayerData(
				QComboBox& _type
			,	QComboBox& _race
			,	QComboBox& _color
			)
			:	m_type( _type )
			,	m_race( _race )
			,	m_color( _color )
		{}

		QComboBox& m_type;
		QComboBox& m_race;
		QComboBox& m_color;
	};

	typedef
		std::map< Core::LandscapeModel::StartPoint::Id, PlayerData >
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
