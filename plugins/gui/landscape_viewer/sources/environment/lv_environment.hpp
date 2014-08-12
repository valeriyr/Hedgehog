
#ifndef __LV_ENVIRONMENT_HPP__
#define __LV_ENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class PluginInstance;

/*---------------------------------------------------------------------------*/

class Environment
	:	public Tools::Core::BaseWrapper< IEnvironment >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	Environment( PluginInstance& _pluginInstance );

	virtual ~Environment();

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString showOpenFileDialog() const;

	/*virtual*/ QString showSaveFileDialog() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const QPixmap& getPixmap(
			const QString& _resourcePath
		,	const Framework::GUI::ImagesManager::IImagesManager::TransformationData& _transformationData ) const;

	/*virtual*/ const QPixmap& getPixmap( const QString& _objectName, const QString& _skinId ) const;

	/*virtual*/ const QPixmap& getPixmap( const QString& _objectName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void playSound( const QString& _resourcePath ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addFrameworkView(
			boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view
		,	const Framework::GUI::WindowManager::ViewPosition::Enum _position ) const;

	/*virtual*/ void removeFrameworkView(
			boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		lockModel () const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Core::LandscapeModel::ISurfaceItem::Id
		getDefaultSurfaceItemId() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void fetchTypes( Core::LandscapeModel::IStaticData::StaticDataCollection& _collection ) const;

	/*virtual*/ Core::LandscapeModel::IStaticData::ObjectStaticData getObjectStaticData( const QString& _objectName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void fetchSurfaceItemGraphicsInfos(
			const QString& _skinId
		,	IGraphicsInfoCache::SurfaceItemGraphicsInfoCollection& _collection ) const;

	/*virtual*/ boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Core::LandscapeModel::ISurfaceItem::Id& _id ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void playAnimation(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _animationName ) const;

	/*virtual*/ void playAnimationOnce(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _animationName ) const;

	/*virtual*/ bool hasAnimation( const QString& _animationName ) const;

	/*virtual*/ void stopAnimation( Framework::GUI::AnimationManager::IAnimateObject& _animateObject ) const;

	/*virtual*/ void stopAllAnimations() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void setBool( const QString& _key, const bool _value ) const;

	/*virtual*/ bool getBool( const QString& _key ) const;

	/*virtual*/ void setString( const QString& _key, const QString& _value ) const;

	/*virtual*/ QString getString( const QString& _key ) const;

	/*virtual*/ void setUInt( const QString& _key, const unsigned int _value ) const;

	/*virtual*/ unsigned int getUInt( const QString& _key ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ Framework::Core::EventManager::Subscriber createSubscriber() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ QString getLandscapesDirectory() const;

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	PluginInstance& m_pluginInstance;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_ENVIRONMENT_HPP__
