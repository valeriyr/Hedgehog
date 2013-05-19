
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_manager.hpp"
#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "game_manager/ih/gm_igame_manager.hpp"


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


QString
Environment::showOpenFileDialog() const
{
	return m_pluginInstance.getDialogsManager()->getOpenFileName( "*.hmap" );

} // Environment::showOpenFileDialog


/*---------------------------------------------------------------------------*/


QString
Environment::showSaveFileDialog() const
{
	return m_pluginInstance.getDialogsManager()->getSaveFileName( "*.hmap" );

} // Environment::showSaveFileDialog


/*---------------------------------------------------------------------------*/


const QPixmap&
Environment::getPixmap( const QString& _resourcePath, const QRect& _rect ) const
{
	return m_pluginInstance.getImagesManager()->getPixmap( _resourcePath, _rect );

} // Environment::getPixmap


/*---------------------------------------------------------------------------*/


void
Environment::initializeLandscape( const QString& _fileName ) const
{
	m_pluginInstance.getLandscapeManager()->initCurrentLandscape( _fileName );

} // Environment::initializeLandscape


/*---------------------------------------------------------------------------*/


void
Environment::closeLandscape() const
{
	m_pluginInstance.getLandscapeManager()->closeCurrentLandscape();

} // Environment::closeLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::ILandscape >
Environment::getLandscape() const
{
	return m_pluginInstance.getLandscapeManager()->getCurrentLandscape();

} // Environment::getLandscape


/*---------------------------------------------------------------------------*/


void
Environment::saveLandscape(
		const QString& _fileName
	,	const Core::LandscapeModel::ILandscape& _landscape ) const
{
	m_pluginInstance.getLandscapeEditor()->saveLandscape( _landscape, _fileName );

} // Environment::saveLandscape


/*---------------------------------------------------------------------------*/


void
Environment::runGameManager() const
{
	m_pluginInstance.getGameManager()->run();

} // Environment::runGameManager


/*---------------------------------------------------------------------------*/


void
Environment::stopGameManager() const
{
	m_pluginInstance.getGameManager()->stop();

} // Environment::stopGameManager


/*---------------------------------------------------------------------------*/


void
Environment::selectItemsInModel(
		const Core::LandscapeModel::Point& _from
	,	const Core::LandscapeModel::Point& _to ) const
{
	m_pluginInstance.getGameManager()->pushSelectAction( _from, _to );

} // Environment::selectItemsInModel


/*---------------------------------------------------------------------------*/


void
Environment::moveSelectedItems( const Core::LandscapeModel::Point& _to ) const
{
	m_pluginInstance.getGameManager()->pushMoveAction( _to );

} // Environment::moveSelectedItems


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
