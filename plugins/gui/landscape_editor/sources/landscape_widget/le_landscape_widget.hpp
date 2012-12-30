
#ifndef __LE_LANDSCAPE_WIDGET_HPP__
#define __LE_LANDSCAPE_WIDGET_HPP__

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

struct ILandscapeEditorController;

/*---------------------------------------------------------------------------*/

class LandscapeWidget
	:	public QGLWidget
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeWidget(
			const ILandscapeEditorController& _landscapeEditorController
		,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager
		,	QWidget* _parent = NULL );

	virtual ~LandscapeWidget();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void setDefaultLandscape();

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	/*virtual*/ void mouseDoubleClickEvent ( QMouseEvent* _event );

	/*virtual*/ void paintEvent( QPaintEvent* _event );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void regenerate();

	void regenerateSurfaceLayer();

	void regenerateObjectsLayer();

/*---------------------------------------------------------------------------*/

	void drawSurfaceItem(
			QPainter& _painter
		,	const unsigned int _widthIndex
		,	const unsigned int _heightIndex );

	void drawWater(
			QPainter& _painter
		,	const unsigned int _widthIndex
		,	const unsigned int _heightIndex );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const ILandscapeEditorController& m_landscapeEditorController;

	Framework::GUI::ImagesManager::IImagesManager& m_imagesManager;

	QPixmap m_surfaceLayer;

	QPixmap m_objectsLayer;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_LANDSCAPE_WIDGET_HPP__
