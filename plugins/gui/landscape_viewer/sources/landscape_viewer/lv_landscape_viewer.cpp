
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/landscape_viewer/lv_landscape_viewer.hpp"

#include "landscape_viewer/sources/view_mode/lv_editing_mode.hpp"
#include "landscape_viewer/sources/view_mode/lv_playing_mode.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeViewer::LandscapeViewer( const IEnvironment& _environment )
	:	m_environment( _environment )
	,	m_viewMode()
{
	ensurePlayingMode();

} // LandscapeViewer::LandscapeViewer


/*---------------------------------------------------------------------------*/


LandscapeViewer::~LandscapeViewer()
{
} // LandscapeViewer::~LandscapeViewer


/*---------------------------------------------------------------------------*/


bool
LandscapeViewer::isPlayingMode() const
{
	return m_viewMode->isPlayingMode();

} // LandscapeViewer::isPlayingMode


/*---------------------------------------------------------------------------*/


bool
LandscapeViewer::isEditingMode() const
{
	return m_viewMode->isEditingMode();

} // LandscapeViewer::isEditingMode


/*---------------------------------------------------------------------------*/


void
LandscapeViewer::ensureLandscapeEditingMode()
{
	if ( !m_viewMode || !m_viewMode->isEditingMode() )
		m_viewMode = boost::intrusive_ptr< IViewMode >( new EditingMode( m_environment ) );

} // LandscapeViewer::ensureLandscapeEditingMode


/*---------------------------------------------------------------------------*/


void
LandscapeViewer::ensurePlayingMode()
{
	if ( !m_viewMode || !m_viewMode->isPlayingMode() )
		m_viewMode = boost::intrusive_ptr< IViewMode >( new PlayingMode( m_environment ) );

} // LandscapeViewer::ensurePlayingMode


/*---------------------------------------------------------------------------*/


QString
LandscapeViewer::getLandscapeFilePath() const
{
	return m_viewMode->getLandscapeFilePath();

} // LandscapeViewer::getLandscapeFilePath


/*---------------------------------------------------------------------------*/


void
LandscapeViewer::openLandscape( const QString& _filePath )
{
	m_viewMode->openLandscape( _filePath );

} // LandscapeViewer::openLandscape


/*---------------------------------------------------------------------------*/


void
LandscapeViewer::closeLandscape()
{
	m_viewMode->closeLandscape();

} // LandscapeViewer::closeLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
LandscapeViewer::getEditingLandscape() const
{
	return m_viewMode->getEditingLandscape();

} // LandscapeViewer::getEditingLandscape


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
