
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/landscape_scene_states/lv_landscape_scene_states.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"
#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/graphics_info_cache/lv_igraphics_info_cache.hpp"

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
		&&	isInSceneRect( _mouseEvent->scenePos() ) )
	{
		m_selectionItem = m_scene.addRect( 0, 0, 0, 0, QPen( QColor( 0, 255, 0 ) ) );
		m_selectionItem->setPos( _mouseEvent->scenePos().x(), _mouseEvent->scenePos().y() );
		m_selectionItem->setZValue( LandscapeScene::ZValue::SelectionRect );
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
	else if ( isInSceneRect( _mouseEvent->scenePos() ) )
	{
		m_environment.sendSelectedObjects( LandscapeScene::convertFromScenePosition( _mouseEvent->scenePos() ), _mouseEvent->modifiers() & Qt::ShiftModifier );
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


bool
LandscapeSceneGameState::isInSceneRect( const QPointF& _point ) const
{
	return
			_point.x() >= 0
		&&	_point.y() >= 0
		&&	_point.x() < m_scene.width()
		&&	_point.y() < m_scene.height();

} // LandscapeSceneGameState::isInSceneRect


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


LandscapeSurfaceItemEditingState::LandscapeSurfaceItemEditingState(	const IEnvironment& _environment
																,	LandscapeScene& _scene
																,	const Plugins::Core::LandscapeModel::ISurfaceItem::Id& _id )
	:	m_environment( _environment )
	,	m_scene( _scene )
	,	m_id( _id )
	,	m_currentEditorItem( NULL )
{
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
		QPointF roundedPosition( LandscapeScene::roundScenePosition( _point ) );

		if ( roundedPosition.x() > m_scene.width() - Resources::Landscape::CellSize )
			roundedPosition.setX( m_scene.width() - Resources::Landscape::CellSize );

		if ( roundedPosition.y() > m_scene.height() - Resources::Landscape::CellSize )
			roundedPosition.setY( m_scene.height() - Resources::Landscape::CellSize );

		m_currentEditorItem->setPos( roundedPosition.x(), roundedPosition.y() );
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
			surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( m_environment.getString( Resources::Properties::SkinId ), m_id );

		m_currentEditorItem
			= new QGraphicsPixmapItem( m_environment.getPixmap(
					surfaceItemGraphicsInfo->getAtlasName()
				,	Framework::GUI::ImagesManager::IImagesManager::TransformationData( surfaceItemGraphicsInfo->getFrameRect() ) ) );

		QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
		opacityEffect->setOpacity( 0.5 );

		m_currentEditorItem->setGraphicsEffect( opacityEffect );

		m_scene.addItem( m_currentEditorItem );

		m_currentEditorItem->setZValue( LandscapeScene::ZValue::EditorSurfaceItem );
		m_currentEditorItem->setPos( 0, 0 );
	}

} // LandscapeSurfaceItemEditingState::addSceneObjects


/*---------------------------------------------------------------------------*/


void
LandscapeSurfaceItemEditingState::setNewItemInPosition( const QPointF& _point )
{
	m_environment.setSurfaceItem( LandscapeScene::convertFromScenePosition( _point ), m_id );

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
	if ( ( _mouseEvent->buttons() & Qt::LeftButton ) && m_currentEditorItem )
	{
		int xpos = m_currentEditorItem->pos().x();
		int ypos = m_currentEditorItem->pos().y();

		Core::LandscapeModel::IStaticData::ObjectStaticData objectStaticData
			= m_environment.getObjectStaticData( m_name );

		const QPixmap& objectPixmap = m_environment.getPixmap( m_name );

		if ( objectPixmap.width() > ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) )
			xpos += ( objectPixmap.width() - ( objectStaticData.m_locateData->m_size.width() * Resources::Landscape::CellSize ) ) / 2;

		if ( objectPixmap.height() > ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) )
			ypos += ( objectPixmap.height() - ( objectStaticData.m_locateData->m_size.height() * Resources::Landscape::CellSize ) ) / 2;

		setNewItemInPosition( QPointF( xpos, ypos ) );
	}

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
		QPointF sceneObjectPosition(
			LandscapeScene::correctSceneObjectPosition(
					m_environment
				,	m_scene.width()
				,	m_scene.height()
				,	LandscapeScene::roundScenePosition( _point )
				,	m_name ) );

		m_currentEditorItem->setPos( sceneObjectPosition.x(), sceneObjectPosition.y() );
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
		m_currentEditorItem = new QGraphicsPixmapItem( m_environment.getPixmap( m_name ) );

		QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
		opacityEffect->setOpacity( 0.5 );

		m_currentEditorItem->setGraphicsEffect( opacityEffect );

		m_scene.addItem( m_currentEditorItem );

		m_currentEditorItem->setPos( 0, 0 );
	}

} // LandscapeObjectEditingState::addSceneObjects


/*---------------------------------------------------------------------------*/


void
LandscapeObjectEditingState::setNewItemInPosition( const QPointF& _point )
{
	m_environment.createObject( LandscapeScene::convertFromScenePosition( _point ), m_name );

} // LandscapeObjectEditingState::setNewItemInPosition


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
