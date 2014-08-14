
#ifndef __LV_MULTIPLAYER_DIALOG_HPP__
#define __LV_MULTIPLAYER_DIALOG_HPP__

#include "landscape_model/h/lm_start_point.hpp"

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscape;
		}
	}
}

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

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void createWidgets();

	void initWidgets();

	void connectWidgets();
	void disconnectWidgets();

	void updateLandscapesList();
	void currentLandscapeWasChanged( const QString& _landscapeName );

	void updateMapPreview( const Core::LandscapeModel::ILandscape& _landscape );
	void updatePlayersList( const Core::LandscapeModel::ILandscape& _landscape );

	void clearLayout( QLayout* _layout );

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
		PlayerData( const QString _race, const QColor _color )
			:	m_race( _race )
			,	m_color( _color )
		{}

		QString m_race;
		QColor m_color;
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
