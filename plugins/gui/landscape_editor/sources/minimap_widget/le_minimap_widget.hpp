
#ifndef __LE_MINIMAP_WIDGET_HPP__
#define __LE_MINIMAP_WIDGET_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

struct ILandscapeEditorController;
struct ILandscapeRenderer;

/*---------------------------------------------------------------------------*/

class MinimapWidget
	:	public QGLWidget
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MinimapWidget(
			const ILandscapeEditorController& _landscapeEditorController
		,	ILandscapeRenderer& _landscapeRenderer
		,	QWidget* _parent = NULL );

	virtual ~MinimapWidget();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void setDefaultLandscape();

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void visibleAreaRectWasChanged( const float _relPosotionByX, const float _relPosotionByY );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onLandscapeSceneLoaded( const float _visibleWidth, const float _visibleHeight );

	void onVisibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	/*virtual*/ void paintEvent( QPaintEvent* _event );

	/*virtual*/ void mousePressEvent( QMouseEvent* _event );

	/*virtual*/ void mouseMoveEvent( QMouseEvent* _event );

/*---------------------------------------------------------------------------*/

	void wasClickedOnWidget( const QPoint& _atPoint );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static const QSize ms_fixedWidgetSize;

/*---------------------------------------------------------------------------*/

	const ILandscapeEditorController& m_landscapeEditorController;

	ILandscapeRenderer& m_landscapeRenderer;

	QPixmap m_surfaceLayer;

	QPixmap m_objectsLayer;

	QRect m_visibleArea;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_MINIMAP_WIDGET_HPP__
