
#ifndef __MV_IMINIMAP_VIEWER_HPP__
#define __MV_IMINIMAP_VIEWER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"
#include "window_manager/ih/wm_iview.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscape;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace MinimapViewer {

/*---------------------------------------------------------------------------*/

	const unsigned int IID_MINIMAP_VIEWER = 0;

/*---------------------------------------------------------------------------*/

struct IMinimapViewer
	:	public Framework::GUI::WindowManager::IView
{
	virtual void showLandscape( const Core::LandscapeModel::ILandscape& _landscape ) = 0;

	virtual void clear() = 0;

	virtual void setVisibilityRectSize( const float _relVisibleWidth, const float _relVisibleHeight ) = 0;

	virtual void setVisibilityRectPosition( const float _relVisibleWidth, const float _relVisibleHeight ) = 0;
};

/*---------------------------------------------------------------------------*/

} // namespace MinimapViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __MV_IMINIMAP_VIEWER_HPP__