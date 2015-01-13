
#ifndef __LV_LANDSCAPE_SCENE_HPP__
#define __LV_LANDSCAPE_SCENE_HPP__

/*---------------------------------------------------------------------------*/

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/h/lm_game_object.hpp"
#include "landscape_model/h/lm_directions.hpp"

#include "animation_manager/ih/am_ianimate_object.hpp"

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

class LandscapeScene;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class ObjectGraphicsItem
	:	public QGraphicsPixmapItem
	,	public Framework::GUI::AnimationManager::IAnimateObject
{

public:

	ObjectGraphicsItem(
			const QPixmap& _pixmap
		,	const IEnvironment& _environment
		,	const LandscapeScene& _landscapeScene
		,	const QString& _objectName
		,	const Tools::Core::Generators::IGenerator::IdType& _objectId
		,	QGraphicsItem* _parent = NULL
		);

	/*virtual*/ void setSprite( const QPixmap& _sprite );

	/*virtual*/ QVariant itemChange( GraphicsItemChange _change, const QVariant& value );

	const Tools::Core::Generators::IGenerator::IdType& getObjectId() const;

private:

	void correctedPosition();

private:

	const IEnvironment& m_environment;

	const LandscapeScene& m_landscapeScene;

	const QString m_objectName;

	const Tools::Core::Generators::IGenerator::IdType m_objectId;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class LandscapeScene
	:	public QGraphicsScene
{

/*---------------------------------------------------------------------------*/

	Q_OBJECT

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	struct ZValue
	{
		enum Enum
		{
				Surface             = 0
			,	Terrain             = 1
			,	EditorSurfaceItem   = 2

			,	ObjectsBegin        = 3

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

/*---------------------------------------------------------------------------*/

	ObjectGraphicsItem* getObjectGraphicsItem( const Tools::Core::Generators::IGenerator::IdType& _objectId ) const;

	ObjectGraphicsItem* getObjectGraphicsItem( const QPointF& _scenePosition ) const;

/*---------------------------------------------------------------------------*/

	QSize calculateLandscapeSize() const;

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

	static QPointF correctSceneObjectPosition(
			const IEnvironment& _environment
		,	const int _sceneWidth
		,	const int _sceneHeight
		,	const QPointF& _roundedPosition
		,	const QString& _objectName
		,	const QPixmap& _objectPixmap );

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

	void onChangeSurfaceItem( const Tools::Core::Generators::IGenerator::IdType& _id );

	void onChangeObject( const QString& _name );

	void onControlItemSelected();

	void onBuildObjectButtonPressed( const Tools::Core::Generators::IGenerator::IdType _builderId, const QString& _objectName );

	void onMousePossitionWasChanged( const QPointF& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void onSettingChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectAdded( const Framework::Core::EventManager::Event& _event );

	void onObjectRemoved( const Framework::Core::EventManager::Event& _event );

	void onCreateObjectFailed( const Framework::Core::EventManager::Event& _event );

	void onSurfaceItemChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectsSelectionChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectMoved( const Framework::Core::EventManager::Event& _event );

	void onObjectStateChanged( const Framework::Core::EventManager::Event& _event );

	void onObjectWasHit( const Framework::Core::EventManager::Event& _event );

	void onObjectReadyToAttack( const Framework::Core::EventManager::Event& _event );

	void onObjectStartBuilding( const Framework::Core::EventManager::Event& _event );

	void onBuilderHasStartedBuild( const Framework::Core::EventManager::Event& _event );

	void onBuilderHasFinishedBuild( const Framework::Core::EventManager::Event& _event );

	void onHolderHasStartedCollect( const Framework::Core::EventManager::Event& _event );

	void onHolderHasStopCollect( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void generateLandscape();

	void generateTerrainMapLayer();

	void clearTerrainMapLayer();

	void regenerateTerrainMapLayer();

	void setCorrectSceneSize();

	void objectWasAdded( const Tools::Core::Generators::IGenerator::IdType& _id, ObjectGraphicsItem* _item );

	ObjectGraphicsItem* addObject(
			const QString& _objectName
		,	const QPoint& _objectLocation
		,	const Tools::Core::Generators::IGenerator::IdType _id
		,	const Core::LandscapeModel::Emplacement::Enum _emplacement );

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

	void playAnimationOnce(
			Framework::GUI::AnimationManager::IAnimateObject& _animateObject
		,	const QString& _skinId
		,	const QString& _typeName
		,	const Core::LandscapeModel::ObjectState::Enum _state
		,	const Core::LandscapeModel::Direction::Enum _direction );

/*---------------------------------------------------------------------------*/

	void removeObject( const Tools::Core::Generators::IGenerator::IdType _id );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map<
				Tools::Core::Generators::IGenerator::IdType
			,	ObjectGraphicsItem*
			>
		ObjectsCollection;

	typedef ObjectsCollection::iterator ObjectsCollectionIterator;
	typedef ObjectsCollection::const_iterator ObjectsCollectionConstIterator;

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
