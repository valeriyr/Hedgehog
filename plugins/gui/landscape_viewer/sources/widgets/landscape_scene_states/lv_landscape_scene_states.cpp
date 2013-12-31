
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/landscape_scene_states/lv_landscape_scene_states.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/graphics_info_cache/lv_graphics_info_cache.hpp"

#include "landscape_model/ih/lm_ilandscape.hpp"
#include "landscape_model/ih/lm_ilandscape_handle.hpp"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


LandscapeSceneGameState::LandscapeSceneGameState( const IEnvironment& _environment, LandscapeScene& _scene )
	:	m_environment( _environment )
	,	m_scene( _scene )
	,	m_startSelectionPoint()
	,	m_selectionItem( NULL )
{
} // LandscapeSceneGameState::LandscapeSceneGameState


/*---------------------------------------------------------------------------*/


LandscapeSceneGameState::~LandscapeSceneGameState()
{
	removeSceneObjects();

} // LandscapeSceneGameState::~LandscapeSceneGameState


/*---------------------------------------------------------------------------*/


void
LandscapeSceneGameState::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if (	_mouseEvent->buttons() == Qt::LeftButton
		&&	_mouseEvent->scenePos().x() >= 0
		&&	_mouseEvent->scenePos().y() >= 0
		&&	_mouseEvent->scenePos().x() <= m_scene.width()
		&&	_mouseEvent->scenePos().y() <= m_scene.height() )
	{
		m_selectionItem = m_scene.addRect( 0, 0, 0, 0 );
		m_selectionItem->setPos( _mouseEvent->scenePos().x(), _mouseEvent->scenePos().y() );
		m_selectionItem->setZValue( LandscapeScene::ObjectZValue::SelectionRect );
		m_startSelectionPoint = _mouseEvent->scenePos();
	}

} // LandscapeSceneGameState::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeSceneGameState::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( m_selectionItem )
	{
		qreal posByX = m_startSelectionPoint.x();
		qreal posByY = m_startSelectionPoint.y();

		qreal mounsePosByX = _mouseEvent->scenePos().x() < 0 ? 0 : _mouseEvent->scenePos().x();
		qreal mounsePosByY = _mouseEvent->scenePos().y() < 0 ? 0 : _mouseEvent->scenePos().y();

		qreal width = mounsePosByX - m_startSelectionPoint.x();
		qreal height = mounsePosByY - m_startSelectionPoint.y();

		if ( width < 0 )
		{
			posByX += width;
			width = -width;
		}

		if ( height < 0 )
		{
			posByY += height;
			height = -height;
		}

		if ( posByX + width >= m_scene.width() )
		{
			width = m_scene.width() - posByX - 1;
		}

		if ( posByY + height >= m_scene.height() )
		{
			height = m_scene.height() - posByY - 1;
		}

		m_selectionItem->setPos( posByX, posByY );

		m_selectionItem->setRect( 0, 0, width, height );
	}

} // LandscapeSceneGameState::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeSceneGameState::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( m_selectionItem )
	{
		QPoint pos1 = LandscapeScene::convertFromScenePosition( m_selectionItem->scenePos() );
		QPoint pos2 = LandscapeScene::convertFromScenePosition( QPoint(		m_selectionItem->scenePos().x() + m_selectionItem->rect().width()
																		,	m_selectionItem->scenePos().y() + m_selectionItem->rect().height() ) );

		m_environment.selectItemsInModel( QRect( pos1, pos2 ) );

		removeSceneObjects();
	}
	else
	{
		m_environment.moveSelectedItems( LandscapeScene::convertFromScenePosition( _mouseEvent->scenePos() ) );
	}

} // LandscapeSceneGameState::mouseReleaseEvent


/*---------------------------------------------------------------------------*/


void
LandscapeSceneGameState::onMousePossitionWasChanged( const QPointF& _point )
{
} // LandscapeSceneGameState::onMousePossitionWasChanged


/*---------------------------------------------------------------------------*/


void
LandscapeSceneGameState::removeSceneObjects()
{
	if ( m_selectionItem )
	{
		m_scene.removeItem( m_selectionItem );
		delete m_selectionItem;
		m_selectionItem = NULL;
		m_startSelectionPoint = QPointF();
	}

} // LandscapeSceneGameState::removeSceneObjects


/*---------------------------------------------------------------------------*/


void
LandscapeSceneGameState::addSceneObjects()
{
} // LandscapeSceneGameState::addSceneObjects


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


LandscapeSurfaceItemEditingState::LandscapeSurfaceItemEditingState(	const IEnvironment& _environment
																,	LandscapeScene& _scene
																,	const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& _id )
	:	m_environment( _environment )
	,	m_scene( _scene )
	,	m_id( _id )
	,	m_currentEditorItem( NULL )
{
	if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
		return;

	addSceneObjects();

} // LandscapeSurfaceItemEditingState::LandscapeSurfaceItemEditingState


/*---------------------------------------------------------------------------*/


LandscapeSurfaceItemEditingState::~LandscapeSurfaceItemEditingState()
{
	removeSceneObjects();

} // LandscapeSurfaceItemEditingState::~LandscapeSurfaceItemEditingState


/*---------------------------------------------------------------------------*/


void
LandscapeSurfaceItemEditingState::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( _mouseEvent->buttons() & Qt::LeftButton )
		setNewItemInPosition( _mouseEvent->scenePos() );

} // LandscapeSurfaceItemEditingState::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeSurfaceItemEditingState::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	/*if ( _mouseEvent->buttons() & Qt::LeftButton )
		setNewItemInPosition( _mouseEvent->scenePos() );*/

} // LandscapeSurfaceItemEditingState::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeSurfaceItemEditingState::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
} // LandscapeSurfaceItemEditingState::mouseReleaseEvent


/*---------------------------------------------------------------------------*/


void
LandscapeSurfaceItemEditingState::onMousePossitionWasChanged( const QPointF& _point )
{
	if ( m_currentEditorItem )
	{
		qreal xpos = _point.x() < 0 ? 0 : ( static_cast< int >( _point.x() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );
		qreal ypos = _point.y() < 0 ? 0 : ( static_cast< int >( _point.y() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );

		if ( xpos > m_scene.width() - Resources::Landscape::CellSize )
			xpos = m_scene.width() - Resources::Landscape::CellSize;

		if ( ypos > m_scene.height() - Resources::Landscape::CellSize )
			ypos = m_scene.height() - Resources::Landscape::CellSize;

		m_currentEditorItem->setPos( xpos, ypos );
	}

} // LandscapeSurfaceItemEditingState::onMousePossitionWasChanged


/*---------------------------------------------------------------------------*/


void
LandscapeSurfaceItemEditingState::removeSceneObjects()
{
	if ( m_currentEditorItem )
	{
		delete m_currentEditorItem;
		m_currentEditorItem = NULL;
	}

} // LandscapeSurfaceItemEditingState::removeSceneObjects


/*---------------------------------------------------------------------------*/


void
LandscapeSurfaceItemEditingState::addSceneObjects()
{
	if ( !m_currentEditorItem )
	{
		boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
			surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, m_id );

		m_currentEditorItem
			= new QGraphicsPixmapItem( m_environment.getPixmap(
					surfaceItemGraphicsInfo->getAtlasName()
				,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( surfaceItemGraphicsInfo->getFrameRect() ) ) );

		QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
		opacityEffect->setOpacity( 0.5 );

		m_currentEditorItem->setGraphicsEffect( opacityEffect );

		m_scene.addItem( m_currentEditorItem );

		m_currentEditorItem->setZValue( LandscapeScene::ObjectZValue::EditorSurfaceItem );
		m_currentEditorItem->setPos( 0, 0 );
	}

} // LandscapeSurfaceItemEditingState::addSceneObjects


/*---------------------------------------------------------------------------*/


void
LandscapeSurfaceItemEditingState::setNewItemInPosition( const QPointF& _point )
{
	if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
		return;

	qreal xpos = _point.x() < 0 ? 0 : static_cast< int >( _point.x() / Resources::Landscape::CellSize );
	qreal ypos = _point.y() < 0 ? 0 : static_cast< int >( _point.y() / Resources::Landscape::CellSize );

	m_environment.setSurfaceItem( QPoint( xpos, ypos ), m_id );

} // LandscapeSurfaceItemEditingState::setNewItemInPosition


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


LandscapeObjectEditingState::LandscapeObjectEditingState(	const IEnvironment& _environment
														,	LandscapeScene& _scene
														,	const QString& _name )
	:	m_environment( _environment )
	,	m_scene( _scene )
	,	m_name( _name )
	,	m_currentEditorItem( NULL )
{
	if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
		return;

	addSceneObjects();

} // LandscapeObjectEditingState::LandscapeObjectEditingState


/*---------------------------------------------------------------------------*/


LandscapeObjectEditingState::~LandscapeObjectEditingState()
{
	removeSceneObjects();

} // LandscapeObjectEditingState::~LandscapeObjectEditingState


/*---------------------------------------------------------------------------*/


void
LandscapeObjectEditingState::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( _mouseEvent->buttons() & Qt::LeftButton )
		setNewItemInPosition( _mouseEvent->scenePos() );

} // LandscapeObjectEditingState::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeObjectEditingState::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	/*if ( _mouseEvent->buttons() & Qt::LeftButton )
		setNewItemInPosition( _mouseEvent->scenePos() );*/

} // LandscapeObjectEditingState::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeObjectEditingState::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
} // LandscapeObjectEditingState::mouseReleaseEvent


/*---------------------------------------------------------------------------*/


void
LandscapeObjectEditingState::onMousePossitionWasChanged( const QPointF& _point )
{
	if ( m_currentEditorItem )
	{
		qreal xpos = _point.x() < 0 ? 0 : ( static_cast< int >( _point.x() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );
		qreal ypos = _point.y() < 0 ? 0 : ( static_cast< int >( _point.y() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );

		const QPixmap& objectPixmap = m_environment.getPixmap( m_name, GraphicsInfoCache::ms_anySkinIdentifier );

		if ( xpos > m_scene.width() - Resources::Landscape::CellSize )
			xpos = m_scene.width() - Resources::Landscape::CellSize;

		if ( ypos > m_scene.height() - Resources::Landscape::CellSize )
			ypos = m_scene.height() - Resources::Landscape::CellSize;

		if ( static_cast< unsigned int >( objectPixmap.width() ) > Resources::Landscape::CellSize )
			xpos -= ( objectPixmap.width() - Resources::Landscape::CellSize ) / 2;

		if ( static_cast< unsigned int >( objectPixmap.height() ) > Resources::Landscape::CellSize )
			ypos -= ( objectPixmap.height() - Resources::Landscape::CellSize ) / 2;

		m_currentEditorItem->setPos( xpos, ypos );
	}

} // LandscapeObjectEditingState::onMousePossitionWasChanged


/*---------------------------------------------------------------------------*/


void
LandscapeObjectEditingState::removeSceneObjects()
{
	if ( m_currentEditorItem )
	{
		delete m_currentEditorItem;
		m_currentEditorItem = NULL;
	}

} // LandscapeObjectEditingState::removeSceneObjects


/*---------------------------------------------------------------------------*/


void
LandscapeObjectEditingState::addSceneObjects()
{
	if ( !m_currentEditorItem )
	{
		m_currentEditorItem = new QGraphicsPixmapItem( m_environment.getPixmap( m_name, GraphicsInfoCache::ms_anySkinIdentifier ) );

		QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
		opacityEffect->setOpacity( 0.5 );

		m_currentEditorItem->setGraphicsEffect( opacityEffect );

		m_scene.addItem( m_currentEditorItem );

		m_currentEditorItem->setZValue( LandscapeScene::ObjectZValue::Object );
		m_currentEditorItem->setPos( 0, 0 );
	}

} // LandscapeObjectEditingState::addSceneObjects


/*---------------------------------------------------------------------------*/


void
LandscapeObjectEditingState::setNewItemInPosition( const QPointF& _point )
{
	if ( m_environment.getBool( Resources::Properties::TerrainMapVisibility ) )
		return;

	qreal xpos = _point.x() < 0 ? 0 : static_cast< int >( _point.x() / Resources::Landscape::CellSize );
	qreal ypos = _point.y() < 0 ? 0 : static_cast< int >( _point.y() / Resources::Landscape::CellSize );

	m_environment.createObject( QPoint( xpos, ypos ), m_name );

} // LandscapeObjectEditingState::setNewItemInPosition


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
