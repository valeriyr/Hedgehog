
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/commands_executor/lv_commands_executor.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


CommandsExecutor::CommandsExecutor( const IEnvironment& _environment, ILandscapeViewer& _landscapeViewer )
	:	m_environment( _environment )
	,	m_landscapeViewer( _landscapeViewer )
{
} // CommandsExecutor::CommandsExecutor


/*---------------------------------------------------------------------------*/


CommandsExecutor::~CommandsExecutor()
{
} // CommandsExecutor::~CommandsExecutor


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::runGame()
{
	QString fileName = m_environment.showOpenFileDialog();

	if ( !fileName.isEmpty() )
	{
		m_landscapeViewer.ensurePlayingMode();
		m_landscapeViewer.openLandscape( fileName );
	}

} // CommandsExecutor::runGame


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::stopGame()
{
	m_landscapeViewer.closeLandscape();

} // CommandsExecutor::stopGame


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::newLandscape()
{
	m_landscapeViewer.ensureLandscapeEditingMode();

	if ( m_landscapeViewer.getCurrentLandscape() )
		m_landscapeViewer.closeLandscape();

	m_landscapeViewer.openLandscape( "c:/temp/new.hmap" );

} // CommandsExecutor::newLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::openLandscape()
{
	QString landscapeFilePath = m_environment.showOpenFileDialog();

	if ( !landscapeFilePath.isEmpty() )
	{
		m_landscapeViewer.ensureLandscapeEditingMode();

		if ( m_landscapeViewer.getCurrentLandscape() )
			m_landscapeViewer.closeLandscape();

		m_landscapeViewer.openLandscape( landscapeFilePath );
	}

} // CommandsExecutor::openLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::closeLandscape()
{
	m_landscapeViewer.closeLandscape();

} // CommandsExecutor::closeLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::saveLandscape()
{
	if ( m_landscapeViewer.getCurrentLandscape() )
		m_environment.saveLandscape(
				m_landscapeViewer.getLandscapeFilePath()
			,	*m_landscapeViewer.getCurrentLandscape() );

} // CommandsExecutor::saveLandscape


/*---------------------------------------------------------------------------*/


void
CommandsExecutor::saveAsLandscape()
{
	QString landscapeFilePath = m_environment.showSaveFileDialog();
	m_environment.saveLandscape(
			m_landscapeViewer.getLandscapeFilePath()
		,	*m_landscapeViewer.getCurrentLandscape() );

} // CommandsExecutor::saveAsLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/