
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_iview.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"

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
Environment::addFrameworkView(
		boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view
	,	const Framework::GUI::WindowManager::ViewPosition::Enum _position ) const
{
	m_pluginInstance.getWindowManager()->addView( _view, _position );

} // Environment::addFrameworkView


/*---------------------------------------------------------------------------*/


void
Environment::removeFrameworkView( boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view ) const
{
	m_pluginInstance.getWindowManager()->removeView( _view );

} // Environment::removeFrameworkView


/*---------------------------------------------------------------------------*/

void
Environment::initializeLandscapeModel( const QString& _fileName ) const
{
	m_pluginInstance.getLandscapeModel()->initCurrentLandscape( _fileName );

} // Environment::initializeLandscapeModel


/*---------------------------------------------------------------------------*/


void
Environment::resetLandscapeModel() const
{
	m_pluginInstance.getLandscapeModel()->closeCurrentLandscape();

} // Environment::resetLandscapeModel


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle >
Environment::getCurrentLandscape() const
{
	return m_pluginInstance.getLandscapeModel()->getCurrentLandscape();

} // Environment::getCurrentLandscape


/*---------------------------------------------------------------------------*/


void
Environment::saveLandscape(
		const QString& _fileName
	,	const Core::LandscapeModel::ILandscape& _landscape ) const
{
	m_pluginInstance.getLandscapeEditor()->saveLandscape( _landscape, _fileName );

} // Environment::saveLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
Environment::createLandscape( const unsigned int _width, const unsigned int _height ) const
{
	return m_pluginInstance.getLandscapeEditor()->createLandscape( _width, _height );

} // Environment::saveLandscape


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
Environment::tryToOpenLandscape( const QString& _landscapePath ) const
{
	return m_pluginInstance.getLandscapeEditor()->loadLandscape( _landscapePath );

} // Environment::saveLandscape


/*---------------------------------------------------------------------------*/


void
Environment::selectItemsInModel(
		const QPoint& _from
	,	const QPoint& _to ) const
{
	//m_pluginInstance.getLandscapeModel()->pushSelectAction( _from, _to );

} // Environment::selectItemsInModel


/*---------------------------------------------------------------------------*/


void
Environment::moveSelectedItems( const QPoint& _to ) const
{
	//m_pluginInstance.getLandscapeModel()->pushMoveAction( _to );

} // Environment::moveSelectedItems


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
