
#ifndef __LV_LANDSCAPE_EDITOR_SCENE_HPP__
#define __LV_LANDSCAPE_EDITOR_SCENE_HPP__

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
			struct IEditableLandscape;
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



/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void regenerate();

	void regenerateSurfaceLayer();
	void regenerateObjectsLayer();

	void setCorrectSceneSize();

	void setNewItemInPosition( const QPointF& _position );

/*---------------------------------------------------------------------------*/

	void onSettingChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct ObjectZValue
	{
		enum Enum
		{
				Surface             = 0
			,	CurrentSurfaceItem  = 1
			,	Terrain             = 2
			,	Object              = 3
		};
	};

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape > m_landscape;

	Framework::Core::EventManager::Subscriber m_subscriber;

	Plugins::Core::LandscapeModel::ISurfaceItem::IdType m_surfaceItemId;

	QString m_objectName;

	QGraphicsPixmapItem* m_currentEditorItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_EDITOR_SCENE_HPP__
