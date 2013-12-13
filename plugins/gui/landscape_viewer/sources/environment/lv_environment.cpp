
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_iview.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "event_manager/h/em_subscriber.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_ilandscape_editor.hpp"
#include "landscape_model/ih/lm_ieditable_landscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"

#include "settings/ih/st_isettings.hpp"


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


const Core::LandscapeModel::ISurfaceItem::IdType
Environment::getDefaultSurfaceItemId() const
{
	return m_pluginInstance.getSurfaceItemsCache()->getDefaultSurfaceItem()->getId();

} // Environment::getDefaultSurfaceItemId


void
Environment::fetchSurfaceItemGraphicsInfos(
		const QString& _skinId
	,	IGraphicsInfoCache::SurfaceItemGraphicsInfoCollection& _collection ) const
{
	m_pluginInstance.getGraphicsInfoCache()->fetchSurfaceItemGraphicsInfos( _skinId, _collection );

} // Environment::fetchSurfaceItemGraphicsInfos


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
Environment::getSurfaceItemGraphicsInfo(
		const QString& _skinId
	,	const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const
{
	return m_pluginInstance.getGraphicsInfoCache()->getSurfaceItemGraphicsInfo( _skinId, _id );

} // Environment::getSurfaceItemGraphicsInfo


/*---------------------------------------------------------------------------*/


void
Environment::regBool( const QString& _key, const bool _defaultValue ) const
{
	m_pluginInstance.getSettings()->regBool( _key, _defaultValue );

} // Environment::regBool


/*---------------------------------------------------------------------------*/


void
Environment::unregProperty( const QString& _key ) const
{
	m_pluginInstance.getSettings()->unregProperty( _key );

} // Environment::unregProperty


/*---------------------------------------------------------------------------*/


void
Environment::setBool( const QString& _key, const bool _value ) const
{
	m_pluginInstance.getSettings()->setBool( _key, _value );

} // Environment::setBool


/*---------------------------------------------------------------------------*/


bool
Environment::getBool( const QString& _key ) const
{
	return m_pluginInstance.getSettings()->getBool( _key );

} // Environment::getBool


/*---------------------------------------------------------------------------*/


Framework::Core::EventManager::Subscriber
Environment::createSubscriber() const
{
	return Framework::Core::EventManager::Subscriber( *m_pluginInstance.getEventManager() );

} // Environment::createSubscriber


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
