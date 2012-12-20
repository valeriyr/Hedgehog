
#ifndef __WM_DIALOGS_MANAGER_HPP__
#define __WM_DIALOGS_MANAGER_HPP__

/*---------------------------------------------------------------------------*/

#include "window_manager/ih/wm_idialogs_manager.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/

class DialogsManager
	:	public Tools::Core::BaseWrapper< IDialogsManager >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	DialogsManager( QWidget& _mainWindow );

	virtual ~DialogsManager();

/*---------------------------------------------------------------------------*/

	/*virtual*/ std::string getExistingDirectory();

	/*virtual*/ std::string getOpenFileName( const std::string& _filter );

	/*virtual*/ std::string getSaveFileName( const std::string& _filter );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void setLastOpenedDirectory( const QString& _filePath );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	QWidget& m_mainWindow;

	QString m_lastOpenedDirectory;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/

#endif // __WM_IWINDOW_MANAGER_HPP__
