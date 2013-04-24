
#ifndef __LE_ILANDSCAPE_RENDERER_HPP__
#define __LE_ILANDSCAPE_RENDERER_HPP__

/*---------------------------------------------------------------------------*/

#include "intrusive_base/ib_ibase.hpp"

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
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct ILandscapeRenderer
	:	public Tools::Core::IBase
{

/*---------------------------------------------------------------------------*/

	virtual void renderSurface(
			const Core::LandscapeModel::ILandscape& _landscape
		,	QPixmap& _pixmap ) = 0;

	virtual void renderObjects(
			const Core::LandscapeModel::ILandscape& _landscape
		,	QPixmap& _pixmap ) = 0;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_ILANDSCAPE_RENDERER_HPP__
