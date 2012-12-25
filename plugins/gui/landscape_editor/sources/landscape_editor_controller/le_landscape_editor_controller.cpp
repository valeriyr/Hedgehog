
#include "landscape_editor/sources/ph/le_ph.hpp"

#include "landscape_editor/sources/landscape_editor_controller/le_landscape_editor_controller.hpp"

#include "landscape_editor/sources/environment/le_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/


LandscapeEditorController::LandscapeEditorController( const IEnvironment& _environment )
	:	m_environment( _environment )
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
} // LandscapeEditorController::newLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::openLandscape()
{
	/*QString fileName( m_environment.getDialogsManager()->getOpenFileName( "*.hmap" ) );

	Plugins::Core::LandscapeModel::IEditableLandscape::Ptr landscape
		= m_environment.getLandscapeEditor()->loadLandscape( fileName );

	m_environment.getDescriptionView()->landscapeWasOpened( landscape );
	m_environment.getObjectsView()->landscapeWasOpened( landscape );
	m_environment.getEditorView()->landscapeWasOpened( landscape );*/

} // LandscapeEditorController::newLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::closeLandscape()
{
} // LandscapeEditorController::newLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeEditorController::saveLandscape()
{
} // LandscapeEditorController::newLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
