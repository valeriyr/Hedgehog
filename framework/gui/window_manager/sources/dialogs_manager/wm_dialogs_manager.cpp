
#include "window_manager/sources/ph/wm_ph.hpp"

#include "window_manager/sources/dialogs_manager/wm_dialogs_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Framework {
namespace GUI {
namespace WindowManager {

/*---------------------------------------------------------------------------*/


DialogsManager::DialogsManager( QWidget& _mainWindow )
	:	m_mainWindow( _mainWindow )
	,	m_lastOpenedDirectory()
{
} // DialogsManager::DialogsManager


/*---------------------------------------------------------------------------*/


DialogsManager::~DialogsManager()
{
} // DialogsManager::~DialogsManager


/*---------------------------------------------------------------------------*/


std::string
DialogsManager::getExistingDirectory()
{
	 m_lastOpenedDirectory = QFileDialog::getExistingDirectory(
			&m_mainWindow
		,	"Open Directory"
		,	m_lastOpenedDirectory );

	 return m_lastOpenedDirectory.toLocal8Bit().data();

} // DialogsManager::getExistingDirectory


/*---------------------------------------------------------------------------*/


std::string
DialogsManager::getOpenFileName( const std::string& _filter )
{
	QString result = QFileDialog::getOpenFileName(
			&m_mainWindow
		,	"Open File"
		,	_filter.c_str()
		,	m_lastOpenedDirectory );

	setLastOpenedDirectory( result );

	return result.toLocal8Bit().data();

} // DialogsManager::getOpenFileName


/*---------------------------------------------------------------------------*/


std::string
DialogsManager::getSaveFileName( const std::string& _filter )
{
	QString result = QFileDialog::getSaveFileName(
			&m_mainWindow
		,	"Save File"
		,	_filter.c_str()
		,	m_lastOpenedDirectory );

	setLastOpenedDirectory( result );

	return result.toLocal8Bit().data();

} // DialogsManager::getSaveFileName


/*---------------------------------------------------------------------------*/


void
DialogsManager::setLastOpenedDirectory( const QString& _filePath )
{
	m_lastOpenedDirectory = QFileInfo( _filePath ).absoluteDir().path();

} // DialogsManager::setLastOpenedDirectory


/*---------------------------------------------------------------------------*/

} // namespace WindowManager
} // namespace GUI
} // namespace Framework

/*---------------------------------------------------------------------------*/
