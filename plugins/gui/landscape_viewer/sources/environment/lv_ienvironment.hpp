
#ifndef __LV_IENVIRONMENT_HPP__
#define __LV_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "window_manager/h/wm_view_position.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/h/lm_object.hpp"

#include "landscape_viewer/sources/graphics_info_cache/lv_igraphics_info_cache.hpp"

#include "images_manager/ih/im_iimages_manager.hpp"

#include "messenger/ms_imessenger.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace GUI
	{
		namespace WindowManager
		{
			struct IView;
		}

		namespace AnimationManager
		{
			struct IAnimateObject;
		}
	}

	namespace Core
	{
		namespace EventManager
		{
			class Subscriber;
		}
	}
}

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscape;
			struct ILandscapeHandle;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IAnimateObject;

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual QString showOpenFileDialog() const = 0;

	virtual QString showSaveFileDialog() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QPixmap& getPixmap(
			const QString& _resourcePath
		,	const Framework::GUI::ImagesManager::IImagesManager::TransformationData& _transformationData ) const = 0;

	virtual const QPixmap& getPixmap( const QString& _objectName, const QString& _skinId ) const = 0;

	virtual const QPixmap& getPixmap( const QString& _objectName ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void playSound( const QString& _resourcePath ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void addFrameworkView(
			boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view
		,	const Framework::GUI::WindowManager::ViewPosition::Enum _position ) const = 0;

	virtual void removeFrameworkView(
			boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void initLandscapeModel( const QString& _fileName ) const = 0;

	virtual void resetLandscapeModel() const = 0;

	virtual boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle >
		getCurrentLandscape () const = 0;

	virtual void saveLandscape( const QString& _fileName ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void selectItemsInModel( const QRect& _rect ) const = 0;

	virtual void selectItemModel( const Core::LandscapeModel::Object::UniqueId& _id ) const = 0;

	virtual void sendSelectedObjects( const QPoint& _to, const bool _pushCommand ) const = 0;

	virtual void createObject( const QPoint& _location, const QString& _name ) const = 0;

	virtual void setSurfaceItem( const QPoint& _location, const Core::LandscapeModel::ISurfaceItem::Id& _id ) const = 0;

	virtual void trainObject( const Core::LandscapeModel::Object::UniqueId& _parentId, const QString& _objectName ) const = 0;

	virtual void buildObject( const Core::LandscapeModel::Object::UniqueId& _builderId, const QString& _objectName, const QPoint& _atLocation ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual const Core::LandscapeModel::ISurfaceItem::Id
		getDefaultSurfaceItemId() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void fetchTypes( Core::LandscapeModel::IStaticData::StaticDataCollection& _collection ) const = 0;

	virtual Core::LandscapeModel::IStaticData::ObjectStaticData getObjectStaticData( const QString& _objectName ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void fetchSurfaceItemGraphicsInfos(
			const QString& _skinId
		,	IGraphicsInfoCache::SurfaceItemGraphicsInfoCollection& _collection ) const = 0;

	virtual boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Core::LandscapeModel::ISurfaceItem::Id& _id ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void playAnimation(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _animationName ) const = 0;

	virtual void playAnimationOnce(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _animationName ) const = 0;

	virtual bool hasAnimation( const QString& _animationName ) const = 0;

	virtual void stopAnimation( Framework::GUI::AnimationManager::IAnimateObject& _animateObject ) const = 0;

	virtual void stopAllAnimations() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void setBool( const QString& _key, const bool _value ) const = 0;

	virtual bool getBool( const QString& _key ) const = 0;

	virtual void setString( const QString& _key, const QString& _value ) const = 0;

	virtual QString getString( const QString& _key ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual Framework::Core::EventManager::Subscriber createSubscriber() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IENVIRONMENT_HPP__
