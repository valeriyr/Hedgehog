
#ifndef __LE_LANDSCAPE_SCENE_HPP__
#define __LE_LANDSCAPE_SCENE_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct IEditableLandscape;
		}
	}
}

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

struct ILandscapeEditorController;

/*---------------------------------------------------------------------------*/

class LandscapeScene
	:	public QGraphicsScene
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeScene(
			const ILandscapeEditorController& _landscapeEditorController
		,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager
		,	QObject* _parent = NULL );

	virtual ~LandscapeScene();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void setDefaultLandscape();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void regenerate();

	void regenerateSurfaceLayer();
	void regenerateObjectsLayer();

	void setCorrectSceneSize();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeEditorController& m_landscapeEditorController;

	Framework::GUI::ImagesManager::IImagesManager& m_imagesManager;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_LANDSCAPE_SCENE_HPP__
