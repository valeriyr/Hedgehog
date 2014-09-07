
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/commands_executor/lv_commands_executor.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"
#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
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
	// TODO: need to implement editor mode
	openLandscape( "" );

} // CommandsExecutor::newLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::openLandscape()
{
	QString landscapeFilePath = m_environment.showOpenFileDialog();

	if ( !landscapeFilePath.isEmpty() )
		openLandscape( landscapeFilePath );

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
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	QString fileName = locker->getLandscapeModel()->getFilePath();

	if ( fileName.isEmpty() )
		fileName = m_environment.showSaveFileDialog();

	locker->getLandscapeModel()->saveModel( fileName );

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
	if ( m_environment.lockModel()->getLandscapeModel()->isSimulationRunning() )
	{
		m_environment.printMessage( Tools::Core::IMessenger::MessegeLevel::Error, Resources::Messages::SimulationIsRunningNow );
		return;
	}

	MultiplayerDialog multiplayerDialog( m_environment );
	multiplayerDialog.exec();

} // CommandsExecutor::startGame


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::openLandscape( const QString& _fileName )
{
	m_environment.getLandscapeViewer()->closeLandscape();
	m_environment.getLandscapeViewer()->initLandscape( _fileName );

	m_environment.lockModel()->getLandscapeModel()->setupSinglePlayerGame();

	m_environment.getLandscapeViewer()->startSimulation();

} // CommandsExecutor::openLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
