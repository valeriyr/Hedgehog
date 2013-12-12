
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

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::shared_ptr< QWidget > m_mainWidget;

	QCheckBox* m_tarrainMapVisibility;

	QString m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_SETTINGS_VIEW_HPP__
