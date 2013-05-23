
#ifndef __LV_LANDSCAPE_EDITOR_SCENE_HPP__
#define __LV_LANDSCAPE_EDITOR_SCENE_HPP__

/*---------------------------------------------------------------------------*/

namespace Plugins
{
	namespace Core
	{
		namespace LandscapeModel
		{
			struct IEditableLandscape;
			struct ISurfaceItem;
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

class LandscapeEditorScene
	:	public QGraphicsScene
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeEditorScene( const IEnvironment& _environment, QObject* _parent = NULL );

	virtual ~LandscapeEditorScene();

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened(
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape > _landscape );

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent );

/*---------------------------------------------------------------------------*/

signals:

/*---------------------------------------------------------------------------*/

	void landscapeWasChanged();

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onChangeSurfaceItem(
		boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > _surfaceItem );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void regenerate();

	void regenerateSurfaceLayer();
	void regenerateObjectsLayer();

	void setCorrectSceneSize();

	void setNewItemInPosition( const QPointF& _position );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape > m_landscape;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem > m_surfaceItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_EDITOR_SCENE_HPP__
