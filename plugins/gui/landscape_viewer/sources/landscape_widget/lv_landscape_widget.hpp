
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

	// Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeWidget( QGraphicsScene* _scene, QWidget* _parent = NULL );

	virtual ~LandscapeWidget();

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_WIDGET_HPP__
