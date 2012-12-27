
#ifndef __LE_LANDSCAPE_WIDGET_HPP__
#define __LE_LANDSCAPE_WIDGET_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class LandscapeWidget
	:	public QGLWidget
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeWidget( const IEnvironment& _environment, QWidget* _parent = 0 );

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

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

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
