
#ifndef __LV_LANDSCAPE_SCENE_STATES_HPP__
#define __LV_LANDSCAPE_SCENE_STATES_HPP__

#include "landscape_viewer/sources/widgets/landscape_scene_states/lv_ilandscape_scene_state.hpp"

#include "landscape_model/ih/lm_isurface_item.hpp"
#include "landscape_model/h/lm_game_object.hpp"

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

	/*virtual*/ void addSceneObjects();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	bool isInSceneRect( const QPointF& _point ) const;

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
									, const Tools::Core::Generators::IGenerator::IdType& _id );

	virtual ~LandscapeSurfaceItemEditingState();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void onMousePossitionWasChanged( const QPointF& _point );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void removeSceneObjects();

	/*virtual*/ void addSceneObjects();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	void setNewItemInPosition( const QPointF& _point );

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	LandscapeScene& m_scene;

	const Tools::Core::Generators::IGenerator::IdType m_id;

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

	/*virtual*/ void addSceneObjects();

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

class LandscapeObjectBuildState
	:	public Tools::Core::BaseWrapper< ILandscapeSceneState >
{

/*---------------------------------------------------------------------------*/

public:

/*---------------------------------------------------------------------------*/

	LandscapeObjectBuildState(  const IEnvironment& _environment
							,	LandscapeScene& _scene
							,	const Tools::Core::Generators::IGenerator::IdType& _builderId
							,	const QString& _name );

	virtual ~LandscapeObjectBuildState();

/*---------------------------------------------------------------------------*/

	/*virtual*/ void mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent );

	/*virtual*/ void onMousePossitionWasChanged( const QPointF& _point );

/*---------------------------------------------------------------------------*/

	/*virtual*/ void removeSceneObjects();

	/*virtual*/ void addSceneObjects();

/*---------------------------------------------------------------------------*/

private:

/*---------------------------------------------------------------------------*/

	const IEnvironment& m_environment;

	LandscapeScene& m_scene;

	const Tools::Core::Generators::IGenerator::IdType m_builderId;

	const QString m_name;

	QGraphicsPixmapItem* m_buildItem;

/*---------------------------------------------------------------------------*/

};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/

#endif // __LV_LANDSCAPE_SCENE_STATES_HPP__
