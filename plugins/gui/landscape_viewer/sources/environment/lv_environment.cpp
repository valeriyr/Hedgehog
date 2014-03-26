
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"

#include "animation_manager/ih/am_ianimation_manager.hpp"
#include "animation_manager/ih/am_ianimations_cache.hpp"
#include "animation_manager/h/am_animation_info.hpp"

#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"

#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_iview.hpp"

#include "event_manager/h/em_subscriber.hpp"

#include "sound_manager/ih/sm_isound_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"

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
			,	Core::LandscapeModel::Direction::South ) );

	if ( m_pluginInstance.getAnimationsCache()->hasAnimation( animationName ) )
	{
		const Framework::GUI::AnimationManager::AnimationInfo& animationInfo
			= m_pluginInstance.getAnimationsCache()->getAnimation( animationName );

		Framework::GUI::ImagesManager::IImagesManager::TransformationData transformationData( animationInfo.m_frames[ 0 ].m_frame );

		return m_pluginInstance.getImagesManager()->getPixmap( animationInfo.m_atlasName, transformationData );
	}
	else
	{
		return getPixmap( _objectName, IGraphicsInfoCache::ms_anySkinIdentifier );
	}

} // Environment::getPixmap


/*---------------------------------------------------------------------------*/


const QPixmap&
Environment::getPixmap( const QString& _objectName ) const
{
	return getPixmap( _objectName, getString( Resources::Properties::SkinId ) );

} // Environment::getPixmap


/*---------------------------------------------------------------------------*/


void
Environment::playSound( const QString& _resourcePath ) const
{
	m_pluginInstance.getSoundManager()->play( _resourcePath );

} // Environment::playSound


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
Environment::initLandscapeModel( const QString& _fileName ) const
{
	m_pluginInstance.getLandscapeModel()->initModel( _fileName );

} // Environment::initLandscapeModel


/*---------------------------------------------------------------------------*/


void
Environment::resetLandscapeModel() const
{
	m_pluginInstance.getLandscapeModel()->resetModel();

} // Environment::resetLandscapeModel


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
Environment::lockModel() const
{
	return m_pluginInstance.getLandscapeModel()->lockModel();

} // Environment::lockModel


/*---------------------------------------------------------------------------*/


void
Environment::saveLandscape( const QString& _fileName ) const
{
	m_pluginInstance.getLandscapeModel()->saveModel( _fileName );

} // Environment::saveLandscape


/*---------------------------------------------------------------------------*/


void
Environment::selectItemsInModel( const QRect& _rect ) const
{
	m_pluginInstance.getLandscapeModel()->selectObjects( _rect );

} // Environment::selectItemsInModel


/*---------------------------------------------------------------------------*/


void
Environment::selectItemModel( const Core::LandscapeModel::Object::Id& _id ) const
{
	m_pluginInstance.getLandscapeModel()->selectObject( _id );

} // Environment::selectItemModel


/*---------------------------------------------------------------------------*/


void
Environment::sendSelectedObjects( const QPoint& _to, const bool _flush ) const
{
	m_pluginInstance.getLandscapeModel()->sendSelectedObjects( _to, _flush );

} // Environment::sendSelectedObjects


/*---------------------------------------------------------------------------*/


void
Environment::createObject( const QPoint& _location, const QString& _name ) const
{
	m_pluginInstance.getLandscapeModel()->createObject( _location, _name );

} // Environment::createObject


/*---------------------------------------------------------------------------*/


void
Environment::setSurfaceItem( const QPoint& _location, const Core::LandscapeModel::ISurfaceItem::Id& _id ) const
{
	m_pluginInstance.getLandscapeModel()->setSurfaceItem( _location, _id );

} // Environment::setSurfaceItem


/*---------------------------------------------------------------------------*/


void
Environment::trainObject( const Core::LandscapeModel::Object::Id& _parentId, const QString& _objectName ) const
{
	m_pluginInstance.getLandscapeModel()->trainObject( _parentId, _objectName );

} // Environment::trainObject


/*---------------------------------------------------------------------------*/


void
Environment::buildObject( const Core::LandscapeModel::Object::Id& _builderId, const QString& _objectName, const QPoint& _atLocation ) const
{
	m_pluginInstance.getLandscapeModel()->buildObject( _builderId, _objectName, _atLocation );

} // Environment::buildObject


/*---------------------------------------------------------------------------*/


const Core::LandscapeModel::ISurfaceItem::Id
Environment::getDefaultSurfaceItemId() const
{
	return m_pluginInstance.getSurfaceItemsCache()->getDefaultSurfaceItem()->getId();

} // Environment::getDefaultSurfaceItemId


/*---------------------------------------------------------------------------*/


void
Environment::fetchTypes( Core::LandscapeModel::IStaticData::StaticDataCollection& _collection ) const
{
	m_pluginInstance.getStaticData()->fetchObjectsStaticData( _collection );

} // Environment::fetchTypes


/*---------------------------------------------------------------------------*/


Core::LandscapeModel::IStaticData::ObjectStaticData
Environment::getObjectStaticData( const QString& _objectName ) const
{
	return m_pluginInstance.getStaticData()->getObjectStaticData( _objectName );

} // Environment::getObjectStaticData


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
	,	const Core::LandscapeModel::ISurfaceItem::Id& _id ) const
{
	return m_pluginInstance.getGraphicsInfoCache()->getSurfaceItemGraphicsInfo( _skinId, _id );

} // Environment::getSurfaceItemGraphicsInfo


/*---------------------------------------------------------------------------*/


void
Environment::playAnimation(
		Framework::GUI::AnimationManager::IAnimateObject& _animateObject
	,	const QString& _animationName ) const
{
	m_pluginInstance.getAnimationManager()->playAnimation( _animateObject, _animationName );

} // Environment::playAnimation


/*---------------------------------------------------------------------------*/


void
Environment::playAnimationOnce(
		Framework::GUI::AnimationManager::IAnimateObject& _animateObject
	,	const QString& _animationName ) const
{
	m_pluginInstance.getAnimationManager()->playAnimationOnce( _animateObject, _animationName );

} // Environment::playAnimationOnce


/*---------------------------------------------------------------------------*/


bool
Environment::hasAnimation( const QString& _animationName ) const
{
	return m_pluginInstance.getAnimationsCache()->hasAnimation( _animationName );

} // Environment::hasAnimation


/*---------------------------------------------------------------------------*/


void
Environment::stopAnimation( Framework::GUI::AnimationManager::IAnimateObject& _animateObject ) const
{
	m_pluginInstance.getAnimationManager()->stopAnimation( _animateObject );

} // Environment::stopAnimation


/*---------------------------------------------------------------------------*/


void
Environment::stopAllAnimations() const
{
	m_pluginInstance.getAnimationManager()->stopAllAnimations();

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


void
Environment::printMessage(
		const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
	,	const QString& _message ) const
{
	m_pluginInstance.getSystemMessenger()->printMessage( Resources::ModuleName, _messageLevel, _message );

} // Environment::printMessage


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
