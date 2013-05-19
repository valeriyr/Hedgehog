
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/view_mode/lv_playing_mode.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


PlayingMode::PlayingMode( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // PlayingMode::PlayingMode


/*---------------------------------------------------------------------------*/


PlayingMode::~PlayingMode()
{
} // PlayingMode::~PlayingMode


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
PlayingMode::getCurrentLandscape() const
{
	return boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >();

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
	/*m_environment.initializeLandscape( fileName );
		m_environment.showCurrentLandscape();
		m_environment.runGameManager();*/

} // PlayingMode::openLandscape


/*---------------------------------------------------------------------------*/


void
PlayingMode::closeLandscape()
{
	/*m_environment.stopGameManager();
	m_environment.clearLandscapeView();
	m_environment.closeLandscape();*/

} // PlayingMode::closeLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
