
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/commands_executor/lv_commands_executor.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"

#include "landscape_viewer/sources/dialogs/lv_multiplayer_dialog.hpp"

#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/h/lm_resources.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


CommandsExecutor::CommandsExecutor( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // CommandsExecutor::CommandsExecutor


/*---------------------------------------------------------------------------*/


CommandsExecutor::~CommandsExecutor()
{
} // CommandsExecutor::~CommandsExecutor


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::newLandscape()
{
	m_environment.getLandscapeViewer()->closeLandscape();
	m_environment.getLandscapeViewer()->openLandscape( "" );

} // CommandsExecutor::newLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::openLandscape()
{
	QString landscapeFilePath = m_environment.showOpenFileDialog();

	if ( !landscapeFilePath.isEmpty() )
	{
		m_environment.getLandscapeViewer()->closeLandscape();
		m_environment.getLandscapeViewer()->openLandscape( landscapeFilePath );
	}

} // CommandsExecutor::openLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::closeLandscape()
{
	m_environment.getLandscapeViewer()->closeLandscape();

} // CommandsExecutor::closeLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::saveLandscape()
{
	QString fileName = m_environment.getLandscapeViewer()->getLandscapeFilePath();

	if ( m_environment.getLandscapeViewer()->getLandscapeFilePath().isEmpty() )
		fileName = m_environment.showSaveFileDialog();

	m_environment.lockModel()->getLandscapeModel()->saveModel( fileName );

} // CommandsExecutor::saveLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::saveAsLandscape()
{
	m_environment.lockModel()->getLandscapeModel()->saveModel( m_environment.showSaveFileDialog() );

} // CommandsExecutor::saveAsLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::startGame()
{
	MultiplayerDialog multiplayerDialog( m_environment );
	multiplayerDialog.exec();

} // CommandsExecutor::startGame


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
