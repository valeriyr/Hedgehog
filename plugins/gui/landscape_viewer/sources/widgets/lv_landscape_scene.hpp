
#ifndef __LV_LANDSCAPE_SCENE_HPP__
#define __LV_LANDSCAPE_SCENE_HPP__

/*---------------------------------------------------------------------------*/

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ILandscapeSceneState;

/*---------------------------------------------------------------------------*/

class LandscapeScene
	:	public QGraphicsScene
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	struct ObjectZValue
	{
		enum Enum
		{
				Surface             = 0
			,	Terrain             = 1
			,	EditorSurfaceItem   = 2
			,	Object              = 3
			,	SelectionRect       = 4
		};
	};

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

	QPoint getObjectPosition( const QString& _skinId, const QString& _objectName, const QPointF& _mousePosition );

/*---------------------------------------------------------------------------*/

	static QPoint convertFromScenePosition( const QPointF& _scenePosition );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onUpdateTimerFired();

	void onChangeSurfaceItem( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& _id );

	void onChangeObject( const QString& _name );

	void onControlItemSelected();

	void onMousePossitionWasChanged( const QPointF& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onSettingChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectCreated( const Framework::Core::EventManager::Event& _event );

	void onSurfaceItemChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void generateLandscape();

	void setCorrectSceneSize();

	/*void updatePosition(
			boost::intrusive_ptr< Plugins::Core::LandscapeModel::IUnit > _unit
		,	QGraphicsPixmapItem* _graphicsItem );*/

/*---------------------------------------------------------------------------*/

private:

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

	boost::intrusive_ptr< ILandscapeSceneState > m_landscapeSceneState;

	//UnitsCollection m_unitsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_SCENE_HPP__
