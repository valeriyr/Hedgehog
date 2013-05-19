
#ifndef __LV_LANDSCAPE_EDITOR_WIDGET_HPP__
#define __LV_LANDSCAPE_EDITOR_WIDGET_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class LandscapeEditorWidget
	:	public QGraphicsView
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeEditorWidget( QGraphicsScene* _scene, QWidget* _parent = NULL );

	virtual ~LandscapeEditorWidget();

/*---------------------------------------------------------------------------*/

	void wasResized();

	void changeVisibleRect( const float _relPosotionByX, const float _relPosotionByY );

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void visibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

	void landscapeViewWasResized( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onSliderMoved( int _value );

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	/*virtual*/ void resizeEvent( QResizeEvent* _event );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_EDITOR_WIDGET_HPP__
