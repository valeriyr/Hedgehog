
#ifndef __LE_MINIMAP_WIDGET_HPP__
#define __LE_MINIMAP_WIDGET_HPP__

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

class MinimapWidget
	:	public QGLWidget
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MinimapWidget(
			const ILandscapeEditorController& _landscapeEditorController
		,	Framework::GUI::ImagesManager::IImagesManager& _imagesManager
		,	QWidget* _parent = NULL );

	virtual ~MinimapWidget();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void setDefaultLandscape();

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	/*virtual*/ void paintEvent( QPaintEvent* _event );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static const QSize ms_fixedWidgetSize;

/*---------------------------------------------------------------------------*/

	const ILandscapeEditorController& m_landscapeEditorController;

	Framework::GUI::ImagesManager::IImagesManager& m_imagesManager;

	QPixmap m_surfaceLayer;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_MINIMAP_WIDGET_HPP__
