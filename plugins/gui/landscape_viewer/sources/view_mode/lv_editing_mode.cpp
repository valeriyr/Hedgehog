
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/view_mode/lv_editing_mode.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "landscape_viewer/sources/views/lv_description_view.hpp"
#include "landscape_viewer/sources/views/lv_editor_view.hpp"
#include "landscape_viewer/sources/views/lv_minimap_view.hpp"
#include "landscape_viewer/sources/views/lv_objects_view.hpp"
#include "landscape_viewer/sources/views/lv_settings_view.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


EditingMode::EditingMode( const IEnvironment& _environment )
	:	BaseMode( _environment )
	,	m_landscape()
	,	m_descriptionView( new DescriptionView() )
	,	m_settingsView( new SettingsView( _environment ) )
	,	m_editorView( new EditorView( _environment, *m_viewsMediator ) )
	,	m_minimapView( new MinimapView( _environment, *m_viewsMediator ) )
	,	m_objectsView( new ObjectsView( _environment, *m_viewsMediator ) )
{
	m_environment.addFrameworkView( m_objectsView, Framework::GUI::WindowManager::ViewPosition::Left );
	m_environment.addFrameworkView( m_editorView, Framework::GUI::WindowManager::ViewPosition::Center );
	m_environment.addFrameworkView( m_minimapView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_descriptionView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_settingsView, Framework::GUI::WindowManager::ViewPosition::Right );

} // EditingMode::EditingMode


/*---------------------------------------------------------------------------*/


EditingMode::~EditingMode()
{
	m_environment.removeFrameworkView( m_settingsView );
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
	m_landscape = m_environment.tryToOpenLandscape( _filePath );

	if ( !m_landscape )
		m_landscape = m_environment.createLandscape( 20, 20 );

	landscapeWasOpened( _filePath );

	m_descriptionView->landscapeWasOpened( QSize( m_landscape->getWidth(), m_landscape->getHeight() ), m_landscapeFilePath );
	m_objectsView->landscapeWasOpened();
	m_minimapView->landscapeWasOpenedInEditor( m_landscape );
	m_editorView->landscapeWasOpened( m_landscape );

} // EditingMode::openLandscape


/*---------------------------------------------------------------------------*/


void
EditingMode::closeLandscape()
{
	m_descriptionView->landscapeWasClosed();
	m_objectsView->landscapeWasClosed();
	m_minimapView->landscapeWasClosed();
	m_editorView->landscapeWasClosed();

	landscapeWasClosed();

	m_landscape.reset();

} // EditingMode::closeLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
EditingMode::getEditingLandscape() const
{
	return m_landscape;

} // EditingMode::getEditingLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
