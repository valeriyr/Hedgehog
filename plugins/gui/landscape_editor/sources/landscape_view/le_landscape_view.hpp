
#ifndef __LE_LANDSCAPE_VIEW_HPP__
#define __LE_LANDSCAPE_VIEW_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class LandscapeView
	:	public QGraphicsView
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeView( QGraphicsScene* _scene, QWidget* _parent = NULL );

	virtual ~LandscapeView();

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

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_LANDSCAPE_VIEW_HPP__
