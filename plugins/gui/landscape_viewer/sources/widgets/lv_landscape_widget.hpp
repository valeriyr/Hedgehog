
#ifndef __LV_LANDSCAPE_WIDGET_HPP__
#define __LV_LANDSCAPE_WIDGET_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

class LandscapeWidget
	:	public QGraphicsView
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeWidget( QGraphicsScene* _scene, QWidget* _parent = NULL );

	virtual ~LandscapeWidget();

/*---------------------------------------------------------------------------*/

	void wasResized();

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void visibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

	void landscapeViewWasResized( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onSliderMoved( int _value );

	void onChangeVisibleRect( const float _relPosotionByX, const float _relPosotionByY );

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

#endif // __LV_LANDSCAPE_WIDGET_HPP__
