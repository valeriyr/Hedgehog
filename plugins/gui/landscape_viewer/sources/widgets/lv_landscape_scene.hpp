
#ifndef __LV_LANDSCAPE_SCENE_HPP__
#define __LV_LANDSCAPE_SCENE_HPP__

/*---------------------------------------------------------------------------*/

#include "event_manager/h/em_subscriber.hpp"
#include "event_manager/h/em_event.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/ih/lm_iunit.hpp"

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

/*---------------------------------------------------------------------------*/

public slots:

/*---------------------------------------------------------------------------*/

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

	void onUnitsSelectionChanged( const Framework::Core::EventManager::Event& _event );

	void onUnitMoved( const Framework::Core::EventManager::Event& _event );

	void onUnitStateChanged( const Framework::Core::EventManager::Event& _event );

/*---------------------------------------------------------------------------*/

	void generateLandscape();

	void generateTerrainMapLayer();

	void clearTerrainMapLayer();

	void regenerateTerrainMapLayer();

	void setCorrectSceneSize();

	void unitWasAdded( const Plugins::Core::LandscapeModel::IUnit::IdType& _id, ObjectGraphicsItem* _item );

	void markSelectedUnits();

	void removeAllObjects();

	void clearScene();

	void fillScene();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	typedef
		std::map<
				Plugins::Core::LandscapeModel::IUnit::IdType
			,	ObjectGraphicsItem*
			>
		UnitsCollection;

	typedef UnitsCollection::iterator UnitsCollectionIterator;

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	Framework::Core::EventManager::Subscriber m_subscriber;

	boost::intrusive_ptr< ILandscapeSceneState > m_landscapeSceneState;

	UnitsCollection m_unitsCollection;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_SCENE_HPP__
