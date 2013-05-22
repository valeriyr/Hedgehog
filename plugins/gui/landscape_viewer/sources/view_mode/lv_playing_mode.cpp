
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/view_mode/lv_playing_mode.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "landscape_viewer/sources/views/lv_description_view.hpp"
#include "landscape_viewer/sources/views/lv_landscape_view.hpp"
#include "landscape_viewer/sources/views/lv_minimap_view.hpp"

#include "window_manager/ih/wm_iview.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


PlayingMode::PlayingMode( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_descriptionView( new DescriptionView() )
	,	m_landscapeView( new LandscapeView( _environment ) )
	,	m_minimapView( new MinimapView( _environment ) )
{
	m_environment.addFrameworkView( m_landscapeView, Framework::GUI::WindowManager::ViewPosition::Center );
	m_environment.addFrameworkView( m_minimapView, Framework::GUI::WindowManager::ViewPosition::Right );
	m_environment.addFrameworkView( m_descriptionView, Framework::GUI::WindowManager::ViewPosition::Right );

} // PlayingMode::PlayingMode


/*---------------------------------------------------------------------------*/


PlayingMode::~PlayingMode()
{
	m_environment.removeFrameworkView( m_descriptionView );
	m_environment.removeFrameworkView( m_minimapView );
	m_environment.removeFrameworkView( m_landscapeView );

} // PlayingMode::~PlayingMode


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
PlayingMode::getCurrentLandscape() const
{
	return m_environment.getLandscape();

} // PlayingMode::getCurrentLandscape


/*---------------------------------------------------------------------------*/


QString
PlayingMode::getLandscapeFilePath() const
{
	return m_landscapeFilePath;

} // PlayingMode::getLandscapeFilePath


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
	m_landscapeFilePath = _filePath;
	m_environment.initializeLandscape( _filePath );

	m_landscapeView->landscapeWasOpened();
	m_descriptionView->landscapeWasOpened( *m_environment.getLandscape(), _filePath );
	m_minimapView->landscapeWasOpened( *m_environment.getLandscape() );

	m_environment.runGameManager();

} // PlayingMode::openLandscape


/*---------------------------------------------------------------------------*/


void
PlayingMode::closeLandscape()
{
	m_environment.stopGameManager();

	m_minimapView->landscapeWasClosed();
	m_descriptionView->landscapeWasClosed();
	m_landscapeView->landscapeWasClosed();

	m_environment.closeLandscape();

} // PlayingMode::closeLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
