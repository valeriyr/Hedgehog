
#ifndef __LV_IENVIRONMENT_HPP__
#define __LV_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "window_manager/h/wm_view_position.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"

#include "landscape_viewer/sources/graphics_info_cache/lv_igraphics_info_cache.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace GUI
	{
		namespace WindowManager
		{
			struct IView;
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
			struct IEditableLandscape;
			struct ILandscapeHandle;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual QString showOpenFileDialog() const = 0;

	virtual QString showSaveFileDialog() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QPixmap& getPixmap( const QString& _resourcePath, const QRect& _rect ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void addFrameworkView(
			boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view
		,	const Framework::GUI::WindowManager::ViewPosition::Enum _position ) const = 0;

	virtual void removeFrameworkView(
			boost::intrusive_ptr< Framework::GUI::WindowManager::IView > _view ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void initializeLandscapeModel( const QString& _fileName ) const = 0;

	virtual void resetLandscapeModel() const = 0;

	virtual boost::intrusive_ptr< Core::LandscapeModel::ILandscapeHandle >
		getCurrentLandscape () const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
		createLandscape( const unsigned int _width, const unsigned int _height ) const = 0;

	virtual boost::intrusive_ptr< Core::LandscapeModel::IEditableLandscape >
		tryToOpenLandscape( const QString& _landscapePath ) const = 0;

	virtual void saveLandscape(
			const QString& _fileName
		,	const Core::LandscapeModel::ILandscape& _landscape ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void selectItemsInModel(
			const QPoint& _from
		,	const QPoint& _to ) const = 0;

	virtual void moveSelectedItems( const QPoint& _to ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual const Core::LandscapeModel::ISurfaceItem::IdType
		getDefaultSurfaceItemId() const = 0;

/*---------------------------------------------------------------------------*/

	virtual void fetchSurfaceItemGraphicsInfos(
			const QString& _skinId
		,	IGraphicsInfoCache::SurfaceItemGraphicsInfoCollection& _collection ) const = 0;

	virtual boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		getSurfaceItemGraphicsInfo(
				const QString& _skinId
			,	const Core::LandscapeModel::ISurfaceItem::IdType& _id ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void regBool( const QString& _key, const bool _defaultValue ) const = 0;

	virtual void unregProperty( const QString& _key ) const = 0;

	virtual void setBool( const QString& _key, const bool _value ) const = 0;

	virtual bool getBool( const QString& _key ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual Framework::Core::EventManager::Subscriber createSubscriber() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IENVIRONMENT_HPP__
