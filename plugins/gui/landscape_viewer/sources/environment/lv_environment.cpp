
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"
#include "landscape_viewer/sources/game_initializer/lv_igame_initializer.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_manager.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


Environment::Environment( const PluginInstance& _pluginInstance )
	:	m_pluginInstance( _pluginInstance )
{
} // Environment::Environment


/*---------------------------------------------------------------------------*/


Environment::~Environment()
{
} // Environment::~Environment


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IGameInitializer >
Environment::getGameInitializer() const
{
	return m_pluginInstance.getGameInitializer();

} // Environment::getGameInitializer


/*---------------------------------------------------------------------------*/


QString
Environment::showOpenFileDialog() const
{
	return m_pluginInstance.getDialogsManager()->getOpenFileName( "*.hmap" );

} // Environment::showOpenFileDialog


/*---------------------------------------------------------------------------*/


void
Environment::initializeLandscapeModel( const QString& _fileName ) const
{
	m_pluginInstance.getLandscapeManager()->initCurrentLandscape( _fileName );

} // Environment::initializeLandscapeModel


/*---------------------------------------------------------------------------*/


void
Environment::showCurrentLandscapeInView() const
{
} // Environment::showCurrentLandscapeInView


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
