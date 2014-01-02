
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"

#include "animation_manager/ih/am_ianimation_manager.hpp"
#include "animation_manager/ih/am_ianimations_cache.hpp"
#include "animation_manager/h/am_animation_info.hpp"

#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"

#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_iview.hpp"

#include "event_manager/h/em_subscriber.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
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
Environment::getPixmap(
		const QString& _resourcePath
	,	const Framework::GUI::ImagesManager::IImagesManager::TransformationData& _transformationData ) const
{
	return m_pluginInstance.getImagesManager()->getPixmap( _resourcePath, _transformationData );

} // Environment::getPixmap


/*---------------------------------------------------------------------------*/


const QPixmap&
Environment::getPixmap( const QString& _objectName, const QString& _skinId ) const
{
	QString animationName(
		generateAnimationName(
				_skinId
			,	_objectName
			,	Core::LandscapeModel::ObjectState::Standing
			,	Core::LandscapeModel::Direction::Down ) );

	const Framework::GUI::AnimationManager::AnimationInfo& animationInfo
		= m_pluginInstance.getAnimationsCache()->getAnimation( animationName );

	Framework::GUI::ImagesManager::IImagesManager::TransformationData transformationData( animationInfo.m_frames[ 0 ].m_frame );

	return m_pluginInstance.getImagesManager()->getPixmap( animationInfo.m_atlasName, transformationData );

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
Environment::saveLandscape( const QString& _fileName ) const
{
	m_pluginInstance.getLandscapeModel()->saveLandscape( _fileName );

} // Environment::saveLandscape


/*---------------------------------------------------------------------------*/


void
Environment::selectItemsInModel( const QRect& _rect ) const
{
	m_pluginInstance.getLandscapeModel()->selectObjects( _rect );

} // Environment::selectItemsInModel


/*---------------------------------------------------------------------------*/


void
Environment::selectItemModel( const Core::LandscapeModel::IObject::IdType& _id ) const
{
	m_pluginInstance.getLandscapeModel()->selectObject( _id );

} // Environment::selectItemModel


/*---------------------------------------------------------------------------*/


void
Environment::moveSelectedItems( const QPoint& _to ) const
{
	m_pluginInstance.getLandscapeModel()->moveSelectedObjects( _to );

} // Environment::moveSelectedItems


/*---------------------------------------------------------------------------*/


void
Environment::createObject( const QPoint& _position, const QString& _name ) const
{
	m_pluginInstance.getLandscapeModel()->createObject( _position, _name );

} // Environment::createObject


/*---------------------------------------------------------------------------*/


void
Environment::setSurfaceItem( const QPoint& _position, const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const
{
	m_pluginInstance.getLandscapeModel()->setSurfaceItem( _position, _id );

} // Environment::setSurfaceItem


/*---------------------------------------------------------------------------*/


const Core::LandscapeModel::ISurfaceItem::IdType
Environment::getDefaultSurfaceItemId() const
{
	return m_pluginInstance.getSurfaceItemsCache()->getDefaultSurfaceItem()->getId();

} // Environment::getDefaultSurfaceItemId


/*---------------------------------------------------------------------------*/


void
Environment::fetchTypes( Core::LandscapeModel::IObjectTypesCache::TypesCollection& _collection ) const
{
	m_pluginInstance.getObjectTypesCache()->fetchTypes( _collection );

} // Environment::fetchTypes


/*---------------------------------------------------------------------------*/


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
Environment::playAnimation(
		Framework::GUI::AnimationManager::IAnimateObject& _animateObject
	,	const QString& _animationName ) const
{
	return m_pluginInstance.getAnimationManager()->playAnimation( _animateObject, _animationName );

} // Environment::playAnimation


/*---------------------------------------------------------------------------*/


void
Environment::stopAnimation( Framework::GUI::AnimationManager::IAnimateObject& _animateObject ) const
{
	return m_pluginInstance.getAnimationManager()->stopAnimation( _animateObject );

} // Environment::stopAnimation


/*---------------------------------------------------------------------------*/


void
Environment::stopAllAnimations() const
{
	return m_pluginInstance.getAnimationManager()->stopAllAnimations();

} // Environment::stopAllAnimations


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


void
Environment::setString( const QString& _key, const QString& _value ) const
{
	m_pluginInstance.getSettings()->setString( _key, _value );

} // Environment::setString


/*---------------------------------------------------------------------------*/


QString
Environment::getString( const QString& _key ) const
{
	return m_pluginInstance.getSettings()->getString( _key );

} // Environment::getString


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
