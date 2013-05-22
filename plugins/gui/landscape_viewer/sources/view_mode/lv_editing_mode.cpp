
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/view_mode/lv_editing_mode.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "landscape_viewer/sources/views/lv_description_view.hpp"
#include "landscape_viewer/sources/views/lv_editor_view.hpp"
#include "landscape_viewer/sources/views/lv_minimap_view.hpp"
#include "landscape_viewer/sources/views/lv_objects_view.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


EditingMode::EditingMode( const IEnvironment& _environment )
	:	BaseMode( _environment )
	,	m_descriptionView( new DescriptionView() )
	,	m_editorView( new EditorView( _environment ) )
	,	m_minimapView( new MinimapView( _environment ) )
	,	m_objectsView( new ObjectsView( _environment ) )
{
	m_environment.addFrameworkView( m_objectsView, Framework::GUI::WindowManager::ViewPosition::Left );
	m_environment.addFrameworkView( m_editorView, Framework::GUI::WindowManager::ViewPosition::Center );
	m_environment.addFrameworkView( m_minimapView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_descriptionView, Framework::GUI::WindowManager::ViewPosition::Right );

} // EditingMode::EditingMode


/*---------------------------------------------------------------------------*/


EditingMode::~EditingMode()
{
	m_environment.removeFrameworkView( m_descriptionView );
	m_environment.removeFrameworkView( m_minimapView );
	m_environment.removeFrameworkView( m_editorView );
	m_environment.removeFrameworkView( m_objectsView );

} // EditingMode::~EditingMode


/*---------------------------------------------------------------------------*/


bool
EditingMode::isPlayingMode() const
{
	return false;

} // EditingMode::isPlayingMode


/*---------------------------------------------------------------------------*/


bool
EditingMode::isEditingMode() const
{
	return true;

} // EditingMode::isEditingMode


/*---------------------------------------------------------------------------*/


void
EditingMode::openLandscape( const QString& _filePath )
{
	m_landscapeFilePath = _filePath;

	m_editableLandscape = m_environment.tryToOpenLandscape( m_landscapeFilePath );

	if ( !m_editableLandscape )
		m_editableLandscape = m_environment.createLandscape( 300, 300 );
	
	m_descriptionView->landscapeWasOpened( *m_editableLandscape, m_landscapeFilePath );
	m_objectsView->landscapeWasOpened();
	m_minimapView->landscapeWasOpened( *m_editableLandscape );
	m_editorView->landscapeWasOpened( m_editableLandscape );

} // EditingMode::openLandscape


/*---------------------------------------------------------------------------*/


void
EditingMode::closeLandscape()
{
	m_descriptionView->landscapeWasClosed();
	m_objectsView->landscapeWasClosed();
	m_minimapView->landscapeWasClosed();
	m_editorView->landscapeWasClosed();

	m_landscapeFilePath.clear();
	m_editableLandscape.reset();

} // EditingMode::closeLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
