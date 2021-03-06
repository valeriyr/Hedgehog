
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/environment/lv_environment.hpp"

#include "landscape_viewer/sources/plugin/lv_plugin_instance.hpp"
#include "landscape_viewer/sources/graphics_info/lv_isurface_item_graphics_info.hpp"

#include "animation_manager/ih/am_ianimation_manager.hpp"
#include "animation_manager/ih/am_ianimations_cache.hpp"
#include "animation_manager/h/am_animation_info.hpp"

#include "landscape_viewer/sources/animations/lv_animation_name_generator.hpp"
#include "landscape_viewer/sources/graphics_info/lv_graphics_info.hpp"
#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/landscape_viewer/lv_ilandscape_viewer.hpp"

#include "window_manager/ih/wm_idialogs_manager.hpp"
#include "window_manager/ih/wm_iwindow_manager.hpp"
#include "window_manager/ih/wm_iview.hpp"

#include "event_manager/h/em_subscriber.hpp"

#include "sound_manager/ih/sm_isound_manager.hpp"

#include "landscape_model/ih/lm_ilandscape_model.hpp"
#include "landscape_model/ih/lm_imodel_locker.hpp"
#include "landscape_model/ih/lm_isurface_items_cache.hpp"
#include "landscape_model/ih/lm_imodel_information.hpp"
#include "landscape_model/ih/lm_ilandscape.hpp"

#include "landscape_model/h/lm_resources.hpp"

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
Environment::showOpenFileDialog( const QString& _filter ) const
{
	return m_pluginInstance.getDialogsManager()->getOpenFileName( _filter );

} // Environment::showOpenFileDialog


/*---------------------------------------------------------------------------*/


QString
Environment::showSaveFileDialog( const QString& _filter ) const
{
	return m_pluginInstance.getDialogsManager()->getSaveFileName( _filter );

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
		return getPixmap( _objectName, IGraphicsInfo::ms_anySkinIdentifier );
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


boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
Environment::lockModel() const
{
	return m_pluginInstance.getModelLocker();

} // Environment::lockModel


/*---------------------------------------------------------------------------*/


const Tools::Core::Generators::IGenerator::IdType
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


void
Environment::fetchRaces( Core::LandscapeModel::IStaticData::RacesCollection& _collection ) const
{
	m_pluginInstance.getStaticData()->fetchRaces( _collection );

} // Environment::fetchRaces


/*---------------------------------------------------------------------------*/


Core::LandscapeModel::IStaticData::ObjectStaticData
Environment::getObjectStaticData( const QString& _objectName ) const
{
	return m_pluginInstance.getStaticData()->getObjectStaticData( _objectName );

} // Environment::getObjectStaticData


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< IGraphicsInfo >
Environment::getGraphicsInfo() const
{
	return m_pluginInstance.getGraphicsInfo();

} // Environment::getGraphicsInfo


/*---------------------------------------------------------------------------*/


boost::intrusive_ptr< ILandscapeViewer >
Environment::getLandscapeViewer() const
{
	return m_pluginInstance.getLandscapeViewer();

} // Environment::getLandscapeViewer


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


void
Environment::setUInt( const QString& _key, const quint32 _value ) const
{
	m_pluginInstance.getSettings()->setUInt( _key, _value );

} // Environment::setUInt


/*---------------------------------------------------------------------------*/


quint32
Environment::getUInt( const QString& _key ) const
{
	return m_pluginInstance.getSettings()->getUInt( _key );

} // Environment::getUInt


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


QString
Environment::getLandscapesDirectory() const
{
	return m_pluginInstance.getModelInformation()->getLandscapesDirectory();

} // Environment::getLandscapesDirectory


/*---------------------------------------------------------------------------*/


void
Environment::generateMapPreview(
		QPixmap& _generateTo
	,	const IMapPreviewGenerator::GenerateLayers::Mask& _mask ) const
{
	m_pluginInstance.getMapPreviewGenerator()->generate( _generateTo, _mask );

} // Environment::generateMapPreview


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
