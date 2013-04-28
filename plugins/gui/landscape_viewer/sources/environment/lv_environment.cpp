
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"
#include "landscape_viewer/sources/game_initializer/lv_igame_initializer.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_manager.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


Environment::Environment( PluginInstance& _pluginInstance )
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


const QPixmap&
Environment::getPixmap( const QString& _resourcePath, const QRect& _rect ) const
{
	return m_pluginInstance.getImagesManager()->getPixmap( _resourcePath, _rect );

} // Environment::getPixmap


/*---------------------------------------------------------------------------*/


void
Environment::initializeLandscapeModel( const QString& _fileName )
{
	m_pluginInstance.getLandscapeManager()->initCurrentLandscape( _fileName );

} // Environment::initializeLandscapeModel


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::ILandscape >
Environment::getLandscape() const
{
	return m_pluginInstance.getLandscapeManager()->getCurrentLandscape();

} // Environment::getLandscape


/*---------------------------------------------------------------------------*/


void
Environment::showCurrentLandscapeModel()
{
	m_pluginInstance.showCurrentLandscapeModel();

} // Environment::showCurrentLandscapeModel


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
