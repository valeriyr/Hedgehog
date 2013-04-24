
#ifndef __LE_LANDSCAPE_RENDERER_HPP__
#define __LE_LANDSCAPE_RENDERER_HPP__

/*---------------------------------------------------------------------------*/

#include "landscape_editor/sources/landscape_renderer/le_ilandscape_renderer.hpp"

/*---------------------------------------------------------------------------*/

namespace Framework
{
	namespace GUI
	{
		namespace ImagesManager
		{
			struct IImagesManager;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class LandscapeRenderer
	:	public Tools::Core::BaseWrapper< ILandscapeRenderer >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeRenderer( Framework::GUI::ImagesManager::IImagesManager& _imagesManager );

	virtual ~LandscapeRenderer();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void renderSurface(
			const Core::LandscapeModel::ILandscape& _landscape
		,	QPixmap& _pixmap );

	/*virtual*/ void renderObjects(
			const Core::LandscapeModel::ILandscape& _landscape
		,	QPixmap& _pixmap );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	Framework::GUI::ImagesManager::IImagesManager& m_imagesManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_LANDSCAPE_RENDERER_HPP__
