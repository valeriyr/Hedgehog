
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/game_initializer/lv_game_initializer.hpp"

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


GameInitializer::GameInitializer( IEnvironment& _environment )
	:	m_environment( _environment )
{
} // GameInitializer::GameInitializer


/*---------------------------------------------------------------------------*/


GameInitializer::~GameInitializer()
{
} // GameInitializer::~GameInitializer


/*---------------------------------------------------------------------------*/


void
GameInitializer::run()
{
	QString fileName = m_environment.showOpenFileDialog();

	if ( !fileName.isEmpty() )
	{
		m_environment.initializeLandscapeModel( fileName );
		m_environment.showCurrentLandscapeModel();
	}

} // GameInitializer::run


/*---------------------------------------------------------------------------*/


void
GameInitializer::stop()
{
} // GameInitializer::stop


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
