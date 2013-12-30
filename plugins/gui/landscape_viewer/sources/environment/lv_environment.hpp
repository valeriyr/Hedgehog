
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

	/*virtual*/ const QPixmap& getPixmap( const QString& _unitName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void addFrameworkView(
			boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view
		,	const Framework::GUI::WindowManager::ViewPosition::Enum _position ) const;

	/*virtual*/ void removeFrameworkView(
			boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void initializeLandscapeModel( const QString& _fileName ) const;

	/*virtual*/ void resetLandscapeModel() const;

	/*virtual*/ boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle >
		getCurrentLandscape () const;

	/*virtual*/ void saveLandscape( const QString& _fileName ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void selectItemsInModel( const QRect& _rect ) const;

	/*virtual*/ void selectItemModel( const Core::LandscapeModel::IUnit::IdType& _id ) const;

	/*virtual*/ void moveSelectedItems( const QPoint& _to ) const;

	/*virtual*/ void createObject( const QPoint& _position, const QString& _name ) const;

	/*virtual*/ void setSurfaceItem( const QPoint& _position, const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ const Core::LandscapeModel::ISurfaceItem::IdType
		getDefaultSurfaceItemId() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void fetchSurfaceItemGraphicsInfos(
			const QString& _skinId
		,	IGraphicsInfoCache::SurfaceItemGraphicsInfoCollection& _collection ) const;

	/*virtual*/ boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void playAnimation(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _animationName ) const;

	/*virtual*/ void stopAnimation( Framework::GUI::AnimationManager::IAnimateObject& _animateObject ) const;

	/*virtual*/ void stopAllAnimations() const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ void regBool( const QString& _key, const bool _defaultValue ) const;

	/*virtual*/ void unregProperty( const QString& _key ) const;

	/*virtual*/ void setBool( const QString& _key, const bool _value ) const;

	/*virtual*/ bool getBool( const QString& _key ) const;

/*---------------------------------------------------------------------------*/

	/*virtual*/ Framework::Core::EventManager::Subscriber createSubscriber() const;

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
