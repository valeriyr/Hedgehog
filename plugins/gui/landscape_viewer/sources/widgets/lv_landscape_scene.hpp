
#ifndef __LV_LANDSCAPE_SCENE_HPP__
#define __LV_LANDSCAPE_SCENE_HPP__

/*---------------------------------------------------------------------------*/

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/h/lm_object.hpp"

/*---------------------------------------------------------------------------*/


namespace Framework
{
	namespace GUI
	{
		namespace AnimationManager
		{
			struct IAnimateObject;
		}
	}
}


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;
struct ILandscapeSceneState;

class ObjectGraphicsItem;

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

			,	SelectionRect       = 1000000
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

	static QPointF convertToScenePosition( const QPoint& _location );

	static QPointF roundScenePosition( const QPointF& _scenePosition );

	static QPointF correctSceneObjectPosition(
			const IEnvironment& _environment
		,	const int _sceneWidth
		,	const int _sceneHeight
		,	const QPointF& _roundedPosition
		,	const QString& _objectName );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onChangeSurfaceItem( const Plugins::Core::LandscapeModel::ISurfaceItem::Id& _id );

	void onChangeObject( const QString& _name );

	void onControlItemSelected();

	void onMousePossitionWasChanged( const QPointF& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onSettingChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectCreated( const Framework::Core::EventManager::Event& _event );

	void onCreateObjectFailed( const Framework::Core::EventManager::Event& _event );

	void onSurfaceItemChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectMoved( const Framework::Core::EventManager::Event& _event );

	void onObjectStateChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void generateLandscape();

	void generateTerrainMapLayer();

	void clearTerrainMapLayer();

	void regenerateTerrainMapLayer();

	void setCorrectSceneSize();

	void objectWasAdded( const Plugins::Core::LandscapeModel::Object::UniqueId& _id, ObjectGraphicsItem* _item );

	void markSelectedObjects();

	void removeAllObjects();

	void clearScene();

	void fillScene();

/*---------------------------------------------------------------------------*/

	void playAnimation(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _skinId
		,	const QString& _typeName
		,	const Core::LandscapeModel::ObjectState::Enum _state
		,	const Core::LandscapeModel::Direction::Enum _direction );

	void playAnimation(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _skinId
		,	const QString& _typeName
		,	const Core::LandscapeModel::ObjectState::Enum _state
		,	const Core::LandscapeModel::Direction::Enum _direction
		,	const qint64 _delay );

	void playAnimationOnce(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _skinId
		,	const QString& _typeName
		,	const Core::LandscapeModel::ObjectState::Enum _state
		,	const Core::LandscapeModel::Direction::Enum _direction );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map<
				Plugins::Core::LandscapeModel::Object::UniqueId
			,	ObjectGraphicsItem*
			>
		ObjectsCollection;

	typedef ObjectsCollection::iterator ObjectsCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	boost::intrusive_ptr< ILandscapeSceneState > m_landscapeSceneState;

	ObjectsCollection m_objectsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_SCENE_HPP__
