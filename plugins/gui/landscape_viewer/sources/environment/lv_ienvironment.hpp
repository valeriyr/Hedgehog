
#ifndef __LV_IENVIRONMENT_HPP__
#define __LV_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

#include "window_manager/h/wm_view_position.hpp"

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
			struct ISurfaceItem;
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

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_IENVIRONMENT_HPP__
