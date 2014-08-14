
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
#include "landscape_viewer/sources/views/lv_object_status_view.hpp"
#include "landscape_viewer/sources/views/lv_player_info_view.hpp"

#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/h/lm_events.hpp"

#include "multithreading_manager/h/mm_external_resources.hpp"

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
	,	m_actionPanelView( new ActionPanelView( _environment, *m_viewsMediator ) )
	,	m_objectStatusView( new ObjectStatusView( _environment ) )
	,	m_playerInfoView( new PlayerInfoView( _environment ) )
	,	m_landscapeFilePath()
{
	m_environment.addFrameworkView( m_objectsView, Framework::GUI::WindowManager::ViewPosition::Left );
	m_environment.addFrameworkView( m_settingsView, Framework::GUI::WindowManager::ViewPosition::Left );
	m_environment.addFrameworkView( m_descriptionView, Framework::GUI::WindowManager::ViewPosition::Left );
	m_environment.addFrameworkView( m_LandscapeView, Framework::GUI::WindowManager::ViewPosition::Center );
	m_environment.addFrameworkView( m_minimapView, Framework::GUI::WindowManager::ViewPosition::Bottom );
	m_environment.addFrameworkView( m_playerInfoView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_objectInfoView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_objectStatusView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_actionPanelView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_selectionView, Framework::GUI::WindowManager::ViewPosition::Right );

} // LandscapeViewer::LandscapeViewer


/*---------------------------------------------------------------------------*/


LandscapeViewer::~LandscapeViewer()
{
	closeLandscape();

	m_environment.removeFrameworkView( m_selectionView );
	m_environment.removeFrameworkView( m_actionPanelView );
	m_environment.removeFrameworkView( m_objectStatusView );
	m_environment.removeFrameworkView( m_objectInfoView );
	m_environment.removeFrameworkView( m_playerInfoView );
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
	boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		locker = m_environment.lockModel();

	m_landscapeFilePath = _filePath;

	locker->getLandscapeModel()->initLandscape( _filePath );

	Plugins::Core::LandscapeModel::ILandscapeModel::PlayersSturtupDataCollection collection;

	Core::LandscapeModel::ILandscape::StartPointsIterator iterator
		= locker->getLandscapeModel()->getLandscape()->getStartPointsIterator();

	while ( iterator->isValid() )
	{
		collection.push_back(
			Plugins::Core::LandscapeModel::ILandscapeModel::PlayerStartupData(
					rand() % 2 ? "Orc" : "Human"
				,	iterator->current().m_id
				,	Plugins::Core::LandscapeModel::PlayerType::Player ) );
		iterator->next();
	}

	locker->getLandscapeModel()->initPlayers( m_landscapeFilePath, collection );

	boost::intrusive_ptr< Core::LandscapeModel::ILandscape >
		landscape = locker->getLandscapeModel()->getLandscape();

	m_descriptionView->landscapeWasOpened( QSize( landscape->getWidth(), landscape->getHeight() ), m_landscapeFilePath );
	m_playerInfoView->landscapeWasOpened();
	m_minimapView->landscapeWasOpened();
	m_LandscapeView->landscapeWasOpened();
	m_selectionView->landscapeWasOpened();
	m_objectInfoView->landscapeWasOpened();
	m_actionPanelView->landscapeWasOpened();
	m_objectStatusView->landscapeWasOpened();

	locker->getLandscapeModel()->startSimulation();

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
	m_objectStatusView->landscapeWasClosed();
	m_playerInfoView->landscapeWasClosed();

	m_landscapeFilePath.clear();

	m_environment.lockModel()->getLandscapeModel()->resetModel();

} // LandscapeViewer::closeLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
