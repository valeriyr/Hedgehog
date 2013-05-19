
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/landscape_viewer/lv_landscape_viewer.hpp"

#include "landscape_viewer/sources/view_mode/lv_editing_mode.hpp"
#include "landscape_viewer/sources/view_mode/lv_playing_mode.hpp"


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


boost::intrusive_ptr< IViewMode >
LandscapeViewer::getViewMode() const
{
	return m_viewMode;

} // LandscapeViewer::getViewMode


/*---------------------------------------------------------------------------*/


void
LandscapeViewer::ensureLandscapeEditingMode()
{
	if ( !m_viewMode->isEditingMode() )
		m_viewMode = boost::intrusive_ptr< IViewMode >( new EditingMode( m_environment ) );

} // LandscapeViewer::ensureLandscapeEditingMode


/*---------------------------------------------------------------------------*/


void
LandscapeViewer::ensurePlayingMode()
{
	if ( !m_viewMode->isPlayingMode() )
		m_viewMode = boost::intrusive_ptr< IViewMode >( new PlayingMode( m_environment ) );

} // LandscapeViewer::ensurePlayingMode


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
