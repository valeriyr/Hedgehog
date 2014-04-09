
#ifndef __LV_PLAYER_INFO_VIEW_HPP__
#define __LV_PLAYER_INFO_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

#include "landscape_model/h/lm_constants.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class PlayerInfoView
	:	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	PlayerInfoView( const IEnvironment& _environment );

	virtual ~PlayerInfoView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QString& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onResourceValueChanged( const Framework::Core::EventManager::Event& _event );

	void onCurrentTickNumberChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void setDefaultText();

	void setInfoText();

	void updatePlayersInfo();

	void updateTickInfo( const Plugins::Core::LandscapeModel::TickType& _tick );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	QString m_viewTitle;

	QString m_playersInfo;
	QString m_tickInfo;

	boost::shared_ptr< QTextEdit > m_mainWidget;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_PLAYER_INFO_VIEW_HPP__
