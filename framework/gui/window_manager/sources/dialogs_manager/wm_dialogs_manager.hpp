
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

	/*virtual*/ QString getExistingDirectory();

	/*virtual*/ QString getOpenFileName( const QString& _filter );

	/*virtual*/ QString getSaveFileName( const QString& _filter );

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
