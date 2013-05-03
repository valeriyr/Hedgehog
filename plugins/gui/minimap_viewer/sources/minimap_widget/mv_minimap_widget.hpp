
#ifndef __MV_MINIMAP_WIDGET_HPP__
#define __MV_MINIMAP_WIDGET_HPP__


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
namespace MinimapViewer {

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

	void showLandscape( const Core::LandscapeModel::ILandscape& _landscape );

	void setDefaultLandscape();

	void setVisibilityRectSize( const float _visibleWidth, const float _visibleHeight );

	void setVisibilityRectPosition( const float _visibleWidth, const float _visibleHeight );

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void visibilityRectChangedPosition( const float _relPosotionByX, const float _relPosotionByY );

/*---------------------------------------------------------------------------*/

protected:

/*---------------------------------------------------------------------------*/

	/*virtual*/ void paintEvent( QPaintEvent* _event );

	/*virtual*/ void mousePressEvent( QMouseEvent* _event );

	/*virtual*/ void mouseMoveEvent( QMouseEvent* _event );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void wasClickedOnWidget( const QPoint& _atPoint );

	void regenerate( const Core::LandscapeModel::ILandscape& _landscape );

	void renderSurface( const Core::LandscapeModel::ILandscape& _landscape );

	void renderObjects( const Core::LandscapeModel::ILandscape& _landscape );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	static const QSize ms_fixedWidgetSize;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	QPixmap m_surfaceLayer;

	QPixmap m_objectsLayer;

	QRect m_visibleArea;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace MinimapViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __MV_MINIMAP_WIDGET_HPP__
