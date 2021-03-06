
#ifndef __LV_IENVIRONMENT_HPP__
#define __LV_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "window_manager/h/wm_view_position.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_istatic_data.hpp"

#include "landscape_model/h/lm_game_object.hpp"

#include "landscape_viewer/sources/graphics_info/lv_igraphics_info.hpp"
#include "landscape_viewer/sources/map_preview_generator/lv_imap_preview_generator.hpp"

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
			struct IModelLocker;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IAnimateObject;
struct ILandscapeViewer;

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual QString showOpenFileDialog( const QString& _filter ) const = 0;

	virtual QString showSaveFileDialog( const QString& _filter ) const = 0;

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

	virtual boost::intrusive_ptr< Core::LandscapeModel::IModelLocker >
		lockModel () const = 0;

/*---------------------------------------------------------------------------*/

	virtual const Tools::Core::Generators::IGenerator::IdType
		getDefaultSurfaceItemId() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void fetchTypes( Core::LandscapeModel::IStaticData::StaticDataCollection& _collection ) const = 0;

	virtual void fetchRaces( Core::LandscapeModel::IStaticData::RacesCollection& _collection ) const = 0;

	virtual Core::LandscapeModel::IStaticData::ObjectStaticData getObjectStaticData( const QString& _objectName ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IGraphicsInfo > getGraphicsInfo() const = 0;

	virtual boost::intrusive_ptr< ILandscapeViewer > getLandscapeViewer() const = 0;

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

	virtual void setUInt( const QString& _key, const quint32 _value ) const = 0;

	virtual quint32 getUInt( const QString& _key ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual Framework::Core::EventManager::Subscriber createSubscriber() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void printMessage(
			const Tools::Core::IMessenger::MessegeLevel::Enum _messageLevel
		,	const QString& _message ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual QString getLandscapesDirectory() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void generateMapPreview(
			QPixmap& _generateTo
		,	const IMapPreviewGenerator::GenerateLayers::Mask& _mask ) const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IENVIRONMENT_HPP__
