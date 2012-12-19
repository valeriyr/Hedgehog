
#ifndef __CON_MAIN_VIEW_HPP__
#define __CON_MAIN_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"
#include "messenger/ms_imessenger.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace Console {

/*---------------------------------------------------------------------------*/

class MainView
	:	public Tools::Core::BaseWrapper< Framework::GUI::WindowManager::IView >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MainView();

	virtual ~MainView();

/*---------------------------------------------------------------------------*/

	/*virtual*/ const std::string& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

	void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const std::string& _message );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	boost::shared_ptr< QTextEdit > m_consoleView;

	std::string m_viewTitle;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_MAIN_VIEW_HPP__
