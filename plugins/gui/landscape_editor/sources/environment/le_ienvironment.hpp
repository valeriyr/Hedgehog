
#ifndef __LE_IENVIRONMENT_HPP__
#define __LE_IENVIRONMENT_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace GUI
	{
		namespace WindowManager
		{
			 struct IDialogsManager;
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
			struct ILandscapeEditor;
			struct ISurfaceItem;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IBaseView;
struct IEditorView;
struct ILandscapeEditorInternal;

/*---------------------------------------------------------------------------*/

struct IEnvironment
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Framework::GUI::WindowManager::IDialogsManager >
		getDialogsManager() const = 0;

	virtual boost::intrusive_ptr< Plugins::Core::LandscapeModel::ILandscapeEditor >
		getLandscapeEditor() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
		getSurfaceItem( const unsigned int _index ) const = 0;

	virtual boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
		getDefaultSurfaceItem() const = 0;

/*---------------------------------------------------------------------------*/

	virtual const QPixmap& getPixmap( const QString& _resourcePath, const QRect& _rect ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual void showLandscapeOnMinimap(
		const Plugins::Core::LandscapeModel::ILandscape& _landscape ) const = 0;

	virtual void clearMinimap() const = 0;

	virtual void setMinimapVisibilityRectSize(
			const float _relVisibleWidth
		,	const float _relVisibleHeight ) const = 0;

	virtual void setMinimapVisibilityRectPosition(
			const float _relVisibleWidth
		,	const float _relVisibleHeight ) const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< IBaseView > getObjectsView() const = 0;

	virtual boost::intrusive_ptr< IEditorView > getEditorView() const = 0;

	virtual boost::intrusive_ptr< IBaseView > getDescriptionView() const = 0;

/*---------------------------------------------------------------------------*/

	virtual boost::intrusive_ptr< ILandscapeEditorInternal > getGUILandscapeEditor() const = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_IENVIRONMENT_HPP__
