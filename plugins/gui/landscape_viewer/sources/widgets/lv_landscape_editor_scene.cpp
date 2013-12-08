
#include "landscape_viewer/sources/ph/lv_ph.hpp"

#include "landscape_viewer/sources/widgets/lv_landscape_scene.hpp"

#include "landscape_viewer/sources/internal_resources/lv_internal_resources.hpp"
#include "landscape_viewer/sources/surface_item_graphics_info/lv_isurface_item_graphics_info.hpp"
#include "landscape_viewer/sources/environment/lv_ienvironment.hpp"

#include "landscape_model/ih/lm_ieditable_landscape.hpp"

#include "lv_landscape_editor_scene.moc"


/*---------------------------------------------------------------------------*/

namespace Plugins {
namespace GUI {
namespace LandscapeViewer {

/*---------------------------------------------------------------------------*/


LandscapeEditorScene::LandscapeEditorScene( const IEnvironment& _environment, QObject* _parent )
	:	QGraphicsScene( _parent )
	,	m_environment( _environment )
	,	m_landscape()
	,	m_surfaceItemId()
	,	m_surfaceGraphicsItem( NULL )
{
} // LandscapeEditorScene::LandscapeEditorScene


/*---------------------------------------------------------------------------*/


LandscapeEditorScene::~LandscapeEditorScene()
{
} // LandscapeEditorScene::~LandscapeEditorScene


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::landscapeWasOpened(
	boost::intrusive_ptr< Plugins::Core::LandscapeModel::IEditableLandscape > _landscape )
{
	m_landscape = _landscape;
	regenerate();

	onChangeSurfaceItem( m_environment.getDefaultSurfaceItemId() );

} // LandscapeEditorScene::landscapeWasOpened


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::landscapeWasClosed()
{
	delete m_surfaceGraphicsItem;
	m_surfaceGraphicsItem = NULL;

	m_landscape.reset();
	regenerate();

} // LandscapeEditorScene::landscapeWasClosed


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::mousePressEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( _mouseEvent->buttons() & Qt::LeftButton )
		setNewItemInPosition( _mouseEvent->scenePos() );

	QGraphicsScene::mousePressEvent( _mouseEvent );

} // LandscapeEditorScene::mousePressEvent


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::mouseMoveEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	if ( _mouseEvent->buttons() & Qt::LeftButton )
		setNewItemInPosition( _mouseEvent->scenePos() );

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeEditorScene::mouseMoveEvent


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* _mouseEvent )
{
	emit landscapeWasChanged();

	QGraphicsScene::mouseMoveEvent( _mouseEvent );

} // LandscapeEditorScene::mouseReleaseEvent


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::onChangeSurfaceItem( const Plugins::Core::LandscapeModel::ISurfaceItem::IdType& _id )
{
	boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
		surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, _id );

	if ( !surfaceItemGraphicsInfo )
		return;

	m_surfaceItemId = _id;

	if ( m_surfaceGraphicsItem )
		delete m_surfaceGraphicsItem;

	m_surfaceGraphicsItem
		= new QGraphicsPixmapItem( m_environment.getPixmap( surfaceItemGraphicsInfo->getAtlasName(), surfaceItemGraphicsInfo->getFrameRect() ) );

	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
	opacityEffect->setOpacity( 0.5 );

	m_surfaceGraphicsItem->setGraphicsEffect( opacityEffect );

	addItem( m_surfaceGraphicsItem );

	m_surfaceGraphicsItem->setZValue( 1 );
	m_surfaceGraphicsItem->setPos( 0, 0 );

} // LandscapeEditorScene::onChangeSurfaceItem


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::onMousePossitionWasChanged( const QPointF& _point )
{
	if ( m_surfaceGraphicsItem )
	{
		qreal xpos = _point.x() < 0 ? 0 : ( static_cast< int >( _point.x() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );
		qreal ypos = _point.y() < 0 ? 0 : ( static_cast< int >( _point.y() / Resources::Landscape::CellSize ) * Resources::Landscape::CellSize );

		if ( xpos > width() - Resources::Landscape::CellSize )
			xpos = width() - Resources::Landscape::CellSize;

		if ( ypos > height() - Resources::Landscape::CellSize )
			ypos = height() - Resources::Landscape::CellSize;

		m_surfaceGraphicsItem->setPos( xpos, ypos );
	}

} // LandscapeEditorScene::onMousePossitionWasChanged


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::regenerate()
{
	clear();

	regenerateSurfaceLayer();
	regenerateObjectsLayer();

	setCorrectSceneSize();

} // LandscapeEditorScene::regenerate


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::regenerateSurfaceLayer()
{
	if ( m_landscape )
	{
		for ( unsigned int i = 0; i < m_landscape->getWidth(); ++i )
		{
			for ( unsigned int j = 0; j < m_landscape->getHeight(); ++j )
			{
				boost::intrusive_ptr< Plugins::Core::LandscapeModel::ISurfaceItem >
					surfaceItem = m_landscape->getSurfaceItem( QPoint( i, j ) );

				boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
					surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, surfaceItem->getId() );

				QGraphicsPixmapItem* item = addPixmap( m_environment.getPixmap( surfaceItemGraphicsInfo->getAtlasName(), surfaceItemGraphicsInfo->getFrameRect() ) );
				item->setPos( i * Resources::Landscape::CellSize, j * Resources::Landscape::CellSize  );
				item->setZValue( 0 );
			}
		}
	}

} // LandscapeEditorScene::regenerateSurfaceLayer


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::regenerateObjectsLayer()
{
	/*if ( m_landscape )
	{
		Plugins::Core::LandscapeModel::ILandscape::UnitsIteratorPtr
			unitsIterator = m_landscape->getUnitsIterator();

		while ( unitsIterator->isValid() )
		{
			QGraphicsPixmapItem* item = addPixmap(
				m_environment.getPixmap( unitsIterator->current()->getBundlePath(), unitsIterator->current()->getRectInBundle() ) );

			QPoint position = m_landscape->getUnitPosition( unitsIterator->current() );

			qreal posByX = position.m_x * Resources::Landscape::CellSize;
			qreal posByY = position.m_y * Resources::Landscape::CellSize;

			if ( static_cast< unsigned int >( unitsIterator->current()->getRectInBundle().width() ) > Resources::Landscape::CellSize )
			{
				posByX -= ( unitsIterator->current()->getRectInBundle().width() - Resources::Landscape::CellSize ) / 2;
			}

			if ( static_cast< unsigned int >( unitsIterator->current()->getRectInBundle().height() ) > Resources::Landscape::CellSize )
			{
				posByY -= ( unitsIterator->current()->getRectInBundle().height() - Resources::Landscape::CellSize ) / 2;
			}

			item->setPos( posByX, posByY );
			item->setZValue( 2 );

			unitsIterator->next();
		}
	}*/

} // LandscapeEditorScene::regenerateObjectsLayer


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::setCorrectSceneSize()
{
	if ( m_landscape )
	{
		setSceneRect( 0, 0, m_landscape->getWidth() * Resources::Landscape::CellSize, m_landscape->getHeight() * Resources::Landscape::CellSize );
	}
	else
	{
		setSceneRect( 0, 0, 0, 0 );
	}

} // LandscapeEditorScene::setCorrectSceneSize


/*---------------------------------------------------------------------------*/


void
LandscapeEditorScene::setNewItemInPosition( const QPointF& _position )
{
	if ( m_landscape )
	{
		QList< QGraphicsItem* > items = this->items( _position, Qt::ContainsItemShape, Qt::AscendingOrder );

		if ( items.isEmpty() )
		{
			return;
		}

		QPointF itemPos = items[0]->scenePos();
		removeItem( items[0] );

		m_landscape->setSurfaceItem(
				QPoint( itemPos.x() / Resources::Landscape::CellSize, itemPos.y() / Resources::Landscape::CellSize )
			,	m_surfaceItemId );

		boost::intrusive_ptr< ISurfaceItemGraphicsInfo >
			surfaceItemGraphicsInfo = m_environment.getSurfaceItemGraphicsInfo( Resources::Landscape::SkinId, m_surfaceItemId );

		QGraphicsPixmapItem* newItem = addPixmap( m_environment.getPixmap( surfaceItemGraphicsInfo->getAtlasName(), surfaceItemGraphicsInfo->getFrameRect() ) );
		newItem->setPos( itemPos );
		newItem->setZValue( 0 );
	}

} // LandscapeEditorScene::setNewItemInPosition


/*---------------------------------------------------------------------------*/

} // namespace LandscapeViewer
} // namespace GUI
} // namespace Plugins

/*---------------------------------------------------------------------------*/
