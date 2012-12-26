
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


QString
DialogsManager::getExistingDirectory()
{
	QString result = QFileDialog::getExistingDirectory(
			&m_mainWindow
		,	"Open Directory"
		,	m_lastOpenedDirectory );

	if ( !result.isEmpty() )
		m_lastOpenedDirectory = result;

	 return result;

} // DialogsManager::getExistingDirectory


/*---------------------------------------------------------------------------*/


QString
DialogsManager::getOpenFileName( const QString& _filter )
{
	QString result = QFileDialog::getOpenFileName(
			&m_mainWindow
		,	"Open File"
		,	_filter
		,	m_lastOpenedDirectory );

	if ( !result.isEmpty() )
		setLastOpenedDirectory( result );

	return result;

} // DialogsManager::getOpenFileName


/*---------------------------------------------------------------------------*/


QString
DialogsManager::getSaveFileName( const QString& _filter )
{
	QString result = QFileDialog::getSaveFileName(
			&m_mainWindow
		,	"Save File"
		,	_filter
		,	m_lastOpenedDirectory );

	if ( !result.isEmpty() )
		setLastOpenedDirectory( result );

	return result;

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
