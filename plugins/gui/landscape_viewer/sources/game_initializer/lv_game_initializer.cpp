
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/game_initializer/lv_game_initializer.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


GameInitializer::GameInitializer( const IEnvironment& _environment )
	:	m_environment( _environment )
{
} // GameInitializer::GameInitializer


/*---------------------------------------------------------------------------*/


GameInitializer::~GameInitializer()
{
} // GameInitializer::~GameInitializer


/*---------------------------------------------------------------------------*/


void
GameInitializer::run() const
{
	QString fileName = m_environment.showOpenFileDialog();

	m_environment.initializeLandscapeModel( fileName );
	m_environment.showCurrentLandscapeInView();

} // GameInitializer::run


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
