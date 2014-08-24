
#ifndef __LV_SETTINGS_VIEW_HPP__
#define __LV_SETTINGS_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class SettingsView
	:	public QObject
	,	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	SettingsView( const IEnvironment& _environment );

	virtual ~SettingsView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

private slots:

/*---------------------------------------------------------------------------*/

	void onTarrainMapVisibilityChanged( bool _visibility );

	void onSkinIdChanged( const QString& _skinId );

	void onUpdateMinimapChanged( bool _visibility );

	void onPlaySoundChanged( bool _play );

	void onIpChanged( const QString& _ip );

	void onPortChanged( const QString& _port );

	void onConnectionTimeOutChanged( const QString& _timeOut );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::shared_ptr< QWidget > m_mainWidget;

	QCheckBox* m_tarrainMapVisibility;

	QComboBox* m_skinId;

	QCheckBox* m_updateMinimap;

	QCheckBox* m_playSound;

	QLineEdit* m_ip;
	QLineEdit* m_port;
	QLineEdit* m_connectionTimeOut;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_SETTINGS_VIEW_HPP__
