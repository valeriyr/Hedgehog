
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_editor_controller/le_landscape_editor_controller.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"
#include "landscape_editor/sources/views/le_ilandscape_editor_view.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "landscape_model/ih/lm_ilandscape_editor.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeEditorController::LandscapeEditorController( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_landscapeFilePath()
	,	m_editableLandscape()
{
} // LandscapeEditorController::LandscapeEditorController


/*---------------------------------------------------------------------------*/


LandscapeEditorController::~LandscapeEditorController()
{
} // LandscapeEditorController::~LandscapeEditorController


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::newLandscape()
{
	m_landscapeFilePath = "c:/temp/new.hmap";
	m_editableLandscape = m_environment.getLandscapeEditor()->createLandscape( 60, 30 );

	landscapeWasOpened();

} // LandscapeEditorController::newLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::openLandscape()
{
	m_landscapeFilePath = m_environment.getDialogsManager()->getOpenFileName( "*.hmap" );

	if ( !m_landscapeFilePath.isEmpty() )
	{
		m_editableLandscape = m_environment.getLandscapeEditor()->loadLandscape( m_landscapeFilePath );
		landscapeWasOpened();
	}

} // LandscapeEditorController::openLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::closeLandscape()
{
	m_landscapeFilePath.clear();
	m_editableLandscape.reset();

	m_environment.getDescriptionView()->landscapeWasClosed();
	m_environment.getObjectsView()->landscapeWasClosed();
	m_environment.getEditorView()->landscapeWasClosed();
	m_environment.getMinimapView()->landscapeWasClosed();

} // LandscapeEditorController::closeLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::saveLandscape()
{
	if ( m_editableLandscape )
		m_environment.getLandscapeEditor()
			->saveLandscape( *m_editableLandscape, m_landscapeFilePath );

} // LandscapeEditorController::saveLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::saveAsLandscape()
{
	QString landscapeFilePath = m_environment.getDialogsManager()->getSaveFileName( "*.hmap" );
	m_environment.getLandscapeEditor()
		->saveLandscape( *m_editableLandscape, landscapeFilePath );

} // LandscapeEditorController::saveAsLandscape


/*---------------------------------------------------------------------------*/


const QString&
LandscapeEditorController::getLandscapeFilePath() const
{
	return m_landscapeFilePath;

} // LandscapeEditorController::getLandscapeFilePath


/*---------------------------------------------------------------------------*/


Plugins::Core::LandscapeModel::IEditableLandscape::Ptr
LandscapeEditorController::getEditableLandscape() const
{
	return m_editableLandscape;

} // LandscapeEditorController::getEditableLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::landscapeWasOpened()
{
	m_environment.getDescriptionView()->landscapeWasOpened();
	m_environment.getObjectsView()->landscapeWasOpened();
	m_environment.getEditorView()->landscapeWasOpened();
	m_environment.getMinimapView()->landscapeWasOpened();

} // LandscapeEditorController::getEditableLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
