
#ifndef __LV_MINIMAP_WIDGET_HPP__
#define __LV_MINIMAP_WIDGET_HPP__

/*---------------------------------------------------------------------------*/

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct ILandscape;
		}
	}
}

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class MinimapWidget
	:	public QWidget
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	MinimapWidget( const IEnvironment& _environment, QWidget* _parent = NULL );

	virtual ~MinimapWidget();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void visibilityRectChangedPosition( const float _relPosotionByX, const float _relPosotionByY );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onChangeVisibilityRectSize( const float _visibleWidth, const float _visibleHeight );

	void onChangeVisibilityRectPosition( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	/*virtual*/ void paintEvent( QPaintEvent* _event );

	/*virtual*/ void mousePressEvent( QMouseEvent* _event );

	/*virtual*/ void mouseMoveEvent( QMouseEvent* _event );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onSettingChanged( const Framework::Core::EventManager::Event& _event );

	void onSurfaceItemChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectWereChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void wasClickedOnWidget( const QPoint& _atPoint );

	void renderSurface();

	void renderObjects();

	void regenerate();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	QPixmap m_surfaceLayer;

	QPixmap m_objectsLayer;

	QRect m_visibleArea;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_MINIMAP_WIDGET_HPP__
