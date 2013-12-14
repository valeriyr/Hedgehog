
#ifndef __LV_LANDSCAPE_SCENE_HPP__
#define __LV_LANDSCAPE_SCENE_HPP__

/*---------------------------------------------------------------------------*/

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

/*---------------------------------------------------------------------------*/

class LandscapeScene
	:	public QGraphicsScene
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeScene( const IEnvironment& _environment, QObject* _parent = NULL );

	virtual ~LandscapeScene();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent );

/*---------------------------------------------------------------------------*/

	void landscapeWasOpened();

	void landscapeWasClosed();

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onUpdateTimerFired();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onSettingChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void generateLandscape();

	/*void updatePosition(
			boost::intrusive_ptr< Plugins::Core::LandscapeModel::IUnit > _unit
		,	QGraphicsPixmapItem* _graphicsItem );*/

/*---------------------------------------------------------------------------*/

	static QPoint convertFromScenePosition( const QPointF& _scenePosition );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	struct ObjectZValue
	{
		enum Enum
		{
				Surface             = 0
			,	Terrain             = 1
			,	Object              = 2
			,	SelectionRect       = 3
		};
	};

/*---------------------------------------------------------------------------*/

	/*typedef
		std::map<
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::IUnit >
			,	QGraphicsPixmapItem*
			>
		UnitsCollection;

	typedef UnitsCollection::iterator UnitsCollectionIterator;*/

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	QPointF m_startSelectionPoint;
	QGraphicsRectItem* m_selectionItem;

	//UnitsCollection m_unitsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_SCENE_HPP__
