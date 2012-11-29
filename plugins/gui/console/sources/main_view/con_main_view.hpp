
#ifndef __CON_MAIN_VIEW_HPP__
#define __CON_MAIN_VIEW_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_iview.hpp"

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

	/*virtual*/ const Framework::GUI::WindowManager::ViewPosition::Enum getViewPossition() const;

	/*virtual*/ const std::string& getViewTitle() const;

	/*virtual*/ QWidget* getViewWidget() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void viewWasClosed();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	/*boost::shared_ptr< QTextEdit >*/ QTextEdit* m_consoleView;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace Console
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __CON_MAIN_VIEW_HPP__
