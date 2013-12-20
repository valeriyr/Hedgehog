
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/landscape_viewer/lv_landscape_viewer.hpp"

#include "landscape_viewer/sources/views/lv_description_view.hpp"
#include "landscape_viewer/sources/views/lv_landscape_view.hpp"
#include "landscape_viewer/sources/views/lv_minimap_view.hpp"
#include "landscape_viewer/sources/views/lv_objects_view.hpp"
#include "landscape_viewer/sources/views/lv_settings_view.hpp"
#include "landscape_viewer/sources/views/lv_selection_view.hpp"
#include "landscape_viewer/sources/views/lv_object_info_view.hpp"
#include "landscape_viewer/sources/views/lv_action_panel_view.hpp"

#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeViewer::LandscapeViewer( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_viewsMediator( new ViewsMediator() )
	,	m_descriptionView( new DescriptionView() )
	,	m_settingsView( new SettingsView( _environment ) )
	,	m_LandscapeView( new LandscapeView( _environment, *m_viewsMediator ) )
	,	m_minimapView( new MinimapView( _environment, *m_viewsMediator ) )
	,	m_objectsView( new ObjectsView( _environment, *m_viewsMediator ) )
	,	m_selectionView( new SelectionView( _environment ) )
	,	m_objectInfoView( new ObjectInfoView( _environment ) )
	,	m_actionPanelView( new ActionPanelView( _environment ) )
	,	m_landscapeFilePath()
{
	m_environment.addFrameworkView( m_objectsView, Framework::GUI::WindowManager::ViewPosition::Left );
	m_environment.addFrameworkView( m_settingsView, Framework::GUI::WindowManager::ViewPosition::Left );
	m_environment.addFrameworkView( m_descriptionView, Framework::GUI::WindowManager::ViewPosition::Left );
	m_environment.addFrameworkView( m_LandscapeView, Framework::GUI::WindowManager::ViewPosition::Center );
	m_environment.addFrameworkView( m_minimapView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_objectInfoView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_actionPanelView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_selectionView, Framework::GUI::WindowManager::ViewPosition::Right );

} // LandscapeViewer::LandscapeViewer


/*---------------------------------------------------------------------------*/


LandscapeViewer::~LandscapeViewer()
{
	m_environment.removeFrameworkView( m_selectionView );
	m_environment.removeFrameworkView( m_actionPanelView );
	m_environment.removeFrameworkView( m_objectInfoView );
	m_environment.removeFrameworkView( m_minimapView );
	m_environment.removeFrameworkView( m_LandscapeView );
	m_environment.removeFrameworkView( m_descriptionView );
	m_environment.removeFrameworkView( m_settingsView );
	m_environment.removeFrameworkView( m_objectsView );

} // LandscapeViewer::~LandscapeViewer


/*---------------------------------------------------------------------------*/


QString
LandscapeViewer::getLandscapeFilePath() const
{
	return m_landscapeFilePath;

} // LandscapeViewer::getLandscapeFilePath


/*---------------------------------------------------------------------------*/


void
LandscapeViewer::openLandscape( const QString& _filePath )
{
	m_environment.initializeLandscapeModel( _filePath );
	m_landscapeFilePath = _filePath;

	{
		boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
			= m_environment.getCurrentLandscape();

		m_descriptionView->landscapeWasOpened( QSize( handle->getLandscape()->getWidth(), handle->getLandscape()->getHeight() ), _filePath );
	}

	m_minimapView->landscapeWasOpened();
	m_LandscapeView->landscapeWasOpened();
	m_selectionView->landscapeWasOpened();
	m_objectInfoView->landscapeWasOpened();
	m_actionPanelView->landscapeWasOpened();

} // LandscapeViewer::openLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeViewer::closeLandscape()
{
	m_LandscapeView->landscapeWasClosed();
	m_minimapView->landscapeWasClosed();
	m_descriptionView->landscapeWasClosed();
	m_selectionView->landscapeWasClosed();
	m_objectInfoView->landscapeWasClosed();
	m_actionPanelView->landscapeWasClosed();

	m_environment.resetLandscapeModel();

	m_landscapeFilePath.clear();

} // LandscapeViewer::closeLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
