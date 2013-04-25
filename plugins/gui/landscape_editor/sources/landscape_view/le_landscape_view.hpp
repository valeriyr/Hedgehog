
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

signals:

/*---------------------------------------------------------------------------*/

	void visibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onVisibleRectOnMinimapWasChanged( const float _relPosotionByX, const float _relPosotionByY );

	void onSliderMoved( int _value );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_LANDSCAPE_VIEW_HPP__
