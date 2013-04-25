
#ifndef __LE_VIEWS_MEDIATOR_HPP__
#define __LE_VIEWS_MEDIATOR_HPP__


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeEditor {

/*---------------------------------------------------------------------------*/

class ViewsMediator
	:	public QObject
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	ViewsMediator();

	virtual ~ViewsMediator();

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void visibleRectOnMinimapWasChanged( const float _relPosotionByX, const float _relPosotionByY );

	void landscapeSceneLoaded( const float _visibleWidth, const float _visibleHeight );

	void visibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onVisibleRectOnMinimapWasChanged( const float _relPosotionByX, const float _relPosotionByY );

	void onLandscapeSceneLoaded( const float _visibleWidth, const float _visibleHeight );

	void onVisibleRectOfLandscapeViewWasChanged( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeEditor
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LE_VIEWS_MEDIATOR_HPP__
