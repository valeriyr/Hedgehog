
#ifndef __LV_MULTIPLAYER_DIALOG_HPP__
#define __LV_MULTIPLAYER_DIALOG_HPP__


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

	void onLandscapeSelected( QListWidgetItem* _oldItem, QListWidgetItem* _newItem );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void createWidgets();

	void initWidgets();

	void connectWidgets();
	void disconnectWidgets();

	void updateLandscapesList();
	void currentLandscapeWasChanged( const QString& _landscapeName );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

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

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_MULTIPLAYER_DIALOG_HPP__
