
#ifndef __LV_LANDSCAPE_SCENE_STATES_HPP__
#define __LV_LANDSCAPE_SCENE_STATES_HPP__

#include "landscape_viewer/sources/widgets/landscape_scene_states/lv_ilandscape_scene_state.hpp"
#include "landscape_model/ih/lm_isurface_item.hpp"

/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/

struct IEnvironment;

class LandscapeScene;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class LandscapeSceneGameState
	:	public Tools::Core::BaseWrapper< ILandscapeSceneState >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeSceneGameState( const IEnvironment& _environment, LandscapeScene& _scene );

	virtual ~LandscapeSceneGameState();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void onMousePossitionWasChanged( const QPointF& _point );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void removeSceneObjects();

	/*virtual*/ void setSceneObjectsVisibility( const bool _visibility );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	LandscapeScene& m_scene;

	QPointF m_startSelectionPoint;
	QGraphicsRectItem* m_selectionItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class LandscapeSurfaceItemEditingState
	:	public Tools::Core::BaseWrapper< ILandscapeSceneState >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeSurfaceItemEditingState( const IEnvironment& _environment
									, LandscapeScene& _scene
									, const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& _id );

	virtual ~LandscapeSurfaceItemEditingState();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void onMousePossitionWasChanged( const QPointF& _point );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void removeSceneObjects();

	/*virtual*/ void setSceneObjectsVisibility( const bool _visibility );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void setNewItemInPosition( const QPointF& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	LandscapeScene& m_scene;

	const Plugins::Core::LandscapeModel::ISurfaceItem::IdType m_id;

	QGraphicsPixmapItem* m_currentEditorItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class LandscapeObjectEditingState
	:	public Tools::Core::BaseWrapper< ILandscapeSceneState >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeObjectEditingState(  const IEnvironment& _environment
								, LandscapeScene& _scene
								, const QString& _name );

	virtual ~LandscapeObjectEditingState();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void onMousePossitionWasChanged( const QPointF& _point );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void removeSceneObjects();

	/*virtual*/ void setSceneObjectsVisibility( const bool _visibility );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void setNewItemInPosition( const QPointF& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	LandscapeScene& m_scene;

	const QString m_name;

	QGraphicsPixmapItem* m_currentEditorItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_SCENE_STATES_HPP__
