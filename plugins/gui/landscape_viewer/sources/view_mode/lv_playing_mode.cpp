
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/view_mode/lv_playing_mode.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

#include "landscape_viewer/sources/views/lv_description_view.hpp"
#include "landscape_viewer/sources/views/lv_settings_view.hpp"
#include "landscape_viewer/sources/views/lv_landscape_view.hpp"
#include "landscape_viewer/sources/views/lv_minimap_view.hpp"
#include "landscape_viewer/sources/views/views_mediator/lv_views_mediator.hpp"

#include "window_manager/ih/wm_iview.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


PlayingMode::PlayingMode( const IEnvironment& _environment )
	:	BaseMode( _environment )
	,	m_descriptionView( new DescriptionView() )
	,	m_settingsView( new SettingsView( _environment ) )
	,	m_landscapeView( new LandscapeView( _environment, *m_viewsMediator ) )
	,	m_minimapView( new MinimapView( _environment, *m_viewsMediator ) )
	,	m_timer()
{
	m_environment.addFrameworkView( m_landscapeView, Framework::GUI::WindowManager::ViewPosition::Center );
	m_environment.addFrameworkView( m_minimapView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_descriptionView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_settingsView, Framework::GUI::WindowManager::ViewPosition::Right );

	QObject::connect( &m_timer, SIGNAL( timeout() ), m_viewsMediator.get(), SIGNAL( updateTimerFired() ) );

} // PlayingMode::PlayingMode


/*---------------------------------------------------------------------------*/


PlayingMode::~PlayingMode()
{
	QObject::disconnect( &m_timer, SIGNAL( timeout() ), m_viewsMediator.get(), SIGNAL( updateTimerFired() ) );

	m_environment.removeFrameworkView( m_settingsView );
	m_environment.removeFrameworkView( m_descriptionView );
	m_environment.removeFrameworkView( m_minimapView );
	m_environment.removeFrameworkView( m_landscapeView );

} // PlayingMode::~PlayingMode


/*---------------------------------------------------------------------------*/


bool
PlayingMode::isPlayingMode() const
{
	return true;

} // PlayingMode::isPlayingMode


/*---------------------------------------------------------------------------*/


bool
PlayingMode::isEditingMode() const
{
	return false;

} // PlayingMode::isEditingMode


/*---------------------------------------------------------------------------*/


void
PlayingMode::openLandscape( const QString& _filePath )
{
	m_environment.initializeLandscapeModel( _filePath );
	landscapeWasOpened( _filePath );

	{
		boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle > handle
			= m_environment.getCurrentLandscape();

		m_descriptionView->landscapeWasOpened( QSize( handle->getLandscape()->getWidth(), handle->getLandscape()->getHeight() ), _filePath );
	}

	m_minimapView->landscapeWasOpened();
	m_landscapeView->landscapeWasOpened();

	m_timer.start( ms_updatePeriod );

} // PlayingMode::openLandscape


/*---------------------------------------------------------------------------*/


void
PlayingMode::closeLandscape()
{
	m_timer.stop();

	m_landscapeView->landscapeWasClosed();
	m_minimapView->landscapeWasClosed();
	m_descriptionView->landscapeWasClosed();

	m_environment.resetLandscapeModel();

	landscapeWasClosed();

} // PlayingMode::closeLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
